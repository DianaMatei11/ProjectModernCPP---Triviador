#pragma once
#include<string>
#include <iostream>
#include<random>
class IntrebareNumerica
{
private:
	std::string m_enunt;
	int m_raspuns;

public:
	IntrebareNumerica() = default;
	IntrebareNumerica(std::string enunt, int raspuns);
	std::string GetEnunt() const;
	int GetRaspuns() const;
	bool VerificareRaspuns();
	void AvantajAproximativRaspunsCorect();
	std::vector<int> afis4();
	void AfisareAvantaje();
	void Avantaj4Raspunsuri();
	double GenerareNumarRandom();
	void Afisare();
	void VerificareRaspunsDupaAvantaj();
	friend std::istream& operator >> (std::istream& in, IntrebareNumerica& intr);
	friend std::ostream& operator <<(std::ostream& out, const IntrebareNumerica& intr);
	int DiferentaInput(int input);
	~IntrebareNumerica() = default;
};

