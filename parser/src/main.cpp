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
#include <cctype>
#include <memory>
#include <map>
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

enum class operations
{
//	POST_INCREMENT,
//	POST_DECREMENT,
	INVALID,
	ADDITION,
	SUBSTRACTION,
	MULTIPLICATION,
	DIVITION,
	REMAINDER,	
};

std::ostream& operator << (std::ostream &stm, const operations & op)
{
	switch (op)
	{
	case operations::INVALID:
		stm << "INVALID";
		break;
	case operations::ADDITION:
		stm << "ADDITION";
		break;
	case operations::SUBSTRACTION:
		stm << "SUBSTRACTION";
		break;
	case operations::MULTIPLICATION:
		stm << "MULTIPLICATION";
		break;
	case operations::DIVITION:
		stm << "DIVITION";
		break;
	case operations::REMAINDER:
		stm << "REMAINDER";
		break;
	default:
		break;
	}
	return stm;
}

std::map<char, operations> supported_operations = {
	{'+', operations::ADDITION},
	{'-', operations::SUBSTRACTION},
	{'*', operations::MULTIPLICATION},
	{'/', operations::DIVITION},
	{'%', operations::REMAINDER},	
};



class priorityQue
{
private:
	std::unique_ptr<largeInt> nr;
	::operations op;
	std::unique_ptr<priorityQue> higherPrio;
	std::unique_ptr<priorityQue> lowerPrio;

public:
	void insert(const largeInt&a, ::operations _op);
	void insert(largeInt &&a, ::operations _op);
	const largeInt process();
	priorityQue(const largeInt &a): nr{std::make_unique<largeInt>(a)}, op {operations::INVALID}, higherPrio {nullptr}, lowerPrio {nullptr} {} 
	priorityQue(largeInt &&a): nr{std::make_unique<largeInt>(std::move(a))}, op{operations::INVALID}, higherPrio {}, lowerPrio {} {} 


	priorityQue(const largeInt&a, ::operations _op):nr{std::make_unique<largeInt>(a)}, op {_op}, higherPrio {nullptr}, lowerPrio{nullptr} {}
	priorityQue(largeInt&&a, ::operations _op):nr{std::make_unique<largeInt>(std::move(a))}, op {_op}, higherPrio {nullptr}, lowerPrio{nullptr} {}

};

void priorityQue::insert(const largeInt&a, ::operations _op)
{
	Print("");
	Print("Inserting ", a, " with operation ", _op);
	if (nullptr != this->lowerPrio)
	{
		Print("Inserting ", a, " with operation ", _op);
		this->lowerPrio->insert(a,_op);
	}
	
	else if (::operations::ADDITION == _op || ::operations::SUBSTRACTION == _op)
	{
		Print("Inserting ", a, " with operation ", _op);
		// lower
		this->lowerPrio = std::make_unique<priorityQue>(a, _op);

	}
	else
	{
		Print("Inserting ", a, " with operation ", _op);
		if (nullptr != this->higherPrio)
		{
			Print("Inserting ", a, " with operation ", _op);
			this->higherPrio->insert(a, _op);
		}
		else
		{
			Print("Inserting ", a, " with operation ", _op);
			// higher
			this->higherPrio = std::make_unique<priorityQue>(a, _op);
		}
	}
}

void priorityQue::insert(largeInt&&a, ::operations _op)
{
	Print("");
	Print("Inserting ", a, " with operation ", _op);
	if (nullptr != this->lowerPrio)
	{
		Print("Inserting ", a, " with operation ", _op);

		this->lowerPrio->insert(std::move(a),_op);
	}
	else if (::operations::ADDITION == _op || ::operations::SUBSTRACTION == _op)
	{
		Print("Inserting ", a, " with operation ", _op);
		// lower
		this->lowerPrio = std::make_unique<priorityQue>(std::move(a), _op);

	}
	else
	{
		Print("Inserting ", a, " with operation ", _op);
		if (nullptr != this->higherPrio)
		{
			Print("Inserting ", a, " with operation ", _op);
			this->higherPrio->insert(std::move(a), _op);
		}
		else
		{
			Print("Inserting ", a, " with operation ", _op);
			// higher
			this->higherPrio = std::make_unique<priorityQue>(std::move(a), _op);
		}
	}
}

