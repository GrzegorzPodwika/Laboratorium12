#include "libExceptions.h"


using namespace std;

int* createTable(int size)
{
	int* tab = nullptr;

	try
	{
		if (size > 0)
			tab = new int[size];
		else
			throw MyRuntimeExceptions::BadAllocateException("Nie udalo sie zaalokowac pamieci na tablice intow!");
	}
	catch (std::runtime_error &e)
	{
		cerr << e.what();
		exit(0);
	}

	return tab;
}
