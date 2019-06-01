#include "CTablica.h"
#include <iostream>
#include <algorithm>
using namespace std;


void CTablica::heapify(int* Tab, int heap_size, int i, int& numberOfComparisons, int& numberOfInversions)
{
	//zmienne pomocnicze
	int largest{}, temp{};
	//np. dla korzenia i=0, jego dzieci to odpowiednio lChild = 1, rChild = 2
	int leftChild = 2 * i + 1, rightChild = (2 * i) + 2;

	//jesli istnieje lewe dziecko i-rodzica oraz wartosc lewego dziecka jest wieksza od wartosci i-rodzica
	//to przypisujemy do largest index lewego dziecka
	if (leftChild < heap_size && Tab[leftChild] > Tab[i])
		largest = leftChild;
	else
		largest = i;

	numberOfComparisons += 2;

	//jesli istnieje prawe dziecko i-rodzica oraz wartosc prawego dziecka jest wieksza od wartosci lewego dziecka(lub i-rodzica)
	//to przypisujemy do largest index prawego dziecka
	if (rightChild < heap_size && Tab[rightChild] > Tab[largest])
		largest = rightChild;

	numberOfComparisons += 2;

	//jesli largest nie jest indexem i-rodzica
	if (largest != i)
	{
		//zamieniamy wartosci lewego/prawego dziecka z rodzicem
		swap(Tab[largest], Tab[i]);
		numberOfInversions++;

		//wywolujemy rekursywnie procedure heapify dla zamienionego dziecka, poniewaz moglo dojsc do zaburzenia wlasnosci kopca
		heapify(Tab, heap_size, largest, numberOfComparisons, numberOfInversions);
	}
}


void CTablica::buildHeap(int* Tab, int heap_size, int& numberOfComparisons, int& numberOfInversions)
{
	//od ostatniego rodzica do zerowego rodzica (korzenia) wywolanie procedury heapify
	for (int i = heap_size / 2 - 1; i >= 0; i--)
		heapify(Tab, heap_size, i, numberOfComparisons, numberOfInversions);
}


void CTablica::swap(int & a, int & b)
{
	int tmp = b;
	b = a;
	a = tmp;
}


int CTablica::Lomuto_Quicksort(int* Tab, int low, int top, int &numberOfComparisons, int &numberOfInversions)
{
	if (low >= top) return 0;			//je�li tablica jest jednoelementowa -> powr��

	int s = (low + top) / 2;			//wyznaczanie �rodka tablicy
	int pivot = Tab[s];					//wyznaczanie piwota jako �rodkowego elementu w tablicy
	swap(Tab[s], Tab[top]);				//zamiana piwota z ostatnim elementem w tablicy
	int b = low;						//ustawienie granicy w quicksorcie Lomuto
	for (int a = low; a < top; a++)		//poruszanie si� od pocz�tku do ko�ca tablicy
	{
		numberOfComparisons++;			//zwi�kszanie liczby por�wna�

		if (Tab[a] <= pivot)			//je�li element w tablicy jest mniejszy od piwota
		{
			swap(Tab[a], Tab[b]);		//zamie� element z elementem wyznaczaj�cym granic�
			numberOfInversions++;		//zwi�kszamy liczb� przestawie�
			b++;						//przes�wamy granic�
		}
	}

	swap(Tab[b], Tab[top]);				//zamie� piwot z granic�
	numberOfInversions++;				//zwi�kszamy liczb� przestawie�

	Lomuto_Quicksort(Tab, low, b - 1, numberOfComparisons, numberOfInversions); //wej�cie do lewej podtablicy
	Lomuto_Quicksort(Tab, b + 1, top, numberOfComparisons, numberOfInversions); //wej�cie do prawej podtablicy
}


void CTablica::HeapSort(int* Tab, int heap_size, int &numberOfComparisons, int &numberOfInversions)
{
	//stworzenie z tablicy kopca
	buildHeap(Tab, heap_size, numberOfComparisons, numberOfInversions);

	//zamiana ostatniego dziecka z maksymalnym elementem (korzeniem)
	//dekrementacja rozmiaru tablicy, poniewaz ostatni element jest juz posortowany
	//przywrocenie wlasnosci kopca, czyli de facto wyplyniecie nastepnego maksymalnego elementu do korzenia
	for (int i = heap_size - 1; i > 0; i--)
	{
		swap(Tab[i], Tab[0]);
		numberOfInversions++;
		heap_size--;
		heapify(Tab, heap_size, 0, numberOfComparisons, numberOfInversions);
	}
}


int CTablica::Hoare_Quicksort(int* Tab, int low, int top, int& numberOfComparisons, int& numberOfInversions)
{
	if (low >= top) return 0;			//je�li tablica jest jednoelementowa -> powr��

	int piwot = Tab[(low+top)/2];		//wyznaczanie piwota jako �rodkowego elementu w tablicy
	int i = low;						//okre�lenie dolnej granicy
	int j = top;						//okre�lenie g�rnej granicy

	while (i <= j)						//dop�ki obie granice nie przejd� za siebie
	{
		while (Tab[i] < piwot)			//szukamy elementu wiekszego lub r�wnego piwotowi od pocz�tka tablicy
		{
			numberOfComparisons++;
			i++;
		}

		while (Tab[j] > piwot)			//szukamy elementu mniejszego lub r�wnego piwotowi od ko�ca tablicy
		{
			numberOfComparisons++;
			j--;
		}

		if (i <= j)						//je�li granice nie przesz�y za siebie dokonujemy inwersji znalezionych element�w w tablicy
		{
			numberOfInversions++;
			swap(Tab[i], Tab[j]);		//zamie� elementy
			i++;						//zwi�kszamy granice doln�
			j--;						//zmniejszamy granic� g�rn�
		}
	}

	Hoare_Quicksort(Tab, low, j, numberOfComparisons, numberOfInversions); //przejd� do lewej podtablicy
	Hoare_Quicksort(Tab, i, top, numberOfComparisons, numberOfInversions); //przejd� do prawej podtablicy
}


void CTablica::cocktailSort(int * Tab, int size, int& numberOfComparisons, int& numberOfInversions)
{

	int bottom{};
	int top = size - 1;
	int lvlOfLastExchange{};

	while (lvlOfLastExchange >= 0)
	{
		lvlOfLastExchange = -1;

		for (int i = bottom; i < top; i++)
		{
			numberOfComparisons++;
			if (Tab[i] > Tab[i + 1])
			{
				swap(Tab[i], Tab[i + 1]);
				lvlOfLastExchange = i;
				numberOfInversions++;
			}
		}

		if (lvlOfLastExchange < 0)
			break;

		top = lvlOfLastExchange;

		//druga czesc algorytmu
		lvlOfLastExchange = -1;

		for (int i = top; i > bottom; i--)
		{
			numberOfComparisons++;
			if (Tab[i] < Tab[i - 1])
			{
				swap(Tab[i], Tab[i - 1]);
				lvlOfLastExchange = i;
				numberOfInversions++;
			}
		}

		bottom = lvlOfLastExchange;
	}
}

CTablica::~CTablica()
{
}