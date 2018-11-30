#pragma once

#include "sqlite3.h"
#include <string>
#include <map>

//https://www.sqlite.org/c3ref/funclist.html

using namespace std;

class Test
{
public:
	int RowId;
	int Id;
	string Name;
};

class Database
{
public:
	// Opens a connection with the given database or creates a new one under that name
	static bool Open(const char* databaseName);
	
	// Closes the connection to the database
	static void Close();

	// Executes the SQL-Query and returns true if successfully executed
	static bool Execute(const string& query);

	// Executes the SQL-Query and returns true if successfully executed
	// Use FetchRow() afterwards to work with the data
	static bool FetchData(const string& query);

	// Fetches a row of data and returns true as long as a new row is found
	static bool FetchRow();

	// Frees the memory of the database so the next query can be executed
	static void FreeMemory();

	// Returns the value of the given column as an integer
	static int GetInteger(const string columnName);

	// Returns the value of the given column as a double
	static double GetDouble(const string columnName);

	// Returns the value of the given column as a boolean value
	static bool GetBoolean(const string columnName);

	// Returns the value of the given column as a string
	static string GetString(const string columnName);

	// Executes a count-query and returns the result
	// If an error occures the result is -1
	static int Count(const string& query);
	
	// Returns the last error message
	static string GetErrorMessage();
private:
	static sqlite3* _db;
	static sqlite3_stmt* _result;
	static string _errorMessage;
	static map<string, int> _columns;
};