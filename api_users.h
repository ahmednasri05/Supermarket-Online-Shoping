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
    int exitVal = 0;
    cout << "This is the sign in page please sign in to proceed" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter your Username:";
    getline(cin, user.Name);
    cout << "Enter your Password:";
    getline(cin, user.Password);

    dbUser = getUserNameAndPass(db, user);
    if (dbUser.ID == "") {
        cout << "Invalid user name or password" << endl << endl;
        cout << "To exit press 1" << endl;
        cout << "To Retry press 0" << endl;
        
        cin >> exitVal;
        exitVal = cinFail(exitVal);
        if (exitVal == 1) {
            return false;
        } else {
            SignIn(db);
        }
        
    }
    cout << "Exit " << exitVal;
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
    char exit;
    person = getUserByID(db, userID);
    bool exitVal = true;
    while (exitVal)
    {
    ClearScreen();
    cout << "=====================================\n";
    cout << "choice 1 : edit your name\n";
    cout << "choice 2 : edit your password\n";
    cout << "choice 3 : edit your phone number\n";
    cout << "choice 4 : edit your location\n";
    cout << "choice 5 : to exit\n";
    // cout << "choice 5 : edit your age\n";
    cout << "=====================================\n";
    cout << "Enter your choice\n";

    cin >> choice;
    choice = cinFail(choice);
    person.ID = userID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice)
        {
        case 1:
            cout << "You're editing your name\n";
            cout << "Enter your name\n";

            getline(cin, name);

            person.Name = name;
            // edit the name in the database
            break;

        case 2:
            cout << "You're editing your password\n";
            cout << "Enter your new password\n";

            getline(cin, password);

            person.Password = password;
            // edit the password
            break;

        case 3:
            cout << "You're editing your phone number\n";
            cout << "Enter your new phone number\n";

            getline(cin, phoneNumber);

            person.PhoneNumber = phoneNumber;
            // edit the phone number
            break;

        case 4:
            cout << "You're editing your location\n";
            cout << "Enter your new location\n";

            getline(cin, location);

            person.Location = location;
            // edit the location

            break;

        case 5 : 
                 cout << "Do you want to exit? Y / N: ";
                 cin >> exit;

                 if (exit == 'Y' || exit == 'y')
                 {
                    exitVal = false;
                     break;
                 }
                 break;

        default:
            cout << "Only choose from 1 to 5" << endl;
            break;
        }
    }

    updateUser(db, person);
    mainMenuRedirection(db, userID);
    return 0;
}
void Greet(sqlite3* db) {
    int INTRO = 0;
    int input = 0;
    bool signedIn = false;
    

    cout << "Welcome to the super-market App" << endl << endl;
    if (INTRO == 0) {
        coolWelcomeIntro();
        enhancedSparklingFirework();
        enjoyTextAnimation();
        //system("pause");
        setTextColor(ANSI_RESET);
        INTRO++;
    }
    ClearScreen();
    cout << "=====================================\n";
    cout << "To sign up press 1" << endl;
    cout << "To sign in press 2" << endl;
    cout << "To exit the app 0" << endl;
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
    setTextColor(ANSI_CYAN);
    printWithDelay("=================================================\n", 5);
    printWithDelay("        Welcome to Online Supermarket         \n", 10);
    printWithDelay("=================================================\n", 5);
    setTextColor(ANSI_RESET);

    cout << "\n";

    setTextColor(ANSI_YELLOW);
    printWithDelay("1. Edit Personal Info        [Press 1]\n", 10);
    printWithDelay("2. View Products Menu        [Press 2]\n", 10);
    printWithDelay("3. Make an Order             [Press 3]\n", 10);
    printWithDelay("4. Review Your Order         [Press 4]\n", 10);
    printWithDelay("5. Modify Your Order         [Press 5]\n", 10);
    printWithDelay("6. Logout from the App       [Press 6]\n", 10);
    setTextColor(ANSI_RESET);

    cout << "\n";

    setTextColor(ANSI_CYAN);
    printWithDelay("=================================================\n", 10);
    printWithDelay("Please enter the corresponding number to navigate:\n", 10);
    printWithDelay("=================================================\n", 10);
    setTextColor(ANSI_RESET);

    cin >> userActionChoice;

    switch (userActionChoice) {
    case 1:

        cout << "You Chose to enter user data" << endl << endl;
        EditInformation(db, userID);
        break;
    case 2:

        cout << "You Chose to view Products menu" << endl;
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
        ClearScreen();
        cout << "You Chose to log out" << endl;
        SignIn(db);
        break;
    default:

        cout << "Please Only Select A Number From The Menu" << endl;
        cout << endl;
        Greeting(db, userID);

    }

}





