// Triviador_ParteI_Commit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "IntrebareNumerica.h"
#include <fstream>
#include<vector>
void citire(std::vector<IntrebareNumerica>& intrebari)
{

    std::ifstream f("IntrebariNumeric.txt");
    IntrebareNumerica aux;
    while (f.peek()!=EOF)
    {
        f >> aux;
        intrebari.push_back(aux);
    }
    f.close();
}
//int main()
//{

    //std::vector<IntrebareNumerica>intrebari;
   // citire(intrebari);
   // for (int i = 0; i < intrebari.size(); i++)
     //   std::cout << intrebari[i] << " " << intrebari[i].GetRaspuns() << std::endl;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
