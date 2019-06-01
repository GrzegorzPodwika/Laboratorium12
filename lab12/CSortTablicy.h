#pragma once
#include <iostream>
#include <Windows.h>
#include <random>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "CTablica.h"
#include "libExceptions.h"


class CSortTablicy :public CTablica
{
	//argumenty glowne do przechowywania danych
	int *Tab;
	int low;
	int top;
	int numberOfComparisons;
	int numberOfInversions;
	std::fstream outFile;

public:

	//kostruktor z lista inicjalizujaca
	CSortTablicy() : Tab{ nullptr }, low{}, top{}, numberOfComparisons{}, numberOfInversions{} 
	{}

	//metoda otwierajaca plik do zapisu
	void openFile();

	//metoda wyswietlajaca glowne menu i zarzadzajaca obiektem
	void menu();

	/*
	Metoda pomocnicza wyswietlajaca menu jaka wersje sortowania chce wybrac uzytkownik
	@return ktora metoda sortowania 1,2,3 czy 4
	*/
	int whichSortMethod();

	/*
	Pomocnicza metoda wyswietlajaca tablice
	@param Tab tablica do wyswietlenia
	@param size rozmiar tablicy do wyswietlenia
	*/
	void showTable(int*Tab, int size);

	/*
	Metoda zajmujaca sie wstawieniem danych od uzytkownika i posortowaniem ich jednym z 4 algorytmow
	*/
	void insertAndSortUserData();

	/*
	Metoda generujaca ilosc podana przez uzytkownika losowych liczb i sortujaca je jednym z 4 algorytmow
	*/
	void generateAndSortRandomNumbers();
	
	/*
	Metoda zapisujaca dzialanie poszczegolnego algorytmu do pliku
	*/
	void showSortMethodsInAction();

	/*
	Metoda pomocnicza zapisujaca dane do pliku wyjsciowego
	@param nameOfMethod nazwa metody
	@param size rozmiar tablicy posortowanej
	@param typeOfTable typ tablicy, np. posortowana malejaco
	@param numberOfComparisons liczba zliczonych porownan 
	@param numberOfInversions liczba zliczonych przypisan
	*/
	void saveDataToFile(std::string nameOfMethod, int size, std::string typeOfTable, int numberOfComparisons, int numberOfInversions);

	/*
	Metoda mieszajaca niektore wartosci w tablicy, w naszym przypadku 10%
	@param Tab tablica do pomieszania
	@param size rozmiar tablicy
	*/
	void shakeTable(int*Tab, int size);

	/*
	Metoda pomocnicza resetujaca liczbe porownan i przestawien
	*/
	void resetNumberOfComparisonsAndInversions();

	/*
	Metoda pomocnicza wstawiajaca liczby uzytkownika do tablicy
	@paran Tab tablica do ktorej wstawiane zostaja liczby uzytkownika
	@param size rozmiar tablicy
	*/
	void insertUserNumbersToTable(int* Tab, int size);

	/*
	Metoda pomocnicza wstawiajaca losowe liczby do tablicy
	@paran Tab tablica do ktorej wstawiane zostaja losowe wartosci
	@param size rozmiar tablicy
	*/
	void insertRandomNumbersToTable(int* Tab, int size);

	//destruktor
	~CSortTablicy();
};


