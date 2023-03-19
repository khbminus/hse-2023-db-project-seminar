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
    auto result = w.exec("SELECT * FROM users WHERE name = '" + w.esc(first_name) + "' AND surname = '" + w.esc(last_name) + "' LIMIT 1");
    if (result.empty()) {
        return {};
    }
    auto [id, name, surname] = result[0].as<int, std::string, std::string>();
    return user{id, name, surname};
}

user create_new_user(pqxx::work& w, const std::string& first_name, const std::string& surname) {
    w.exec("INSERT INTO users(id, name, surname) VALUES (DEFAULT, '" + first_name + "', '" + surname + "')");
    return get_user_by_name(w, first_name, surname).value();
}

int main() {
    pqxx::connection c, c2;
    assert(c.dbname() == std::string("db_workshop"));


    pqxx::work tx{c};
    // "SELECT * FROM users WHERE name = '' AND 1 <> 1; DROP DATABASE db_workshop; name' -- AND surname = 'surname' LIMIT 1");
    get_user_by_name(tx, "' AND 1 <> 1; DROP TABLE order_items; --", "");
    tx.commit();
    return 0;
    try {
        user user = create_new_user(tx, "Perry", "The Platypus2");
        tx.commit();
        pqxx::work tx2{c2};
//        assert(get_user_by_name(tx, "Perry", "The Platypus2").has_value());
        assert(get_user_by_name(tx2, "Perry", "The Platypus2").has_value());
//        tx.commit();
    } catch (const std::exception &e) {
        std::cout << "Error occurred: " << e.what() << std::endl;
        return 1;
    }
}