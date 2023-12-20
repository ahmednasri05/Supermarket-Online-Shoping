#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <iomanip>
#include "model_products.h"
#include "database_conn.h"
#include "user_database.h"
#include "OpenDataBase.h"

using namespace std;

int generateID() {
    srand(time(0));
    //cout << "Rand " << rand() << endl;
    return rand();
}

void ClearScreen() {
    system("clear"); // Command to clear the terminal on macOS
}

//bool dateChekcer(Date date) {
//    time_t currentTime = std::time(nullptr);
//
//    // Convert the current time to a calendar time
//    //tm* currentCalendarTime = std::localtime(&currentTime);
//
//    // Extract the year from the calendar time
//    int currentYear = currentCalendarTime->tm_year + 1900; // tm_year is years since 1900
//
//    int currentMonth = currentCalendarTime->tm_mon + 1; 
//
//    int currentDay = currentCalendarTime->tm_mday;
//    // cout << "Year " << currentYear << " Month " << currentMonth << " Day " << currentDay <<endl;
//    // cout << "EYear " << date.year << " EMonth " << date.month << " EDay " << date.day <<endl;
//    if (date.year < currentYear) {
//        return false;
//    }
//    if (date.year == currentYear && date.month < currentMonth) {
//        return false;
//    }
//
//     if (date.year == currentYear && date.month == currentMonth && date.day < currentDay) {
//        return false;
//    }
//
//    return true;
//    
//}

void Order(sqlite3* db) {
    
    
    UserOrder userOrder = {};
    vector<UserOrder> pendingOrder;
    Product requiredProduct = {};
    Date myDate = {};
    int input = 0;
    int exitVal = 0;
    int totalPrice = 0;
    int itemCounter = 1;
    vector<UserOrder> dynamicArray;
    // While the user didn't exit continue to take orders
    while (exitVal != -1) {

    exitVal = 0;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "To Choose the product press its id: ";
    cin >> input;

    if (input == -1) {
        exitVal = -1;
        continue;
    }

    //Get the product from the database to check its expiration date
    //and quanity
    requiredProduct = getProductById(db, to_string(input));

    //Check if this product is in the database
    if (requiredProduct.Code == "") {
        cout << "Invalid ID" << endl;
        continue;
    }
    
    //Convert the string date to day month and year
    stringstream ss(requiredProduct.ExpirationDate);
    char delimiter;
    ss >> myDate.day >> delimiter >> myDate.month >> delimiter >> myDate.year;
    //Function we created to check if the date of expiration has past and returns true
    //if it didn't expire and false if it did
    //bool dateChecker = dateChekcer(myDate);

    ////if (dateChecker == false) {
    //    cout << "This Product is expired choose another product" << endl;;
    //    continue;
    //}
    
    if (requiredProduct.Quantity == 0) {
        cout << "This Product is out of stock" << endl;
        continue;
    }
    //!!!!!!!!!!! REMEMBER TO CHANGE THE USER ID !!!!!!!!!!!
    pendingOrder = userOrdersByID(db, to_string(2));
    if (pendingOrder.size() != 0) {
        cout << "There is a pending order please confirm the purchase or delete it" << endl;
        return;
    }
    cout << "Choose the quantity you want: ";
    int quantity;
    cin >> quantity;

    while (requiredProduct.Quantity < quantity) {
        cout << "The Only available quantity is " << requiredProduct.Quantity << endl;
        cout << "Choose a smaller quantity: ";
        cin >> quantity;
    }

   //Update the quantity of the product 
    requiredProduct.Quantity = requiredProduct.Quantity - quantity;

    //!!!!!!!!!!! REMEMBER TO CHANGE THE USER ID !!!!!!!!!!!
    //Assign the order
    userOrder.UserID = 2;
    userOrder.ProductID = to_string(input);
    userOrder.Quantity = quantity;
    userOrder.ProductName = requiredProduct.Name;
    userOrder.Price = requiredProduct.Price * quantity;
    userOrder.ItemCode = itemCounter;
    itemCounter++;
    totalPrice = totalPrice + userOrder.Price;
    //Push the order into an array to take another order
    dynamicArray.push_back(userOrder);

    //Update new product quantity
    updateProduct(db, requiredProduct);
    //Display cart
    system("cls");
    ClearScreen();
    cout << "ItemCode" << setw(10) << "ProductName" << setw(10) << "Quantity" << "Product Price" << endl;
    for (int i = 0; i < dynamicArray.size(); i++) {
        cout << dynamicArray[i].ItemCode << setw(10) << dynamicArray[i].ProductName << setw(15) << dynamicArray[i].Quantity << setw(10) << dynamicArray[i].Price << endl;
    }
    cout << "Total Price: " << totalPrice << endl;
    cout <<  "\n" <<"To Exit press -1 " << endl;
    cout << "To Continue press -2 " << endl;

    cin >> exitVal;

    //Validation for the right input
    while (exitVal != 1 && exitVal != -1 && exitVal != -2) {
        cout << "Please only select between -1 to exit -2 for different category and 1 to continue" << endl;
        cin >> exitVal;
    }
     
    }

    cout << endl;
    //Save each order seperatly
    for (int i = 0; i < dynamicArray.size(); i++) {
        saveOrder(db, dynamicArray[i]);
    }
    //Display the order
    cout << "ItemCode" << setw(10) << "ProductName" << setw(10) << "Quantity" << "Product Price" << endl;
    for (int i = 0; i < dynamicArray.size(); i++) {
        cout << dynamicArray[i].ItemCode << setw(10) <<dynamicArray[i].ProductName << setw(15) << dynamicArray[i].Quantity << setw(10) << dynamicArray[i].Price << endl;
    }
    cout << "Total Price: " << totalPrice << endl;
    
}

