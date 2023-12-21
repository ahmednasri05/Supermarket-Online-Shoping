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
#include "api_users.h"
//#include "main.cpp"

using namespace std;

int generateID() {
    srand(time(0));
    //cout << "Rand " << rand() << endl;
    return rand();
}

void ClearScreen() {
    system("clear"); // Command to clear the terminal on macOS
    system("cls");  // Command to clear the terminal on windows
}

void mainMenuRedirection(sqlite3* db, string userId) {
    cout << "===========================================\n";
    cout << "To return to main menu press 0" << endl;
    cout << "To exit the app press any other key" << endl;
    cout << "===========================================\n";
    int mainMenu;
    cin >> mainMenu;
    void Greeting(sqlite3* db, string userId);
    if (mainMenu == 0) {
        ClearScreen();
        //Return to main menu
         Greeting(db, userId);
    }
}

void ViewItemInfo(sqlite3* db, string barCode) {
    ItemInfo itemInfo = {};
    itemInfo = getProductInfo(db, barCode);
    cout << "ProductName " << itemInfo.ProductName << " Desctription " << itemInfo.Description << endl;
}

void ViewProducts(sqlite3* db, string userId, bool view) {
    
    vector<Product> products;
    products = getProducts(db);
    cout << "PRODUCTS ON SHELF" << "\n";
    cout << "===================================================================================================================================================================\n";
    cout << "ItemBarCode" << setw(30) << "Name" << setw(30) << "Price" << setw(30) << "Category" << setw(30) << "ProductionDate" << setw(30) << "ExpirationDate" << endl;
    for (int i = 0; i < products.size(); i++) {
        cout <<products[i].Code << setw(30) << products[i].Name << setw(30) << products[i].Price << setw(30) << products[i].CategoryType << setw(30) << products[i].ProductionDate << setw(30) << products[i].ExpirationDate <<endl;
    }
    cout << "===================================================================================================================================================================\n";
    if (view == false) {
    cout << "===========================================\n";
    cout << "To View an item's info press 1" << endl;
    cout << "To Continue Press any other number" << endl;
    cout << "===========================================\n";
    int itemInfo = 0;
    cin >> itemInfo;
    while (itemInfo == 1) {
    cout << "===========================================\n";
    cout << "To View an item's info enter its bar code" << endl;
    cout << "===========================================\n";
    int barCode = 0;
    cin >> barCode;
        ViewItemInfo(db, to_string(barCode));
    cout << "===========================================\n";
    cout << "To View another item press 1" << endl;
    cout << "To Exit press 0" << endl;
    cout << "===========================================\n";
    cin >> itemInfo;
    }
        mainMenuRedirection(db, userId);
    }
    
}

