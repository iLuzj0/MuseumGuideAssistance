#pragma once
#include <iostream>
#include <JSON/json.hpp>
#include <mysql.h>

/// @brief Klasa umożliwiająca komunikacje z bazą danych
/// @author Dominik Tekiela
/// @date 27.05.2021
class SQLWrapper
{
	private:
		/// Informacjena temat eksponatu
		nlohmann::json exibitData; 
		
		/// Informacje na temat pokoju
		nlohmann::json exitData; 

		/// Komunikacja z bazą danych
		int qstate; 
		/// Komunikacja z bazą danych
		MYSQL* conn; 
		/// Komunikacja z bazą danych
		MYSQL_ROW row; 
		/// Komunikacja z bazą danych
		MYSQL_RES* res; 

	public:
		/// @brief Konstruktor, który łączy nas z bazą danych
		/// @param server Nazwa serwera
		/// @param user Nazwa użytkownika
		/// @param password Hasło użytkownika
		/// @param database Jaka baza danych z serwera zostanie użyta
		/// @param port Na jakim porcie będziemy operować
		SQLWrapper(const char* server, const char* user, const char* password, const char* database, int port);

		/// @brief Metoda, która na podstawie ID znalezionego tagu zwraca nam informacje o eksponacie, który stoi za danym ID
		/// @param tagID Zmienna typu string, która przekazuje do bazy danych w zapytaniu ID taga. Na podstawie ID ustalane są informacje na temat eksponatów
		/// @return Zwraca zmienną typu JSON, która zawiera w sobie informacje na temat eksponatu - nazwe autora, nazwe eksponatu, opis eksponatu, date utworzenia
		nlohmann::json SQLGetExibitsIntoJSON(std::string tagID);

		/// @brief Metoda, która na podstawie ID taga opisującego pokój zwraca ilość wyjść oraz ilość eksponatów w pokoju
		/// @param tagID Zmienna typu string, która przekazuje do bazy danych w zapytaniu ID taga. Na podstawie ID ustalane wyjścia i eksponaty w pokoju
		/// @return Zwraca zmienna typu JSON, która zawiera w sobie informacjena temat pokoju - wyjść i eksponatów w pokoju
		nlohmann::json SQLGetExitsInfo(std::string tagID);
};

