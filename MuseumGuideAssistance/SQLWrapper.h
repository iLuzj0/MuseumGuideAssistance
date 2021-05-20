#pragma once
#include <iostream>
#include <JSON/json.hpp>
#include <mysql.h>

class SQLWrapper
{
	private:
		nlohmann::json exibitData;
		nlohmann::json exitData;
		int qstate;
		MYSQL* conn;
		MYSQL_ROW row;
		MYSQL_RES* res;

	public:
		SQLWrapper(const char* server, const char* user, const char* password, const char* database, int port);
		nlohmann::json SQLGetExibitsIntoJSON(std::string table, std::string tagID);
		nlohmann::json SQLGetExitsInfo(std::string tagID);
};

