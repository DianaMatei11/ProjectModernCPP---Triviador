#include"IntrebariGrila.h"
#include "IntrebareNumerica.h"
#include "Conect.h"
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

int GenerareRandom(const int max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> x(0, max);
	return x(mt);
}

void ValidareRaspuns(const int& raspunsCorect)
{
	int raspunsUser;
	std::cin >> raspunsUser;
	std::cout << '\n';
	if (raspunsCorect == raspunsUser)
	{
		std::cout << "Raspuns Corect!" << '\n';
	}
	else
	{
		std::cout << "Raspuns gresit!" << '\n';
	}
}

void AlegeIntrebareGrila(const std::vector<IntrebariGrila>& vect_intrebari)
{
	int index;
	index = GenerareRandom(vect_intrebari.size() - 1);
	std::cout << vect_intrebari[index];
	std::cout << "Introduceti indexul raspunsului corect: ";
	ValidareRaspuns(vect_intrebari[index].GetIndex_Rasp_Corect());
}

void AlegeIntrebareNumerica(const std::vector<IntrebareNumerica>& vect_intrebari)
{
	int index, no;
	index = GenerareRandom(vect_intrebari.size() - 1);
	std::cout << vect_intrebari[index];
	std::cout << "Introduceti raspunsul corect: ";
	ValidareRaspuns(vect_intrebari[index].GetRaspuns());
}

int main()
{
	Conect c;
	c.meniu();

	std::vector<IntrebariGrila> intrebariVariante;
	std::ifstream in("IntrebariCuVariante.txt");
	Read(in, intrebariVariante);
	in.close();

	std::ifstream inN("IntrebariNumeric.txt");
	std::vector<IntrebareNumerica>intrebariRaspunsUnic;
	Read(inN, intrebariRaspunsUnic);
	inN.close();

	AlegeIntrebareGrila(intrebariVariante);
	AlegeIntrebareNumerica(intrebariRaspunsUnic);

	return 0;
}