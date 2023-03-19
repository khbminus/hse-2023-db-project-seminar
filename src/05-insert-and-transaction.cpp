#include <pqxx/pqxx>
#include <iostream>
#include "user.h"
#include "item.h"
#include "order.h"
#include <optional>

namespace {
    std::ostream& operator<<(std::ostream& os, const user& user) {
        os << "user{" << user.id << ", " << user.name << ", " << user.surname << '}';
        return os;
    }
}

std::optional<user> get_user_by_name(pqxx::work& w, const std::string &first_name, const std::string &last_name) {
    return user{};
}

user create_new_user(pqxx::work& w, const std::string& first_name, const std::string& surname) {
    return user{};
}

int main() {
    pqxx::connection c, c2;
    assert(c.dbname() == std::string("db_workshop"));

    pqxx::work tx{c};
    try {
        user user = create_new_user(tx, "Perry", "The Platypus");
//        tx.commit();
        pqxx::work tx2{c2};
        assert(get_user_by_name(tx, "Perry", "The Platypus").has_value());
        assert(get_user_by_name(tx2, "Perry", "The Platypus").has_value());
//        tx.commit();
    } catch (const std::exception &e) {
        std::cout << "Error occurred: " << e.what() << std::endl;
        return 1;
    }
}