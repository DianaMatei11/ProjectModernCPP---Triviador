#include "IntrebariGrila.h"
#include<fstream>
#include<vector>


IntrebariGrila::IntrebariGrila(std::string enunt, std::array < std::string, 4> raspunsuri, int index_rasp_corect)
{
	this->enunt = enunt;
	this->raspunsuri = raspunsuri;
	this->index_rasp_corect = index_rasp_corect;

}

void IntrebariGrila::SetEnunt(const std::string& enunt)
{
	this->enunt = enunt;
}

void IntrebariGrila::SetRaspunsuri(const std::string& raspunsuri)
{
	for (int i = 0; i < 4; i++)
		this->raspunsuri[i] = raspunsuri[i];
}

void IntrebariGrila::SetIndex_Rasp_Corect(int index_rasp_corect)
{
	this->index_rasp_corect = index_rasp_corect;
}

std::string IntrebariGrila::GetEnunt()
{
	return enunt;
}
std::array<std::string, 4> IntrebariGrila::GetRaspunsuri()
{
	return raspunsuri;
}

int IntrebariGrila::GetIndex_Rasp_Corect()
{
	return index_rasp_corect;
}

void IntrebariGrila::AfisareAvantaj()
{
	srand (time(NULL));
	int r = rand() % 4;
	int x = GetIndex_Rasp_Corect();
	x--;
	while (r ==x)
	{
		r = rand() % 4;
	}

	std::cout << "Avantajul FIFTY - FIFTY este: " << '\n';
	std::cout<< raspunsuri[r];
	std::cout << std::endl;
	std::cout<< raspunsuri[x];

}

std::istream& operator>>(std::istream& in, IntrebariGrila& intrebari)
{
	std::string str;
	std::getline(in, str);
	intrebari.enunt = str;
	for (int i = 0; i < 4; i++)
	{
		getline(in, str);
		intrebari.raspunsuri[i] = str;
	}
	getline(in, str);
	intrebari.index_rasp_corect = stoi(str);
	return in;


}
std::ostream& operator <<(std::ostream& out, const IntrebariGrila& a)
{
	out << a.enunt << '\n';
	out << "Variante de raspuns: " << '\n';
	out << "1." << a.raspunsuri[0] << '\n';
	out << "2." << a.raspunsuri[1] << '\n';
	out << "3." << a.raspunsuri[2] << '\n';
	out << "4." << a.raspunsuri[3] << '\n';
	return out;
}
