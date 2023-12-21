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

int EditInformation(sqlite3* db, string userID)
{

    Person person;
    int choice, age;
    string name, password, phoneNumber, location;
    person = getUserByID(db, userID);
    cout << "=====================================\n";
    cout << "choice 1 : edit your name\n";
    cout << "choice 2 : edit your password\n";
    cout << "choice 3 : edit your phone number\n";
    cout << "choice 4 : edit your location\n";
    // cout << "choice 5 : edit your age\n";
    cout << "=====================================\n";
    cout << "Enter your choice\n";

    cin >> choice;
    person.ID = userID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (choice)
    {
    case 1 :
        cout << "You're editing your name\n";
        cout << "Enter your name\n";

        getline(cin, name);

        person.Name = name;
            // edit the name in the database
         break;

    case 2 : 
        cout << "You're editing your password\n";
        cout << "Enter your new password\n";

        getline(cin, password);

        person.Password = password;
        // edit the password
        break;

    case 3 :
        cout << "You're editing your phone number\n";
        cout << "Enter your new phone number\n";

        getline(cin, phoneNumber);

        person.PhoneNumber = phoneNumber;
        // edit the phone number
        break;

    case 4 :
        cout << "You're editing your location\n";
        cout << "Enter your new location\n";

        getline(cin, location);

        person.Location = location;
        // edit the location

        break;

    // case 5 : 
    //     cout << "You're editing your age\n";
    //     cout << "Enter your new age\n";

    //     cin >> age;

    //     person.Age = age;
    default:
        break;
    }

    updateUser(db, person);
    //mainMenuRedirection(db, userID);
    return 0;
}

void Greet(sqlite3* db) {

    int input = 0;
    bool signedIn = false;
    ClearScreen();

    cout << "Welcome to the super-market App" << endl << endl;
    cout << "=====================================\n";
    cout << "To sign up press 1" << endl;
    cout << "To sign in press 2" << endl;
    cout << "To exit the app press any other number" << endl;
    cout << "=====================================\n";
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
    cout << "====================================================\n";
    cout << "To Edit Your Personal Info Press 1" << endl;
    cout << "To View The Products Menu Press 2" << endl;
    cout << "To Make An Order Press 3" << endl;
    cout << "To Review Your Order Press 4" << endl;
    cout << "To Modify Your Order Press 5" << endl;
    cout << "To Display The Order Total Price Press 6" << endl;
    cout << "To Logout From The App Press 7" << endl;
    cout << "(For Admins Only) To Create a new Product press 8" << endl;
    cout << "(For Admins Only) To Create a new category press 9" << endl;
    cout << "====================================================\n";

    cin >> userActionChoice;

    switch (userActionChoice) {
    case 1:

        cout << "You Chose to enter user data" << endl << endl;
        EditInformation(db, userID);
        break;
    case 2:

        cout << "You entered 2" << endl;
        ViewProducts(db, userID, false);
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