void ViewUserOrders(sqlite3* db) {
    //!!!!!!!!!!! REMEMBER TO CHANGE THE USER ID !!!!!!!!!!!
    int userID = 2;
    int totalPrice = 0;
    vector<UserOrder> userOrders;
    userOrders = userOrdersByID(db, to_string(userID));
    if (userOrders.size() == 0) {
        cout << "No Items in the cart" << endl;
        return;
    }
    cout << "ItemCode" << setw(12) << "ProductName" << setw(10) << "Quantity" << setw(10) << "ItemPrice" << endl;
    for (int i = 0; i < userOrders.size(); i++) {
        cout << userOrders[i].ItemCode << setw(20) << userOrders[i].ProductName << setw(9) << userOrders[i].Quantity << setw(9) << userOrders[i].Price << endl;
        totalPrice = totalPrice + userOrders[i].Price;
    }
    cout << "Total Price: " << totalPrice << endl;
}

void EditOrder(sqlite3* db) {
    //!!!!!!!!!!! REMEMBER TO CHANGE THE USER ID !!!!!!!!!!!
    ClearScreen();
    cout << "Your Order is:" << endl;
    ViewUserOrders(db);
    int userID = 2;
    cout << "To Remove an item press 1" << endl;
    cout << "To Edit an item's quantity press 2" << endl;
    int input = 0;
    int itemCode = 0;
    Product requiredProduct = {};
    vector<UserOrder> userOrders;
    UserOrder userOrder = {};
    int oldQuantity = 0;
    int newQuantity = 0;
    userOrders = userOrdersByID(db, to_string(userID));

    cin >> input;
      while (input != 1 && input != 2) {
        cout << "Please only select between 1 and 2 for different category and 1 to continue" << endl;
        cin >> input;
    }
    
      
  
        cout << "Please Enter the item code: ";
        cin >> itemCode;
        //Loop over user orders
    for (int i = 0; i < userOrders.size(); i++) {
        //Get the item with this code
        if (userOrders[i].ItemCode == itemCode ) {
            userOrder = userOrders[i];
        }
        
    }
    
    while (userOrder.ItemCode == 0) {
        cout << "Invalid ID" << endl;
        cout << "Please Enter the item code: ";
        cin >> itemCode;
    //Loop over user orders
    for (int i = 0; i < userOrders.size(); i++) {
        //Get the item with this code
        if (userOrders[i].ItemCode == itemCode ) {
            userOrder = userOrders[i];
        }
        
    }
    }
    
    if (input == 1) {
        cout << "DELETECode " << userOrder.ProductID << " DELETEITEM " << userOrder.ItemCode << endl;
        deleteOrderItem(db, userOrder.ProductID, userOrder.ItemCode);
    }
    if (input == 2) {
        cout << "Please Enter the new quantity: ";
        cin >> newQuantity;
        
        requiredProduct = getProductById(db, userOrder.ProductID);
        requiredProduct.Quantity = requiredProduct.Quantity + oldQuantity;
        requiredProduct.Quantity = requiredProduct.Quantity - newQuantity;
        
        userOrder.Price = newQuantity * requiredProduct.Price;
        userOrder.Quantity = newQuantity;
       
        updateOrder(db, userOrder);
    }

     
    
    cout << "Data updated successfully" << endl;;
}

void CreateProductCategory(sqlite3* db) {
    ProductCategory category;
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Category Name: ";
    getline(cin, category.CategoryType);

    saveCategory(db, category);
    
}

void ViewCategories(sqlite3* db) {
    
    vector<ProductCategory> categories;
    categories = getCategories(db);
    cout << "ID" << setw(10) << "Type" << endl;
    

    for (int i = 0; i < categories.size(); i++) {
        cout <<categories[i].ID << setw(15) << categories[i].CategoryType << endl;
    }
}

void CreateProduct(sqlite3* db) {
     Product product;
     Date myDate = {};
     string date = "";
     cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Category ID: ";
    getline(cin, product.CategoryType);

    cout << "Enter Product Name: ";
    getline(cin, product.Name);

    product.Code = to_string(generateID());

    cout << "Enter Production Day: ";
    cin >> myDate.day;
    cout << "Enter Production Month: ";
    cin >> myDate.month;
    cout << "Enter Production Year: ";
    cin >> myDate.year;

    date = to_string(myDate.day) +  "/" + to_string(myDate.month) +  "/" + to_string(myDate.year);

    product.ProductionDate = date;

    cout << "Enter Expiration Day: ";
    cin >> myDate.day;
    cout << "Enter Expiration Month: ";
    cin >> myDate.month;
    cout << "Enter Expiration Year: ";
    cin >> myDate.year;

    date = to_string(myDate.day) +  "/" + to_string(myDate.month) +  "/" + to_string(myDate.year);
    
    product.ExpirationDate = date;

    
    cout << "Enter Product Price: ";
    cin >> product.Price;

    cout << "Enter Product Quantity: ";
    cin >> product.Quantity;


    saveProduct(db, product);
}