#include <iostream>

#include <pqxx/pqxx>


void print_info(const pqxx::connection &c) {
    std::cout << "Connected to " << c.dbname() << '\n';
    std::cout << "By " << c.username() << "\nWhole connection string: " << c.connection_string() << std::endl;
}
int main() {
    pqxx::connection c;
    print_info(c);
    int SUBTASK = 0;
    switch (SUBTASK) {
        case 0:
            assert(c.dbname() == std::string("db_workshop"));
            break;
        case 1:
            assert(c.dbname() == std::string("db_workshop"));
            assert(c.username() == std::string("postgres"));
            break;
    }
    return 0;
}