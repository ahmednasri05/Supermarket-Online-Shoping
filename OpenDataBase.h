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

	//Users Table
	int req = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, password TEXT, phone TEXT, location TEXT)", NULL, NULL, NULL);
    checkForError(db, req);
	if (req == 1)
	{
		cout << "users table does not exist, thus a new table was created." << endl;
	}

	//Products Table
	int reqProducts = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS products (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, price INTEGER, quantity INTEGER, code TEXT, category TEXT, production_date TEXT, expiration_date TEXT)", NULL, NULL, NULL);
    checkForError(db, reqProducts);
	if (reqProducts == 1)
	{
		cout << "products table does not exist, thus a new table was created." << endl;
	}

	//Categories Table
	int reqCategory = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS categories (id INTEGER PRIMARY KEY AUTOINCREMENT, category TEXT)", NULL, NULL, NULL);
    checkForError(db, reqCategory);
	if (reqCategory == 1)
	{
		cout << "categories table does not exist, thus a new table was created." << endl;
	}

	//Orders Table
	int reqOrder = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY AUTOINCREMENT, item_id INTEGER, user_id INTEGER, code TEXT, quantity INTEGER, product_name TEXT, product_price INTEGER, purchased INTEGER CHECK (purchased IN (0, 1)) DEFAULT 0)", NULL, NULL, NULL);
    checkForError(db, reqOrder);
	if (reqOrder == 1)
	{
		cout << "orders table does not exist, thus a new table was created." << endl;
	}
	cout << "Database " + dbFileName + " opened successfully" << endl;
	return db;
}
