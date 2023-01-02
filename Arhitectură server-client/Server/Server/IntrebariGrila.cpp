#include "IntrebariGrila.h"
#include<fstream>
#include<vector>


IntrebariGrila::IntrebariGrila(const std::string& enunt, std::array < std::string, 4>& answers, int indexRaspunsCorect) : Intrebare(enunt), raspunsuri{answers}, index_rasp_corect{indexRaspunsCorect}
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

int IntrebariGrila::GetOptionRandom() const
{
	int r = GetRandomNumber(0, 3);
	int x = GetIndex_Rasp_Corect();
	x--;
	while (r == x)
	{
		r = GetRandomNumber(0, 3);
	}
	return r;
	
}

std::string IntrebariGrila::GetOption0() const
{
	return raspunsuri[0];
}

std::string IntrebariGrila::GetOption1() const
{
	return raspunsuri[1];
}

std::string IntrebariGrila::GetOption2() const
{
	return raspunsuri[2];
}

std::string IntrebariGrila::GetOption3() const
{
	return raspunsuri[3];
}


void IntrebariGrila::SetOption0(const std::string opt)
{
	raspunsuri[0] = opt;
}

void IntrebariGrila::SetOption1(const std::string opt)
{
	raspunsuri[1] = opt;
}

void IntrebariGrila::SetOption2(const std::string opt)
{
	raspunsuri[2] = opt;
}

void IntrebariGrila::SetOption3(const std::string opt)
{
	raspunsuri[3] = opt;
}


uint16_t IntrebariGrila::GetId() const
{
	return m_id;
}

void IntrebariGrila::SetId(const uint16_t& newId)
{
	m_id = newId;
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
