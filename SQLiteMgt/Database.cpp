#include "Database.hpp"

sqlite3* Database::_db;
sqlite3_stmt* Database::_result;
string Database::_errorMessage;
map<string, int> Database::_columns;

// Opens a connection with the given database or creates a new one under that name
bool Database::Open(const char* databaseName)
{
	// Check if there is already a connection to another database and close it if there is
	if (_db) Close();

	// Open a connection and check if it was successful
	if (sqlite3_open(databaseName, &_db) != SQLITE_OK)
	{
		// Close the failed connection
		Close();

		return false;
	}
	else return true;
}

// Closes the connection to the database
void Database::Close()
{
	// Check if there is a connection to close
	if (!_db) return;

	// Free the memory
	FreeMemory();

	// Close the connection
	sqlite3_close(_db);

	// Set the pointer to null
	_db = nullptr;

	return;
}

// Executes the SQL-Query and returns true if successfully executed
bool Database::Execute(const string& query)
{
	// Check for a database connection
	if (!_db)
	{
		_errorMessage = "No open database connection";

		return false;
	}

	sqlite3_stmt* result;

	// Prepare query and check the resultcode
	if (sqlite3_prepare_v2(_db, query.c_str(), query.size(), &result, NULL) == SQLITE_OK)
	{
		if (sqlite3_step(result) == SQLITE_DONE)
		{
			// Finalize the prepared query
			sqlite3_finalize(result);

			return true;
		}
	}

	// Get the error message
	_errorMessage = sqlite3_errmsg(_db);

	// Finalize the prepared query
	sqlite3_finalize(result);

	return false;
}

// Executes a count-query and returns the result
// If an error occures the result is -1
int Database::Count(const string& query)
{
	// Check for a database connection
	if (!_db)
	{
		_errorMessage = "No open database connection";

		return -1;
	}

	sqlite3_stmt* result;

	// Prepare query and check the resultcode
	if (sqlite3_prepare_v2(_db, query.c_str(), query.size(), &result, NULL) == SQLITE_OK)
	{
		// Execute the first step
		int resultCode = sqlite3_step(result);

		int count = 0;

		// Check the result code
		if (resultCode == SQLITE_ROW)
		{
			count = sqlite3_column_int(result, 0);
		}

		// Execute the next step to check if the query was valid
		resultCode = sqlite3_step(result);

		// The query was invalid if the result code is anything else than SQLITE_DONE  
		if (resultCode != SQLITE_DONE)
		{
			count = -1;

			_errorMessage = "Invalid query";
		}

		// Finalize the prepared query
		sqlite3_finalize(result);

		return count;
	}

	// Get the error message
	_errorMessage = sqlite3_errmsg(_db);

	// Finalize the prepared query
	sqlite3_finalize(result);

	return -1;
}

// Executes the SQL-Query and returns true if successfully executed
// Use FetchRow() afterwards to work with the data
bool Database::FetchData(const string& query)
{
	// Check for a database connection
	if (!_db)
	{
		_errorMessage = "No open database connection";

		return false;
	}

	// Check if there is a query-result still waiting to be finalized
	if (_result)
	{
		_errorMessage = "Memory not free";

		return false;
	}

	// Check if the query was successfully prepared
	if (sqlite3_prepare_v2(_db, query.c_str(), query.size(), &_result, NULL) != SQLITE_OK)
	{
		// Get the error message
		_errorMessage = sqlite3_errmsg(_db);

		// Finalize the prepared query
		sqlite3_finalize(_result);

		// Set the pointer to null
		_result = nullptr;

		return false;
	}

	// Empty the map
	map<string, int>().swap(_columns);

	int i = 0;

	// Get all column names and their index
	while (true)
	{
		const char *columnName = sqlite3_column_name(_result, i);

		if (!columnName) break;

		_columns.insert(make_pair(columnName, i++));
	}

	return true;
}

// Fetches a row of data and returns true as long as a new row is found
bool Database::FetchRow()
{
	// Check for a database connection
	if (!_db)
	{
		_errorMessage = "No open database connection";

		return false;
	}

	// Check if there is a query-result to work with
	if (!_result)
	{
		_errorMessage = "No data to fetch";

		return false;
	}

	int resultCode = sqlite3_step(_result);

	switch (resultCode)
	{
	case SQLITE_ROW:
		return true;
		break;
	case SQLITE_DONE:
		return false;
		break;
	case SQLITE_BUSY:
		_errorMessage = "Database is busy";
		return false;
		break;
	default:
		_errorMessage = sqlite3_errmsg(_db);
		return false;
		break;
	}
}

// Frees the memory of the database so the next query can be executed
void Database::FreeMemory()
{
	// Finalize the statement
	if (_result) sqlite3_finalize(_result);

	// Reset the pointer
	_result = nullptr;

	// Empty the map
	map<string, int>().swap(_columns);

	// Empty the error message
	_errorMessage = "";
}

// Returns the value of the given column as an integer
int Database::GetInteger(const string columnName)
{
	// Check for a database connection and a result to work with
	if (_db && _result)
	{
		map<string, int>::iterator i;

		// Try to find the given column
		i = _columns.find(columnName);

		// Check if a column was found
		if (i != _columns.end())
		{
			// Get the index of the column
			int index = i->second;

			return sqlite3_column_int(_result, index);
		}
	}

	// Return a default value if column was not found or there was no data
	return 0;
}

// Returns the value of the given column as a double
double Database::GetDouble(const string columnName)
{
	// Check for a database connection and a result to work with
	if (_db && _result)
	{
		map<string, int>::iterator i;

		// Try to find the given column
		i = _columns.find(columnName);

		// Check if a column was found
		if (i != _columns.end())
		{
			// Get the index of the column
			int index = i->second;

			return sqlite3_column_double(_result, index);
		}
	}

	// Return a default value if column was not found or there was no data
	return 0;
}

// Returns the value of the given column as a boolean value
bool Database::GetBoolean(const string columnName)
{
	// Check for a database connection and a result to work with
	if (_db && _result)
	{
		map<string, int>::iterator i;

		// Try to find the given column
		i = _columns.find(columnName);

		// Check if a column was found
		if (i != _columns.end())
		{
			// Get the index of the column
			int index = i->second;

			int result = sqlite3_column_int(_result, index);

			return result == 1 ? true : false;
		}
	}

	// Return a default value if column was not found or there was no data
	return false;
}

// Returns the value of the given column as a string
string Database::GetString(const string columnName)
{
	// Check for a database connection and a result to work with
	if (_db && _result)
	{
		map<string, int>::iterator i;

		// Try to find the given column
		i = _columns.find(columnName);

		// Check if a column was found
		if (i != _columns.end())
		{
			// Get the index of the column
			int index = i->second;

			const unsigned char *result = sqlite3_column_text(_result, index);

			return result ? (const char*)result : "";
		}
	}

	// Return a default value if column was not found or there was no data
	return "";
}

// Returns the last error message
string Database::GetErrorMessage()
{
	return _errorMessage;
}