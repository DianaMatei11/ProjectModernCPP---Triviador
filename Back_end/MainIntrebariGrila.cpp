#include"IntrebariGrila.h"
#include<iostream>

void Read(std::vector<IntrebariGrila>& vect_intrebari)
{
	IntrebariGrila p;
	std::ifstream f("in.txt");
	while (f.peek() != EOF)
	{
		f >> p;
		vect_intrebari.push_back(p);
	}
	f.close();
}
int Random()
{
	srand(time(0));
	return rand() % 10;
}
void Intrebare(std::vector<IntrebariGrila> vect_intrebari)
{
	int index, no;
	index = Random();
	std::cout << vect_intrebari[index];
	std::cout << "Introduceti indexul raspunsului corect: ";
	std::cin >> no;
	std::cout << '\n';
	if (vect_intrebari[index].GetIndex_Rasp_Corect() == no)
		std::cout << "Raspuns Corect!" << '\n';
	else std::cout << "Raspuns gresit!" << '\n';
}

int main()
{
	std::vector<IntrebariGrila> vect_intrebari;
	Read(vect_intrebari);
	Intrebare(vect_intrebari);

	system("pause");
	return 0;
}