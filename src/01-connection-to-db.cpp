#include <iostream>

#include <pqxx/pqxx>
void print_info(const pqxx::connection &c) {
    std::cout << "Connected to " << c.dbname() << '\n';
    std::cout << "By " << c.username() << "\nWhole connection string: " << c.connection_string() << '\n';
}
int main() {
    pqxx::connection c;
    pqxx::connection c1("..."); // connect to your user's database
    pqxx::connection c2("..."); // connect to db_workshop database
    assert(std::string(c2.dbname()) == "db_workshop");
    pqxx::connection c3("..."); // connect to db_workshop database using postgres user;
    print_info(c3);
    assert(c3.dbname() == std::string("db_workshop"));
    assert(c3.username() == std::string("postgres"));
    return 0;
}