const largeInt priorityQue::process()
{
	Print("");
	largeInt ret {*nr};
	Print("Nr = ", *nr);
	if (nullptr != higherPrio)
	{
		largeInt b = higherPrio->process(); 
		switch(higherPrio->op)
		{
		case operations::INVALID:
			//Print("");
			break;
		case operations::ADDITION:
			Print(ret, " + ", b, " = ", ret + b);
			ret = ret + b;
			break;
		case operations::SUBSTRACTION:
			//Print("");
			Print(ret, " - ", b, " = ", ret - b);
			ret = ret - b;
			break;
		case operations::MULTIPLICATION:
			//Print("");	
			Print(ret, " * ", b, " = ", ret * b);
			ret = ret * b;
			break;
		case operations::DIVITION:
			//Print("");
			Print(ret, " / ", b, " = ", ret / b);
			ret = ret / b;
			break;
		case operations::REMAINDER:
			//Print("");	
			Print(ret, " % ", b, " = ", ret % b);
			ret = ret % b;
			break;
		default:
			break;
		}
	}
	Print("Nr = ", *nr);
	Print("Ret = ", ret);
	if (nullptr != lowerPrio)	
	{
		largeInt b = lowerPrio->process(); 

		switch(lowerPrio->op)
		{
		case operations::INVALID:
			break;
		case operations::ADDITION:
			//Print("");
			Print(ret, " + ", b);
			ret = ret + b;
			break;
		case operations::SUBSTRACTION:
			//Print("");
			Print(ret, " - ", b);
			ret = ret - b;
			break;
		case operations::MULTIPLICATION:
			//Print("");
			Print(ret, " * ", b);
			ret = ret * b;
			break;
		case operations::DIVITION:
			//Print("");
			Print(ret, " / ", b);
			ret = ret / b;
			break;
		case operations::REMAINDER:
			//Print("");
			Print(ret, " % ", b);
			ret = ret % b;
			break;
		default:
			break;
		}
	}
	Print("Nr = ", *nr);
	Print("Ret = ", ret);
	return ret;
}

::operations getOperator(const char c)
{
	::operations op = ::operations::INVALID;
	for (auto it : supported_operations)
	{
		if (c == it.first)
		{
			op = it.second;
		}
	}
	return op;
}

const std::string interpret2 (const std::string &input)
{
	//std::istringstream ss(input);
	const char *p = input.c_str();
	std::string buffer;
	largeInt a {};
	size_t it = 0;
	bool gotOperator = false;
	::operations op = ::operations::INVALID;
	while (it < input.size())
	{
		Print("Processing char ", p[it], " position ", it);
		if (std::isdigit(static_cast<unsigned char>(p[it])))
		{
			while (it < input.size() && std::isdigit(static_cast<unsigned char>(p[it])))
			{
				Print("");
				buffer += p[it];
				Print("Buffer so far ", buffer);
				++it;
			}
			Print("Buffer so far ", buffer, " number ", largeInt{buffer});

			a = largeInt {buffer};
			buffer = {};
			Print("Found number ", a);
			break;
		}
		else if (p[it] == ' ')
		{
			++it;
		}
		else
		{
			return std::string {"Unrecognized operator"};
		}
	}

	priorityQue red {a};
	
	while (it < input.size())
	{
		if (std::isdigit(static_cast<unsigned char>(p[it])) && gotOperator)
		{
			while (it < input.size() && std::isdigit(static_cast<unsigned char>(p[it])))
			{
				buffer += p[it];
				++it;
			}
			a = largeInt{buffer};
			buffer = {};
			Print("Found number ", a);	
			red.insert(a, op);
			gotOperator = false;
		}
		else if (::operations::INVALID != getOperator(p[it]) && !gotOperator)
		{
			op = getOperator(p[it]);
			Print("Found operator ", op);
			gotOperator = true;
			++it;	
		}
		else if (p[it] == ' ')
		{
			++it;
		}
		else
		{
			return std::string {"Unrecognized operator"};
		}
	}
	return red.process().serialize();
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
			std::cout << interpret2(input);
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
	//largeInt a {"123456"};
	//std::cout << a << "\n";
	//a = largeInt {"44444444444444444"};
	//std::cout << a << "\n";

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

	std::cout << "Execution time "<< duration << "\n";
	return 0;
}
