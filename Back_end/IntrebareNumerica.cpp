#include "IntrebareNumerica.h"

IntrebareNumerica::IntrebareNumerica(std::string enunt, int raspuns)
{
	m_enunt = enunt;
	m_raspuns = raspuns;
}

std::string IntrebareNumerica::GetEnunt() const
{
	return m_enunt;
}

int IntrebareNumerica::GetRaspuns() const
{
	return m_raspuns;
}
int IntrebareNumerica::DiferentaInput(int input)
{
	return abs(input - m_raspuns);
}

bool IntrebareNumerica::VerificareRaspuns()
{
	if (m_raspuns < 30)
		return false;
	return true;
}

void IntrebareNumerica::AvantajAproximativRaspunsCorect()
{
	srand(time(NULL));
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> distribution(-10.0, 10.0);
	if (VerificareRaspuns() == true)
	{
		std::cout << "Raspunsul corect este apropiat de: ";
		std::cout << m_raspuns + distribution(mt);
	}
}
double IntrebareNumerica::GenerareNumarRandom()
{
	srand(time(NULL));
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> distribution(-100.0, 100.0);
	return distribution(mt);
}
std::vector<int>IntrebareNumerica::Avantaj4Raspunsuri()
{
	std::vector<int>vect;
	int x = GenerareNumarRandom();
	for (int i = 0; i < 4; i++)
	{
		vect[i] = x+VerificareRaspuns();
		x = GenerareNumarRandom();
	}
	return vect;
}



std::istream& operator>>(std::istream& in, IntrebareNumerica& intr)
{
	std::getline(in, intr.m_enunt);
	std::string aux;
	std::getline(in, aux);
	intr.m_raspuns = stoi(aux);
	return in;
}

std::ostream& operator<<(std::ostream& out, const IntrebareNumerica& intr)
{
	out << intr.m_enunt;
	out << std::endl;
	//la afisarea unei intrebari cu raspuns numeric, se asteapta inputul utilizatorului/jucatorului pentru validare
	//astfel, raspunsul atasat intrebarii nu este afisat pe ecran decat dupa colectarea rapunsurilor tuturor jucatorilor
	//acest lucru se face intr-o functie ulterioara
	return out;
}
