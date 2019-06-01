#include "CSortTablicy.h"

using namespace std;


void CSortTablicy::menu()
{
	int choice{};
	cout << "MENU " << endl;
	cout << "*******************************************" << endl;
	cout << "Podaj typ metody wprowadzania danych: " << endl << endl;
	cout << "1. Wprowadzenie zadaniej liczby elementow z klawiatury " << endl;
	cout << "2. Losowanie zadanej liczby elementow " << endl;
	cout << "3. Wybor i ilustracja dzialania przykladowych metod sortowania dla zadanej liczby elementow " << endl;
	cout << "*******************************************" << endl;

	choice = sprawdzLiczbe<int>();

	switch (choice)
	{
	case 1:
		insertAndSortUserData();
		break;

	case 2:
		generateAndSortRandomNumbers();
		break;

	case 3:
		showSortMethodsInAction();
		break;

	default:
		cout << "Niepoprawny wybór. Koniec programu";
		exit(0);
		break;
	}
}


void CSortTablicy::insertAndSortUserData()
{
	int numberOfElements{};
	int sortMethod{};

	//wczytanie ilosci elementow
	cout << "Podaj ilosc elementow ktore chcesz wprowadzic: " << endl;
	numberOfElements = sprawdzLiczbe<int>();

	//stworzenie tablicy dynamicznej o zadanej wielkosci i przypisanie rozmiaru do top'a
	Tab = createTable(numberOfElements);
	top = numberOfElements;

	//wczytanie liczb od uzytkownika do tablicy oraz metody sortowania
	insertUserNumbersToTable(Tab, top);
	sortMethod = whichSortMethod();

	switch (sortMethod)
	{
	case 1:
		cocktailSort(Tab, top, numberOfComparisons, numberOfInversions);
		break;

	case 2:
		Lomuto_Quicksort(Tab, low, top - 1, numberOfComparisons, numberOfInversions);
		break;

	case 3:
		Hoare_Quicksort(Tab, low, top - 1, numberOfComparisons, numberOfInversions);
		break;

	case 4:
		HeapSort(Tab, top, numberOfComparisons, numberOfInversions);
		break;

	default:
		cout << "Niepoprawny wybor. Koniec programu";
		exit(0);
		break;
	}

	cout << "Ilosc porownan: " << numberOfComparisons << endl;
	cout << "Ilosc przestwaien: " << numberOfInversions << endl;
	cout << "Oto posortowana tablica: " << endl << endl;
	showTable(Tab, top);

	delete[] Tab;
}


void CSortTablicy::openFile()
{
	string name_file;
	cout << "Podaj nazwe pliku do ktorego chcesz zapisywac dane: " << endl;
	cin >> name_file;

	outFile.open(name_file.c_str(), ios::out);
	if (!outFile.good())
	{
		//skorzystanie z wyjatkow
		throw MyRuntimeExceptions::FileOpenException("Nie mozna otworzyc pliku wejsciowego");
	}

	outFile << setw(20) << "Nazwa metody" << setw(20) << "Dlugosc tablicy" << setw(40) << "Rodzaj tablicy" << setw(20) << "Liczba porownan" << setw(20) << "Liczba przestawien" << endl;
}


int CSortTablicy::whichSortMethod()
{	
	//pomocnicza metoda z malym menu
	int choice{};
	cout << endl;
	cout << "SORT MENU " << endl;
	cout << "*******************************************" << endl;
	cout << "Podaj typ metody sortowania danych: " << endl << endl;
	cout << "1. Sortowanie babelkowe (cocktail-sort)" << endl;
	cout << "2. Quicksort - Lomuto " << endl;
	cout << "3. Quicksort - Hoare'a " << endl;
	cout << "4. Heapsort " << endl;
	cout << "*******************************************" << endl;

	choice = sprawdzLiczbe<int>();

	return choice;
}


void CSortTablicy::showTable(int* Tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << Tab[i] << " ";

		if ((i + 1) % 20 == 0)
			cout << endl;
	}

	cout << endl;
}



