#include <iostream>
#include "computer.h"
#include <string>
#include <vector>

using std::string;

int main()
{
	std::cout << call_calculator<double>("sin(1)").second;
}