void Order(sqlite3* db, string userId, bool edit) {
    ClearScreen();
    
    cout << "THIS IS YOUR ADD TO CART FUNCTION" << endl << endl;
    //Single order which represents order of each loop
    UserOrder userOrder = {};
    //Previous Orders in cart
    vector<UserOrder> pendingOrder;
    //All orders in cart
    vector<UserOrder> dynamicArray;
    //The Product that the user chose
    Product requiredProduct = {};
    Date myDate = {};
    //Item Code
    int input = 0;
    //cout <<  "Input =" << input << endl;
    //Ordered quantity
    int quantity = 0;
    int exitVal = 0;
    int totalPrice = 0;
    int itemCounter = 1;

    //While the user didn't exit continue to take orders
    while (input != -1 && quantity != -1) {

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    ViewProducts(db, userId, true);
    cout << "To add product to cart enter its bar code: ";
    input = 0;
    cin >> input;
    
    if (input == -1) {
        input = -1;
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

    //Check if product out of stock
    if (requiredProduct.Quantity == 0) {
        cout << "This Product is out of stock" << endl;
        continue;
    }

    //!!!!!!!!!!! REMEMBER TO CHANGE THE USER ID !!!!!!!!!!!

    //Get previous orders in cart for this user by his ID
    pendingOrder = userOrdersByID(db, userId);
    if (pendingOrder.size() != 0) {
        //cout << "There is a pending order please confirm the purchase or delete it" << endl;
        //return;
        int largest = 0;
        for (int i = 0; i < pendingOrder.size(); i++) {
            if ( pendingOrder[i].ItemCode > largest) {
                largest = pendingOrder[i].ItemCode;
            }
        }
        itemCounter = itemCounter + largest;
    }

    cout << "Choose the quantity you want: ";
    cin >> quantity;
    //Validate the quantity
    while (requiredProduct.Quantity < quantity) {
        cout << "The Only available quantity is " << requiredProduct.Quantity << endl;
        cout << "Choose a smaller quantity: ";
        cin >> quantity;
    }

   //Update the quantity of the product 
    requiredProduct.Quantity = requiredProduct.Quantity - quantity;

    //!!!!!!!!!!! REMEMBER TO CHANGE THE USER ID !!!!!!!!!!!

    //Assign the order to order struct
    userOrder.UserID = userId;
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
    ClearScreen();
    cout << "YOUR CART" << endl;
    cout << "===================================================================================================================================================================\n\n";
    cout << "ItemCode" << setw(30) << "ProductName" << setw(30) << "Quantity" << setw(30) <<"Product Price" << endl;
    for (int i = 0; i < dynamicArray.size(); i++) {
        cout << dynamicArray[i].ItemCode << setw(30) << dynamicArray[i].ProductName << setw(30) << dynamicArray[i].Quantity << setw(30) << dynamicArray[i].Price << endl;
    }
    for (int i = 0; i < pendingOrder.size(); i++) {
        cout << pendingOrder[i].ItemCode << setw(30) << pendingOrder[i].ProductName << setw(30) << pendingOrder[i].Quantity << setw(30) << pendingOrder[i].Price << endl;
        totalPrice = totalPrice + pendingOrder[i].Price;
    }
    cout << "Total Price: " << totalPrice << endl;
    cout <<  "\n" <<"To Exit press -1 " << endl;
    cout << "===================================================================================================================================================================\n\n";
     
    }

    cout << endl;
    //Save each order seperatly
    for (int i = 0; i < dynamicArray.size(); i++) {
        saveOrder(db, dynamicArray[i]);
    }
    

    cout << "Thank you for your Purchase" << endl;
    if (edit == true) {
        cout << "Redirecting to edit order to proceed" << endl;
        return;
    }
    mainMenuRedirection(db, userId);
  
}

void ViewUserOrders(sqlite3* db, bool view, string userId) {
    if (view == false) {
         ClearScreen();
    }
   
    //!!!!!!!!!!! REMEMBER TO CHANGE THE USER ID !!!!!!!!!!!

    string userID = userId;
    int totalPrice = 0;
    vector<UserOrder> userOrders;
    //Get user orders with his ID
    userOrders = userOrdersByID(db, userID);
    if (userOrders.size() == 0) {
        cout << "No Items in the cart" << endl;
        return;
    }

    //Display the cart
    cout << "======================================================================================================\n";
    cout << "ItemCode" << setw(30) << "ProductName" << setw(30) << "Quantity" << setw(30) << "ItemPrice" << endl;
    for (int i = 0; i < userOrders.size(); i++) {
        cout << userOrders[i].ItemCode << setw(30) << userOrders[i].ProductName << setw(30) << userOrders[i].Quantity << setw(30) << userOrders[i].Price << endl;
        totalPrice = totalPrice + userOrders[i].Price;
    }
    cout << "Total Price: " << totalPrice << endl;
     cout << "======================================================================================================\n";
    //Checker that tells if this function is called as a feature to display order
    //Or only display function that is used in other blocks
    if (view == false) {

    mainMenuRedirection(db, userId);

    }
    
}

void EditOrder(sqlite3* db, string userId) {
    //!!!!!!!!!!! REMEMBER TO CHANGE THE USER ID !!!!!!!!!!!
    //ClearScreen();
    cout << "THIS IS YOUR EDIT ORDER FUNCTION" << endl << endl;
    
    int exitVal = 0;
    while(exitVal != - 1) {
    ClearScreen();
    cout << "Your Order is:" << endl;
    ViewUserOrders(db, true, userId);
    cout << "=====================================\n";
    cout << "To Remove an item press 1" << endl;
    cout << "To Edit an item's quantity press 2" << endl;
    cout << "To Add a new item press 3" << endl;
    cout << "=====================================\n";
    //User choice 
    int input = 0;

    int itemCode = 0;
    //Chosen product struct
    Product requiredProduct = {};
    //Previous order to modify
    vector<UserOrder> userOrders;

    UserOrder userOrder = {};
    int oldQuantity = 0;
    int newQuantity = 0;
    userOrders = userOrdersByID(db, userId);

    cin >> input;

      while (input != 1 && input != 2 && input != 3) {
        cout << "Please only select between 1, 2 and 3 for different category and 1 to continue" << endl;
        cin >> input;
    }
    
     if (input == 3) {
        //Add to cart
        Order(db, userId, true);
        EditOrder(db, userId);
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

     
    
    cout << "Data updated successfully" << endl;
    cout << "=====================================\n";
    cout << "To exit edit order press -1" << endl;
    cout << "To Editing in your order press any other number" << endl;
    cout << "=====================================\n";
    cin >> exitVal;
    }
    mainMenuRedirection(db, userId);
    
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