void CSortTablicy::generateAndSortRandomNumbers()
{
	//zmienne pomocnicze
	int numberOfElements{};
	int sortMethod{};

	//wczytanie rozmiaru tablicy
	cout << "Podaj ilosc elementow do wylosowania: " << endl;
	numberOfElements = sprawdzLiczbe<int>();

	//stworzenie tablicy dynamicznej o zadanej wielkosci i przypisanie rozmiaru do top'a
	Tab = createTable(numberOfElements);
	top = numberOfElements;

	//wstawienie losowych liczb do tablicy
	insertRandomNumbersToTable(Tab, top);

	cout << "Wylosowane liczby to: " << endl;
	showTable(Tab, top);

	sortMethod = whichSortMethod();

	switch (sortMethod)
	{
	case 1:
		cocktailSort(Tab, top, numberOfComparisons, numberOfInversions);
		break;

	case 2:
		Lomuto_Quicksort(Tab, low, top - 1, numberOfComparisons, numberOfInversions);
		break;

	case 3:
		Hoare_Quicksort(Tab, low, top - 1, numberOfComparisons, numberOfInversions);
		break;

	case 4:
		HeapSort(Tab, top, numberOfComparisons, numberOfInversions);
		break;

	default:
		cout << "Zly wybor. Koniec programu";
		exit(0);
		break;
	}

	cout << "Ilosc porownan: " << numberOfComparisons << endl;
	cout << "Ilosc przestwaien: " << numberOfInversions << endl;
	cout << "Oto posortowana tablica" << endl;
	showTable(Tab, top);

	delete[] Tab;
}


void CSortTablicy::showSortMethodsInAction()
{
	//zmienne pomocnicze
	int numberOfElements{};
	int sortMethod{};

	//wczytanie rozmiaru tablicy
	cout << "Podaj ilosc elementow: " << endl;
	numberOfElements = sprawdzLiczbe<int>();

	//stworzenie tablicy dynamicznej o zadanej wielkosci i przypisanie rozmiaru do top'a
	Tab = createTable(numberOfElements);
	top = numberOfElements;

	//wstawienie losowych wartosci do tablicy
	insertRandomNumbersToTable(Tab, top);

	//wczytanie, jaka metoda posortowan dane
	sortMethod = whichSortMethod();

	//proba otwarcia pliku do zapisu
	try
	{
		openFile();
	}
	catch (const std::exception & e)
	{
		cerr << e.what();
		exit(0);
	}

	switch (sortMethod)
	{
	case 1:
	{
		//1 przypadek z losowymi wartosciami
		cocktailSort(Tab, top, numberOfComparisons, numberOfInversions);
		saveDataToFile("Cocktail sort", top, "Tablica z losowymi liczbami", numberOfComparisons, numberOfInversions);
		resetNumberOfComparisonsAndInversions();

		//2 przypadek z posortowana tablica
		cocktailSort(Tab, top, numberOfComparisons, numberOfInversions);
		saveDataToFile("Cocktail sort", top, "Tablica posortowana rosn¹ca", numberOfComparisons, numberOfInversions);
		resetNumberOfComparisonsAndInversions();

		//3 przypadek z tablica posortowana malejaco
		reverse(Tab, Tab + top);
		cocktailSort(Tab, top, numberOfComparisons, numberOfInversions);
		saveDataToFile("Cocktail sort", top, "Tablica posortowana malej¹co", numberOfComparisons, numberOfInversions);
		resetNumberOfComparisonsAndInversions();

		//4 przypadek z tablica czesciowo nieuporzadkowana
		shakeTable(Tab, top);
		cocktailSort(Tab, top, numberOfComparisons, numberOfInversions);
		saveDataToFile("Cocktail sort", top, "Tablica czêsciowo uporz¹dkowana", numberOfComparisons, numberOfInversions);

	}
	break;

	case 2:
	{
		//1 przypadek z losowymi wartosciami
		Lomuto_Quicksort(Tab, low, top - 1, numberOfComparisons, numberOfInversions);
		saveDataToFile("Quicksort - Lomuto", top, "Tablica z losowymi liczbami", numberOfComparisons, numberOfInversions);
		resetNumberOfComparisonsAndInversions();

		//2 przypadek z posortowana tablica
		Lomuto_Quicksort(Tab, low, top - 1, numberOfComparisons, numberOfInversions);
		saveDataToFile("Quicksort - Lomuto", top, "Tablica posortowana rosn¹ca", numberOfComparisons, numberOfInversions);
		resetNumberOfComparisonsAndInversions();

		//3 przypadek z tablica posortowana malejaco
		reverse(Tab, Tab + top);
		Lomuto_Quicksort(Tab, low, top - 1, numberOfComparisons, numberOfInversions);
		saveDataToFile("Quicksort - Lomuto", top, "Tablica posortowana malej¹co", numberOfComparisons, numberOfInversions);
		resetNumberOfComparisonsAndInversions();

		//4 przypadek z tablica czesciowo nieuporzadkowana
		shakeTable(Tab, top);
		Lomuto_Quicksort(Tab, low, top-1, numberOfComparisons, numberOfInversions);
		saveDataToFile("Quicksort - Lomuto", top, "Tablica czêsciowo uporz¹dkowana", numberOfComparisons, numberOfInversions);
	}
	break;

	case 3:
	{
		//1 przypadek z losowymi wartosciami
		Hoare_Quicksort(Tab, low, top-1, numberOfComparisons, numberOfInversions);
		saveDataToFile("Quicksort - Hoare'a", top, "Tablica z losowymi liczbami", numberOfComparisons, numberOfInversions);
		resetNumberOfComparisonsAndInversions();

		//2 przypadek z posortowana tablica
		Hoare_Quicksort(Tab, low, top-1, numberOfComparisons, numberOfInversions);
		saveDataToFile("Quicksort - Hoare'a", top, "Tablica posortowana rosn¹ca", numberOfComparisons, numberOfInversions);
		resetNumberOfComparisonsAndInversions();

		//3 przypadek z tablica posortowana malejaco
		reverse(Tab, Tab + top);
		Hoare_Quicksort(Tab, low, top-1, numberOfComparisons, numberOfInversions);
		saveDataToFile("Quicksort - Hoare'a", top, "Tablica posortowana malej¹co", numberOfComparisons, numberOfInversions);
		resetNumberOfComparisonsAndInversions();

		//4 przypadek z tablica czesciowo nieuporzadkowana
		shakeTable(Tab, top);
		Hoare_Quicksort(Tab, low, top-1, numberOfComparisons, numberOfInversions);
		saveDataToFile("Quicksort - Hoare'a", top, "Tablica czêsciowo uporz¹dkowana", numberOfComparisons, numberOfInversions);
	}
	break;

	case 4:
	{
		//1 przypadek z losowymi wartosciami
		HeapSort(Tab, top, numberOfComparisons, numberOfInversions);
		saveDataToFile("Heapsort", top, "Tablica z losowymi liczbami", numberOfComparisons, numberOfInversions);
		resetNumberOfComparisonsAndInversions();

		//2 przypadek z posortowana tablica
		HeapSort(Tab, top, numberOfComparisons, numberOfInversions);
		saveDataToFile("Heapsort", top, "Tablica posortowana rosn¹ca", numberOfComparisons, numberOfInversions);
		resetNumberOfComparisonsAndInversions();

		//3 przypadek z tablica posortowana malejaco
		reverse(Tab, Tab + top);
		HeapSort(Tab, top, numberOfComparisons, numberOfInversions);
		saveDataToFile("Heapsort", top, "Tablica posortowana malej¹co", numberOfComparisons, numberOfInversions);
		resetNumberOfComparisonsAndInversions();

		//4 przypadek z tablica czesciowo nieuporzadkowana
		shakeTable(Tab, top);
		HeapSort(Tab, top, numberOfComparisons, numberOfInversions);
		saveDataToFile("Heapsort", top, "Tablica czêsciowo uporz¹dkowana", numberOfComparisons, numberOfInversions);
	}
	break;

	default:
		cout << "Zly wybor. Koniec programu";
		exit(0);
		break;
	}

	outFile.close();
	delete[] Tab;
}


