#pragma once

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string readFile(string fileName)
{
	string fileText;
	ifstream myFile(fileName);
	string tempText;
	while (getline(myFile, tempText))
	{
		std::cout << tempText << std::endl;
		fileText += tempText;
	}
	std::cout << fileText << std::endl;
	return fileText;
}