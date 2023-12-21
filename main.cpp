#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "api_users.h"
#include "model_users.h"
#include "database_conn.h"
#include "OpenDataBase.h"
#include "check_conn_error.h"
#include "sqlite-header/sqlite3.h"
#include <string>

using namespace std;



int main() {
    //Create Variable of type sqlite3
    sqlite3* db;
    //Open database wich means to create db tables if not exist
    db = openDataBase("users1.db");
    Greet(db);
    //Main Menu funciton
    //Greeting(db);

    return 0;
}