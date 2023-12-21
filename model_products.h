#pragma once
using namespace std;
#include <string>

 struct Date {
        int day;
        int month;
        int year;
    };

struct ProductCategory {
    int ID;
    string CategoryType;
};

struct Product {
    string ID;
    int Price;
    int Quantity;
    string Code;
    string Name;
    string CategoryType;
    string ProductionDate;
    string ExpirationDate;
};

struct ItemInfo {
    string ID;
    string ProductName;
    string productCode;
    string Description;
};

struct UserOrder {
    string UserID;
    int Price;
    string ProductID;
    int Quantity;
    string ProductName;
    int ItemCode;
};

