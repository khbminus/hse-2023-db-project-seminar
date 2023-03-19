#ifndef DB_WORKSHOP_ORDER_H
#define DB_WORKSHOP_ORDER_H
#include "user.h"
#include "item.h"
#include <vector>
struct order {
    user customer;
    std::vector<item> items;
    std::string delivery_address;
};
#endif//DB_WORKSHOP_ORDER_H
