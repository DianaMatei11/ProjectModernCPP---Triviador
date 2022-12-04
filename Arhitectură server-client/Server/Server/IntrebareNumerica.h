#pragma once
#include<string>
#include <iostream>
#include<random>
#include "Intrebare.h"

class IntrebareNumerica : public Intrebare
{
private:
	int m_raspuns;
	uint16_t m_id;
public:
	IntrebareNumerica() = default;
	IntrebareNumerica(const std::string& enunt, int raspuns);
	int GetRaspuns() const;
	void SetRaspuns(const int raspuns);
	bool VerificareRaspuns();

	void AvantajAproximativRaspunsCorect();
	std::vector<int> afis4();
	void AfisareAvantaje();
	void Avantaj4Raspunsuri();
	void Afisare();
	void VerificareRaspunsDupaAvantaj();
	
	uint16_t GetId() const;
	void SetId(const uint16_t& newId);

	friend std::istream& operator >> (std::istream& in, IntrebareNumerica& intr);
	friend std::ostream& operator <<(std::ostream& out, const IntrebareNumerica& intr);
	int DiferentaInput(int input);
	~IntrebareNumerica() = default;
};

