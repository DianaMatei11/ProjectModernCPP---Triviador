#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<array>
#include<vector>
#include "Intrebare.h"

class IntrebariGrila:public Intrebare
{
private:
	std::array <std::string, 4> raspunsuri;
	int index_rasp_corect;
	uint16_t m_id;

public:
	IntrebariGrila() = default;
	IntrebariGrila(const std::string& enunt, std::array < std::string, 4>& answers, int indexRaspunsCorect);

	void SetRaspunsuri(const std::array<std::string,4>& raspunsuri);
	void SetIndex_Rasp_Corect(int index_rasp_corect);

	std::array<std::string, 4> GetRaspunsuri() const;
	int GetIndex_Rasp_Corect() const;

	std::string GetOption0() const;
	std::string GetOption1() const;
	std::string GetOption2() const;
	std::string GetOption3() const;

	void SetOption0(const std::string opt);
	void SetOption1(const std::string opt);
	void SetOption2(const std::string opt);
	void SetOption3(const std::string opt);


	uint16_t GetId() const;
	void SetId(const uint16_t& newId);

	void AfisareAvantaj();
	
	friend std::istream& operator>>(std::istream& in, IntrebariGrila& a);
	friend std::ostream& operator << (std::ostream& out, const IntrebariGrila& a);
	~IntrebariGrila()=default;
};

