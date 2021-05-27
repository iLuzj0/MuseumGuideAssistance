#pragma once
#include <iostream>
#include <JSON/json.hpp>
#include <mysql.h>

/// @brief Klasa umożliwiająca komunikacje z bazą danych
/// @author Dominik Tekiela
/// @date 27.05.2021
/// @warning Twoja baza danych musi zostać zabezpieczona hasłem !
class SQLWrapper
{
	private:
		/// Informacjena temat eksponatu
		nlohmann::json exibitData; 
		
		/// Informacje na temat pokoju
		nlohmann::json exitData; 

		/// Stan komunikacji z bazą danych
		int qstate; 

		/// Komunikacja z bazą danych
		MYSQL* conn; 

		/// Rezultat przeprowadzenia zapytania na bazie danych
		MYSQL_RES* res;

		/// Wiersz wyciągniety z zapytania, które jest w zmiennej res
		MYSQL_ROW row;

	public:
		/// @brief Konstruktor, który łączy nas z bazą danych
		/// Połącznie jest realizowane za pomocą podanych przez użytkownika aplikacji danych.
		/// Jeśli połączenie się nie powiedzie otrzymamy o tym kominikat, w przypadku powodzenia program ruszy do przodu.
		/// @param server Nazwa serwera
		/// @param user Nazwa użytkownika
		/// @param password Hasło użytkownika
		/// @param database Jaka baza danych z serwera zostanie użyta
		/// @param port Na jakim porcie będziemy operować
		SQLWrapper(const char* server, const char* user, const char* password, const char* database, int port);

		/// @brief Metoda, która na podstawie ID znalezionego tagu zwraca nam informacje o eksponacie, który stoi za danym ID.
		/// Do osiągniecia tego rezultatu na bazie danych przeprowadzone jest zapytanie: SELECT * FROM exibits, zwracające wszystko co potrzebujemy.
		/// Następnie dana kolumna tabeli jest umieszczana w odpowiedni opis zmiennej JSON.
		/// @param tagID Zmienna typu string, która przekazuje do bazy danych w zapytaniu ID taga. Na podstawie ID ustalane są informacje na temat eksponatów
		/// @return Zwraca zmienną typu JSON, która zawiera w sobie informacje na temat eksponatu - nazwe autora, nazwe eksponatu, opis eksponatu, date utworzenia
		nlohmann::json SQLGetExibitsIntoJSON(std::string tagID);

		/// @brief Metoda, która na podstawie ID taga opisującego pokój zwraca ilość wyjść oraz ilość eksponatów w pokoju.
		/// Do osiągniecia tego rezultatu na bazie danych przeprowadzone jest zapytanie: SELECT exits.ExitID, exits.Exits, exibits.Exibit FROM exibits INNER JOIN exits ON exibits.ExitID=exits.ExitID.
		/// Następnie dana kolumna tabeli jest umieszczana w odpowiedni opis zmiennej JSON.
		/// @param tagID Zmienna typu string, która przekazuje do bazy danych w zapytaniu ID taga. Na podstawie ID ustalane wyjścia i eksponaty w pokoju
		/// @return Zwraca zmienna typu JSON, która zawiera w sobie informacjena temat pokoju - wyjść i eksponatów w pokoju
		nlohmann::json SQLGetExitsInfo(std::string tagID);
};

