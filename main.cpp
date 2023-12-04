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

sqlite3* createConnection() {
    sqlite3* db;
    sqlite3_open("users1.db", &db);
    int req = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, password TEXT, phone TEXT, location TEXT)", NULL, NULL, NULL);
    checkForError(db, req);
    cout << "Database opened successfully" << endl;
    return db;
}

int main() {
    sqlite3* db;
    db = createConnection();
    Greeting(db);
    return 0;
}