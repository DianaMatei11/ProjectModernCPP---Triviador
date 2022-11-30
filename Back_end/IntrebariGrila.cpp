#include "IntrebariGrila.h"
#include<fstream>
#include<vector>


IntrebariGrila::IntrebariGrila(const std::string& enunt, std::array < std::string, 4>& answers, int indexRaspunsCorect):Intrebare(enunt),raspunsuri{answers},index_rasp_corect{indexRaspunsCorect}
{
}


void IntrebariGrila::SetRaspunsuri(const std::array<std::string,4>& raspunsuri)
{
	for (int i = 0; i < 4; i++)
		this->raspunsuri[i] = raspunsuri[i];
}

void IntrebariGrila::SetIndex_Rasp_Corect(int index_rasp_corect)
{
	this->index_rasp_corect = index_rasp_corect;
}


std::array<std::string, 4> IntrebariGrila::GetRaspunsuri() const
{
	return raspunsuri;
}

int IntrebariGrila::GetIndex_Rasp_Corect() const
{
	return index_rasp_corect;
}

void IntrebariGrila::AfisareAvantaj()
{
	int r = GetRandomNumber(0,3);
	int x = GetIndex_Rasp_Corect();
	x--;
	while (r ==x)
	{
		r = GetRandomNumber(0, 3);
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
	intrebari.SetEnunt(str);

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
	out << a.GetEnunt() << '\n';
	out << "Variante de raspuns: " << '\n';
	out << "1." << a.raspunsuri[0] << '\n';
	out << "2." << a.raspunsuri[1] << '\n';
	out << "3." << a.raspunsuri[2] << '\n';
	out << "4." << a.raspunsuri[3] << '\n';
	return out;
}
