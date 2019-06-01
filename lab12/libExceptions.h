#pragma once

#include <fstream>
#include <exception>
#include <string>
#include <iostream>

namespace MyRuntimeExceptions {

	/*
	Klasa obslugujaca blad otwarcia pliku
	*/
	class FileOpenException : public std::runtime_error {
	public:
		FileOpenException() : runtime_error("Nie mozna otworzyc pliku")
		{}

		FileOpenException(std::string msg) : runtime_error(msg.c_str())
		{}

	};

	/*
	Klasa obslugujaca blad w odczycie danych z pliku
	*/
	class FileReadException : public std::runtime_error
	{
	public:

		FileReadException() : runtime_error("Blad w odczycie danych z pliku")
		{}

		FileReadException(std::string msg) : runtime_error(msg.c_str())
		{}
	};

	/*
	Klasa obslugujaca blad zaalokowania pamieci
	*/
	class BadAllocateException : public std::runtime_error
	{
	public:
		BadAllocateException() : runtime_error("Nie udalo sie zaalokowac pamieci")
		{}

		BadAllocateException(std::string msg) : runtime_error(msg.c_str())
		{}

	};

}

using namespace std;

template <typename T>
T sprawdzLiczbe()
{
	T liczba;
	int ok, podglad;
	do
	{
		ok = 1;
		cin >> liczba;
		if (cin.fail())                    //jesli wczytanie sie nie powiodlo
		{
			ok = 0;
			cin.clear();                   //czysci flage bledu strumienia
			cin.ignore(INT_MAX, '\n');     //usuwa wszystkie znaki z buforu strumienia aż do napotkania znaku '\n' 

		}
		else
		{
			while ((podglad = cin.get()) != '\n')  //cin.get() - pobierz znak ze strumienia 
			{
				if (podglad != ' ')            // Szukanie zbędnych danych w strumieniu
				{
					ok = 0;
					cin.ignore(INT_MAX, '\n'); // czyszczenie strumienia
					break;
				}
			}
		}
		if (ok == 0) cout << "\n Nie podano wlasciwego typu danych. Sprobuj wpisac ponownie...\n\n ";
	} while (ok == 0);
	return liczba;
}



/*
Funkcja tworzaca tablice jednowierszowa dynamiczna
@param size rozmiar tablicy do utworzenia
@return adres tablicy dynamicznej
*/
int* createTable(int size);