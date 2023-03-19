#ifndef DB_WORKSHOP_ITEM_H
#define DB_WORKSHOP_ITEM_H
#include "manufacturer.h"
struct item {
    int id;
    std::string name;
    int price;
    double rating;
    manufacturer manufacturer;
};
#endif//DB_WORKSHOP_ITEM_H
