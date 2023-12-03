#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "../sqlite-header/sqlite3.h"
#include "check_conn_error.h"
#include "../models/model_users.h"

void saveUser(sqlite3* db, Person user)
{
	string query = "INSERT INTO users (name , password, phone, location) VALUES ('"+user.Name+"', '"+user.Password+"', '"+user.PhoneNumber+"', '"+user.Location+"');";

	int req = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
	checkForError(db, req);
}