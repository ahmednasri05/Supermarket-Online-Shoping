#pragma once

#include <iostream>
#include <string>
#include "model_users.h"
#include "database_conn.h"
#include "user_database.h"
#include "OpenDataBase.h"
#include "api_products.h"
using namespace std;


bool SignIn(sqlite3* db) {
    Person user = {};
    Person dbUser = {};
    cout << "This is the sign in page please sign in to proceed" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter your Username:";
    getline(cin, user.Name);
    cout << "Enter your Password:";
    getline(cin, user.Password);

    dbUser = getUserNameAndPass(db, user);
    if (dbUser.ID == "") {
        cout << "Invalid user name or password" << endl << endl;
        cout << "To exit press -1" << endl;
        cout << "To Retry press any other key" << endl;
        int exitVal = 0;
        cin >> exitVal;
        if (exitVal == -1) {
            return false;
        }
        SignIn(db);
    }
    cout << "You Have Logged in successfully";
    cout << "Redirecting to the main menu" << endl << endl;
     void Greeting(sqlite3* db, string userID);
        Greeting(db, dbUser.ID);  
    return true;
}

void Signup(sqlite3* db) {
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
    cout << "Your account has been created please log in to proceed" << endl;
    cout << "Redirecting to login page" << endl << endl;
    SignIn(db);
}

void Greet(sqlite3* db) {

    int input = 0;
    bool signedIn = false;
    ClearScreen();

    cout << "Welcome to the super-market App" << endl << endl;
    cout << "To sign up press 1" << endl;
    cout << "To sign in press 2" << endl;
    cout << "To exit the app press any other number" << endl;
    cin >> input;

    switch(input) {
    case 1:
        cout << "You chose to sign up" << endl << endl;
        Signup(db);
        break;
    case 2:
        cout << "You chose to sign in" << endl << endl;
        SignIn(db);
        break;

    }
    
}

void Greeting(sqlite3* db, string userID) {
    ClearScreen();
    int userActionChoice = 0;
    cout << "Welcome to the online super-market App" << endl;
    cout << endl;
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

        cout << "You Chose to enter user data" << endl << endl;
        Signup(db);

        break;
    case 2:

        cout << "You entered 2" << endl;

        break;
    case 3:

        cout << "You Chose to make an order" << endl << endl;
        Order(db, userID, false);

        break;
    case 4:

        cout << "You Chose to review your order" << endl << endl;
        ViewUserOrders(db, false, userID);

        break;
    case 5:

        cout << "You chose to edit your order" << endl << endl;
        EditOrder(db, userID);

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
        Greeting(db, userID);

    }

}





