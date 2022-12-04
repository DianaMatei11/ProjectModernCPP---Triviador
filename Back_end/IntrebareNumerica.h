#pragma once
#include<string>
#include <iostream>
#include<random>
#include "Intrebare.h"

class IntrebareNumerica:public Intrebare
{
private:
	int m_raspuns;

public:
	IntrebareNumerica() = default;
	IntrebareNumerica(const std::string& enunt, int raspuns);
	int GetRaspuns() const;
	bool VerificareRaspuns();
	void AvantajAproximativRaspunsCorect();
	std::vector<int> afis4();
	void AfisareAvantaje();
	void Avantaj4Raspunsuri();
	void Afisare();
	void VerificareRaspunsDupaAvantaj();
	friend std::istream& operator >> (std::istream& in, IntrebareNumerica& intr);
	friend std::ostream& operator <<(std::ostream& out, const IntrebareNumerica& intr);
	int DiferentaInput(int input);
	~IntrebareNumerica() = default;
};