void CSortTablicy::saveDataToFile(string nameOfMethod, int size, string typeOfTable, int numberOfComparisons, int numberOfInversions)
{
	outFile << setw(20) << nameOfMethod << setw(20) << size << setw(40) << typeOfTable << setw(20) << numberOfComparisons << setw(20) << numberOfInversions << endl;
}



void CSortTablicy::shakeTable(int* Tab, int size)
{
	random_device rd;
	mt19937 mt(rd());

	uniform_int_distribution<int> dist(0, size - 1);

	int numberOfShakeElements = static_cast<int>(round(size * 0.1));
	int x, y;

	for (int i = 0; i < numberOfShakeElements; i++)
	{
		x = dist(rd);
		y = dist(rd);
		swap(Tab[x], Tab[y]);
	}
}

void CSortTablicy::resetNumberOfComparisonsAndInversions()
{
	numberOfComparisons = 0;
	numberOfInversions = 0;
}

void CSortTablicy::insertUserNumbersToTable(int* Tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		Tab[i] = sprawdzLiczbe<int>();
	}
}

void CSortTablicy::insertRandomNumbersToTable(int* Tab, int size)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(0, size*10);

	for (int i = 0; i < size; i++)
	{
		Tab[i] = dist(rd);
	}
}


CSortTablicy::~CSortTablicy()
{
}