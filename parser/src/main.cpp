/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/05/2018 01:09:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include "../../largeInt/inc/log.hpp"
#include "../../largeInt/inc/largeInt.hpp"

std::string interpret(const std::string &s)
{
	Print("");
	if (s == "")
	{
		throw std::exception ();
	}
	Print(s);
	std::istringstream stm (s);
	largeInt a, b;
	stm >> a;
	std::string op {};
	stm >> op;
	stm >> b;
	
	if ( op == "+")
	{
		return (a + b).serialize();
	}
	else if (op == "*")
	{
		return (a * b).serialize();
	}
	else if (op =="-")
	{
		return (a - b).serialize();
	}
	else if (op == "/")
	{	
		return (a / b).serialize();
	}
	else if (op == "%")
	{
		return (a % b).serialize();
	}
	else if (op == "<")
	{
		return (a < b? "True" : "False");
	}
	else if (op == ">")
	{
		return (a > b? "True" : "False");
	}
	else if (op == "<=")
	{
		return (a <= b? "True" : "False");
	}
	else if (op == ">=")
	{
		return (a >= b? "True" : "False");
	}
	else if (op == "==")
	{
		return (a == b? "True" : "False");
	}
	else
	{
		throw std::exception ();
	}
	return "";
}

void process(void)
{
	Print("");
	std::string input;
	while(true)
	{
		std::cout << ">>";
		std::getline(std::cin, input);
		Print(input);
		if ("quit" == input || "Quit" == input || "exit" == input || "Exit" == input)
		{
			break;
		}
		try 
		{
			std::cout << interpret(input);
		}
		catch (...)
		{
			std::cout << "Incorrect input\n";
		}
		std::cout << "\n";
	}
}

int main(int argc, char** argv)
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	process();	
	//std::cout << (largeInt {1} < largeInt {1} ? "True":"False") << "\n"; 
	//std::cout << (largeInt {2} < largeInt {1} ? "True":"False") << "\n"; 
	//std::cout << (largeInt {1} < largeInt {2} ? "True":"False") << "\n"; 
	//std::cout << (largeInt {11} < largeInt {2} ? "True":"False") << "\n"; 
	//std::cout << (largeInt {1} < largeInt {11} ? "True":"False") << "\n"; 
	//std::cout << (largeInt {22} < largeInt {11} ? "True":"False") << "\n"; 

	//std::cout << (largeInt {1} > largeInt {1} ? "True":"False") << "\n"; 
	//std::cout << (largeInt {2} > largeInt {1} ? "True":"False") << "\n"; 
	//std::cout << (largeInt {1} > largeInt {2} ? "True":"False") << "\n"; 
	//std::cout << (largeInt {11} > largeInt {2} ? "True":"False") << "\n"; 
	//std::cout << (largeInt {1} > largeInt {11} ? "True":"False") << "\n"; 
	//std::cout << (largeInt {22} > largeInt {11} ? "True":"False") << "\n"; 


	//int a[] = {1, 1, 1, 4, 5, 6, 7};
	//int b[] = {1, 2, 3, 4, 5, 6, 7};
	//std::cout << (compare(a,b,cmp,7)? "True":"False") << "\n";
	

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

	std::cout << "Execution time "<< duration << "\n";
	return 0;
}
