#include <pqxx/pqxx>
#include <iostream>
#include "user.h"
#include "item.h"
#include "order.h"

user construct_user(const pqxx::row& row) {
    auto [id, name, last_name] = row.as<int, std::string, std::string>();
    return user{id, name, last_name};
}

namespace {
    std::ostream& operator<<(std::ostream& os, const user& user) {
        os << "user{" << user.id << ", " << user.name << ", " << user.surname << '}';
        return os;
    }
}

int main() {
    pqxx::connection c;
    assert(c.dbname() == std::string("db_workshop"));

    pqxx::work tx{c};
    try {
        pqxx::row row = tx.exec1("SELECT count(*) FROM users");
        auto [users_count] = row.as<int>();
        std::cout << "There are " << users_count << " users" << std::endl;

        pqxx::row random_user_row = tx.exec1("SELECT * FROM users LIMIT 1");
        user random_user = construct_user(random_user_row);
        std::cout << random_user << std::endl;

        pqxx::result all_users = tx.exec("SELECT * FROM users");
        std::vector<user> users;
        users.reserve(all_users.size());
        for (const auto& row : all_users) {
            users.push_back(construct_user(row));
        }

        for (const auto& [id, name, surname] : tx.stream<int, std::string, std::string>("SELECT * FROM USERS")) {
            // blazing fast
        }

        std::cout << "after we get all users, we have " << users.size() << " users\n";
    } catch (const std::exception& e) {
        std::cout << "Exception occurred: " << e.what() << '\n';
    }
}