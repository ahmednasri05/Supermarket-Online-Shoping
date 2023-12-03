#include <iostream>
#include "../sqlite-header/sqlite3.h"
#include "check_conn_error.h"
using namespace std;

// sqlite3* createConnection() {
//     sqlite3* db;
// 	sqlite3_stmt* stmt;
// 	sqlite3_open("users1.db", &db);
// 	int req = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, password TEXT, phone TEXT, location TEXT)", NULL, NULL, NULL);
// 	checkForError(db, req);
// 	cout << "Database opened successfully" << endl;
//     return db;
// }