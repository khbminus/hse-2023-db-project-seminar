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
        tx.exec(R"#(CREATE TABLE manufacturers(
    id serial primary key ,
    name TEXT,
country TEXT))#");
        tx.exec(R"#(CREATE TABLE items(
                id serial primary key,
                name text not null,
                price int not null CHECK ( price > 0 ),
                rating float not null,
                manufacturer_id int not null,
                constraint m_fk
                foreign key (manufacturer_id)
                references manufacturers(id)
                ))#");

        tx.exec(R"#(
        CREATE TABLE orders(
                id serial primary key,
                customer int not null,
                delivery_address text not null,
                constraint fk_customer
                foreign key (customer)
                references users(id)
                ))#");
        tx.exec(R"#(CREATE TABLE order_items(
                order_id int not null,
                item_id int not null,
                primary key (order_id, item_id),
                constraint fk_order
                foreign key (order_id)
                references orders(id),
                constraint fk_item
                foreign key (item_id)
                references items(id)
                ))#");
        tx.commit();
    } catch (const std::exception& e) {
        std::cout << "Exception occurred: " << e.what() << '\n';
    }
}