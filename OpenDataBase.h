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
	int req = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, adress TEXT)", NULL, NULL, NULL);
	checkForError(db, req);
	if (req == 1)
	{
		cout << "Table does not exist, thus a new table was created." << endl;
	}
	cout << "Database " + dbFileName + " opened successfully" << endl;
	return db;
}
