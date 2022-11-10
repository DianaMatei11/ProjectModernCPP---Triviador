#include "IntrebariGrila.h"#include "IntrebariGrila.h"

IntrebariGrila::IntrebariGrila(std::string enunt, std::array < std::string, 4> raspunsuri, int index_rasp_corect)
{
	this->enunt = enunt;
	this->raspunsuri = raspunsuri;
	this->index_rasp_corect = index_rasp_corect;

}

std::istream& operator>>(std::istream& IntrebariCuVariante, IntrebariGrila& intrebari)
{
	getline(IntrebariCuVariante, intrebari.enunt);
	std::string str;

	for (int i = 0; i < 4; i++)
	{
		getline(IntrebariCuVariante, str);
		intrebari.raspunsuri[i] = str;
	}
	IntrebariCuVariante >> intrebari.index_rasp_corect;
	return IntrebariCuVariante;
}

std::ostream& operator <<(std::ostream& out,const IntrebariGrila& intrebare)
{
	out << intrebare.enunt;
	int i = 0;
	out << "Alegeti raspunsul corect: ";
	out << "A." << intrebare.raspunsuri[i++] << '\n';
	out << "B." << intrebare.raspunsuri[i++] << '\n';
	out << "C." << intrebare.raspunsuri[i++] << '\n';
	out << "D." << intrebare.raspunsuri[i] << '\n';
	return out;
}
