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
	if (m_raspuns < 5)
		return false;
	return true;
}

void IntrebareNumerica::AvantajAproximativRaspunsCorect()
{
	srand(time(NULL));
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> distribution(-10, 10);
	if (VerificareRaspuns() == true)
	{
		std::cout << "Raspunsul corect este apropiat de: ";
		std::cout << m_raspuns + round(distribution(mt));
	}
}

double IntrebareNumerica::GenerareNumarRandom()
{
	srand(time(NULL));
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> distribution(-100, 100);
	return round(distribution(mt));
}
std::vector<int>IntrebareNumerica::afis4()
{
	std::vector<int>vect;
	int x = GenerareNumarRandom();
	for (int i = 0; i < 4; i++)
	{
		while(m_raspuns + x <5)
		{ 
			x = GenerareNumarRandom();
		}
		x = x + m_raspuns;
		vect.push_back( x);
		x = GenerareNumarRandom();
		
	}
	if (std::find(vect.begin(), vect.end(), m_raspuns) == vect.end())
	{
		x = GenerareNumarRandom();
		x = abs(x) % 3;
		vect[x] = m_raspuns;
	}
	return vect;
}
void IntrebareNumerica::Afisare()
{
	int numar;
	std::string aux;
	std::cout << "Aveti nevoie de un avantaj?\n";
	std::cin >> aux;
	if (aux == "da" || aux == "Da" || aux == "dA" || aux == "DA")
	{
		AfisareAvantaje();
	}
	else
	{
		std::cout << "Introduceti raspunsul corect: ";
		std::cin >> numar;
		//conditie pusa pana cand se vor juca mai multe persoane
		if (numar == m_raspuns)
			std::cout << "Raspuns corect";
		else
			std::cout << "Raspuns gresit";
	}
}

void IntrebareNumerica::VerificareRaspunsDupaAvantaj()
{
	int a;
	std::cout << "Introduceti raspunsul corect:\n";
	std::cin >> a;
	if (a == m_raspuns)
		std::cout << "raspuns corect\n";
	else
		std::cout << "raspuns gresit";
}


void IntrebareNumerica::AfisareAvantaje()
{ 
	int numar;
	std::cout << "Puteti alege unul dintre urmatoarele avantaje: " << '\n';
	std::cout << "1.Alegere raspuns! \n";
	std::cout << "2.Sugerare raspuns!\n";
	std::cin >> numar;
	if (numar == 1)
	{ 
		Avantaj4Raspunsuri();
		VerificareRaspunsDupaAvantaj();
	}
	else
		AvantajAproximativRaspunsCorect();
}


void IntrebareNumerica::Avantaj4Raspunsuri()
{
	std::vector<int>aux;
	aux = afis4();
	int a = 1;
	for (int i = 0; i < aux.size(); i++)
		std::cout <<a++ <<"." << aux[i] << '\n';
	
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
