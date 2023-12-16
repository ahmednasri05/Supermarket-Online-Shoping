#pragma once

#include <iostream>
#include <string>
#include "model_users.h"
#include "database_conn.h"
#include "user_database.h"
#include "OpenDataBase.h"
#include "api_products.h"
using namespace std;

void CreateUser(sqlite3* db) {
    Person user = {};
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Your Username: ";
    getline(cin, user.Name);
    cout << "Enter Your Password: ";
    getline(cin, user.Password);
    cout << "Enter Your Phone Number: ";
    getline(cin, user.PhoneNumber);
    cout << "Enter Your Location: ";
    getline(cin, user.Location);
    cout << endl;
    saveUser(db, user);
}

void Greeting(sqlite3* db) {
    int userActionChoice = 0;
    cout << "Welcome to the online super-market" << endl;
    cout << "To Edit Your Personal Info Press 1" << endl;
    cout << "To View The Products Menu Press 2" << endl;
    cout << "To Make An Order Press 3" << endl;
    cout << "To Review Your Order Press 4" << endl;
    cout << "To Modify Your Order Press 5" << endl;
    cout << "To Display The Order Total Price Press 6" << endl;
    cout << "To Logout From The App Press 7" << endl;
    cout << "(For Admins Only) To Create a new Product press 8" << endl;
    cout << "(For Admins Only) To Create a new category press 9" << endl;

    cin >> userActionChoice;

    switch (userActionChoice) {
    case 1:
        cout << "You Chose to enter user data" << endl;
        CreateUser(db);
        break;

    case 2:
        cout << "You entered 2" << endl;
        break;

    case 3:
        cout << "You Chose to make an order" << endl;
        Order(db);
        break;

    case 4:
        cout << "You Chose to review your order" << endl;
        ViewUserOrders(db);
        break;

    case 5:
        cout << "You chose to edit your order" << endl;
        EditOrder(db);
        break;

    case 6:
        cout << "You entered 6" << endl;
        break;

    case 7:
        cout << "You entered 7" << endl;
        break;
    
    case 8:
        cout << "You Chose to create a product" << endl;
        CreateProduct(db);
        break;

    case 9:
        cout << "You Chose to create a category" << endl;
        CreateProductCategory(db);
        break;

     case 10:
        cout << "You Chose to view categories" << endl;
        ViewCategories(db);
        break;

    default:
        cout << "Please Only Select A Number From The Menu" << endl;
        cout << endl;
        Greeting(db);
    }

}





