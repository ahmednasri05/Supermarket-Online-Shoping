#pragma once

#include <iostream>
#include "sqlite-header/sqlite3.h"
#include <string>

using namespace std;

/*int checkForError(sqlite3* db, int req)
{
	if (req != SQLITE_OK)
	{
		cout << "Error: " << sqlite3_errmsg(db) << endl;
		return 1;
	}
	return 0;
}*/