#include "SQLWrapper.h"

SQLWrapper::SQLWrapper(const char* server, const char* user, const char* password, const char* database, int port) {
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, server, user, password, database, port, NULL, 0);

	if (conn) 
		puts("Successful connection to database!");
	else 
		puts("Connection to dabasabe has failed");
}

nlohmann::json SQLWrapper::SQLGetExibitsIntoJSON(std::string tagID) {
	if (conn) {
		std::string query = "SELECT * FROM exibits";
		const char* q = query.c_str();

		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				if (row[0] == tagID) {
					exibitData["Exibit"] = row[1];
					exibitData["Autor"] = row[2];
					exibitData["Data"] = row[3];
					exibitData["Opis"] = row[4];
				}
			}
		}
	}
	return exibitData;
}

nlohmann::json SQLWrapper::SQLGetExitsInfo(std::string tagID)
{
	if (conn) {
		std::string query = "SELECT exits.ExitID, exits.Exits, exibits.Exibit FROM exibits INNER JOIN exits ON exibits.ExitID=exits.ExitID";
		const char* q = query.c_str();
		std::string Exibits;
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				if (row[0] == tagID) {
					exitData["Exits"] = row[1];
					Exibits.append(row[2]);
					Exibits.append("|");
				}
			}
		}
		exitData["Exibits"] = Exibits;
	}
	return exitData;
}

