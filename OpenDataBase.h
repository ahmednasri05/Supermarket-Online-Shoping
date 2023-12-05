#pragma once

#include <iostream>
#include "sqlite-header/sqlite3.h"
#include <string>
#include "check_conn_error.h"

using namespace std;

sqlite3* openDataBase(string dbFileName)
{
	sqlite3* db;
	sqlite3_open(dbFileName.c_str(), &db);
	int req = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, password TEXT, phone TEXT, location TEXT)", NULL, NULL, NULL);
    checkForError(db, req);
	if (req == 1)
	{
		cout << "users table does not exist, thus a new table was created." << endl;
	}
	int reqProducts = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS products (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, price INTEGER, code TEXT, category TEXT, production_date TEXT, expiration_date TEXT)", NULL, NULL, NULL);
    checkForError(db, reqProducts);
	if (req == 1)
	{
		cout << "products table does not exist, thus a new table was created." << endl;
	}
	cout << "Database " + dbFileName + " opened successfully" << endl;
	return db;
}
