#pragma once
#include <iostream>


class CTablica
{
protected:
	//metody pomocnicze do algorytmow sortowania

	/*
	Metoda pomocnicza ustawiajaca dla i-tego wezla rekurencyjnie wlasnosc kopca, czyli
	dla i-ty rodzic musi miec wartosc wieksza od swoich dzieci
	@param Tab przysylana tablica do posortowania
	@param heap_size rozmiar kopca, de facto rozmiar tablicy
	@param i ktory wezel ma byc sprawdzony pod katem wlasnosci kopca
	@param numberOfComparisons liczba porownan do zliczania
	@param numberOfInversions liczba zamian do zliczania
	*/
	void heapify(int* Tab, int heap_size, int i, unsigned long long& numberOfComparisons, unsigned long long& numberOfInversions);

	/*
	Metoda rekursywna budujaca kopiec za pomoca heapify
	@param Tab przysylana tablica do posortowania
	@param heap_size rozmiar kopca, de facto rozmiar tablicy
	@param numberOfComparisons liczba porownan do zliczania
	@param numberOfInversions liczba zamian do zliczania
	*/
	void buildHeap(int* Tab, int heap_size, unsigned long long& numberOfComparisons, unsigned long long& numberOfInversions);

	/*
	Metoda pomocnicza przypisujaca a=b i b=a
	@param a pierwsza liczba do zamiany
	@param b druga liczba do zamiany
	*/
	void swap(int& a, int& b);

public:

	//kostruktor
	CTablica() {}

	/*
	Metoda sortujaca dane za pomoca quicksort Lomuto
	@param Tab przysylana tablica do posortowania
	@param low pierwszy index w tablicy
	@param top ostatni index w tablicy
	@param numberOfComparisons liczba porownan do zliczania
	@param numberOfInversions liczba zamian do zliczania
	*/

	int Lomuto_Quicksort(int* Tab, int low, int top, unsigned long long &numberOfComparisons, unsigned long long &numberOfInversions);

	/*
	Metoda sortujaca dane za pomoca kopca
	@param Tab przysylana tablica do posortowania
	@param heap_size rozmiar kopca, de facto rozmiar tablicy
	@param numberOfComparisons liczba porownan do zliczania
	@param numberOfInversions liczba zamian do zliczania	
	*/
	void HeapSort(int* Tab, int heap_size, unsigned long long& numberOfComparisons, unsigned long long& numberOfInversions);

	
	/*
	Metoda sortujaca dane za pomoca quicksort Hoare
	@param Tab przysylana tablica do posortowania
	@param low pierwszy index w tablicy
	@param top ostatni index w tablicy
	@param numberOfComparisons liczba porownan do zliczania
	@param numberOfInversions liczba zamian do zliczania
	*/

	int Hoare_Quicksort(int* Tab, int low, int top, unsigned long long &numberOfComparisons, unsigned long long &numberOfInversions);

	/*
	Metoda sortujaca dane algorytmem babelkowym dwukierunkowym
	@param Tab przysylana tablica do posortowania
	@param size rozmiar tablicy
	@param numberOfComparisons liczba porownan do zliczania
	@param numberOfInversions liczba zamian do zliczania
	*/
	void cocktailSort(int* Tab, int size, unsigned long long& numberOfComparisons, unsigned long long & numberOfInversions);

	//destruktor
	~CTablica(void);
};


