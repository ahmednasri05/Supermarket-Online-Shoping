#pragma once

#include <iostream>
#include <string>
#include "model_users.h"
#include "database_conn.h"
#include "user_database.h"
#include "OpenDataBase.h"
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
        cout << "You entered 3" << endl;
        break;

    case 4:
        cout << "You entered 4" << endl;
        break;

    case 5:
        cout << "You entered 5" << endl;
        break;

    case 6:
        cout << "You entered 6" << endl;
        break;

    case 7:
        cout << "You entered 7" << endl;
        break;

    default:
        cout << "Please Only Select A Number From The Menu" << endl;
        cout << endl;
        Greeting(db);
    }

}





