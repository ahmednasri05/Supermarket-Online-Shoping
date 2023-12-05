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
    sqlite3* db;
    db = openDataBase("users1.db");
    Greeting(db);
    return 0;
}