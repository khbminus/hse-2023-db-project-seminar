#include <pqxx/pqxx>
#include <iostream>
#include "user.h"

int main() {
    pqxx::connection c;
    assert(c.dbname() == std::string("db_workshop"));

    pqxx::work tx{c};
    try {
        tx.exec(R"#(
            CREATE TABLE users(
                id serial PRIMARY KEY,
                name TEXT NOT NULL,
                surname TEXT NOT NULL
            ))#");
        tx.exec("CREATE TABLE items(...)");
        tx.exec("CREATE TABLE manufacturers(...)");
        tx.exec("CREATE TABLE orders(...)"); // how?
    } catch (const std::exception& e) {
        std::cout << "Exception occurred: " << e.what() << '\n';
    }
}