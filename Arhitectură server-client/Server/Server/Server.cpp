#include<iostream>
#include<numeric>
#include<sstream>
#include<regex>
#include<string>

#include<cpr/cpr.h>
#include<crow.h>

int main()
{
	std::string adresa_url = "10000";
	cpr::Response response = cpr::Get(cpr::Url{ adresa_url });
	crow::json::rvalue products = crow::json::load(response.text);

	return 0;
}