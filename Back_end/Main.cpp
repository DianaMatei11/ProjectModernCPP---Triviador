#include"IntrebariGrila.h"
#include "IntrebareNumerica.h"
#include<iostream>
#include <fstream>
#include<vector>
#include<random>

template<class T>
void Read(std::istream& in , std::vector<T>& vect_intrebari)
{
	T p;
	while (in.peek() != EOF)
	{
		in >> p;
		vect_intrebari.push_back(p);
	}
}

int Random()
{
	srand(time(0));
	return rand() % 10;
}

void Intrebare(std::vector<IntrebariGrila>& vect_intrebari)
{
	int index, no;
	index = Random();
	std::cout << vect_intrebari[index];
	std::cout << "Introduceti indexul raspunsului corect: ";
	std::cin >> no;
	std::cout << '\n';
	if (vect_intrebari[index].GetIndex_Rasp_Corect() == no)
	{
		std::cout << "Raspuns Corect!" << '\n';
	}
	else
	{
		std::cout << "Raspuns gresit!" << '\n';
	}
}

void GenerareRandom(std::vector<IntrebareNumerica>intrebari)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> x(0, intrebari.size() - 1);
	std::cout << intrebari[x(mt)] << '\n';
	std::cout << "Introduceti raspunsul corect: ";
}

int main()
{
	std::vector<IntrebariGrila> intrebariVariante;
	std::ifstream in("IntrebariCuVariante.txt");
	Read(in, intrebariVariante);
	in.close();

	std::ifstream inN("IntrebariNumeric.txt");
	std::vector<IntrebareNumerica>intrebariRaspunsUnic;
	Read(inN, intrebariRaspunsUnic);
	inN.close();

	Intrebare(intrebariVariante);
	GenerareRandom(intrebariRaspunsUnic);

	return 0;
}