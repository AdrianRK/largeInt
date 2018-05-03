/*
 * main.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: adrian
 */
#include <algorithm>
#include <cstring>
#include <vector>
#include <typeinfo>
#include <cctype>
#include <exception>

#include "../inc/largeInt.hpp"
#include "../inc/log.hpp"

template <typename T, typename op, typename size>
bool compare(const T & a, const T & b, const op& cmp, const size &sz)
{
	for (size it = sz; it > 0; --it)	
	{
		if (!cmp (a[it-1], b[it-1]))
		{
			return false;
		}
	}
	return true;
}

void largeInt::PrintDBG() const
{
	lout << "Size " << size << " MaxSize " << maxSize << "\n";

	for (dataSizeType it = 0; it < maxSize; ++it)
	{
		lout << number[it] << " ";
	}
	lout << "\n";
}


std::string largeInt::serialize() const
{
	std::stringstream stm;
	
	stm << *this;

	return stm.str();
}

largeInt::largeInt(): number (nullptr), size(0), maxSize(0), sign(sign_t::positive)
{
	Print("ctor default");
	grow();
	number[size++] = 0;
}

largeInt::largeInt(const largeInt&nr): number (nullptr), size(0), maxSize(0), sign(sign_t::positive)
{
	Print("copy ctor");
	size = nr.size;
	maxSize = nr.maxSize;
	number = new dataType[maxSize];
	sign = nr.sign;
	std::memcpy(number,nr.number, size*sizeof(dataType));
}

largeInt::largeInt(long long nr):  number (nullptr), size(0), maxSize(0), sign(sign_t::positive)
{
	Print("ctor from int");
	add(nr);
}

largeInt::largeInt(largeInt&&nr):  number (std::move(nr.number)), size(std::move(nr.size)), maxSize(std::move(nr.maxSize)), sign(std::move(nr.sign))
{
	Print("move ctor");
	nr.number = nullptr;
}

largeInt::largeInt(const std::string &buffer):  number (nullptr), size(0), maxSize(0), sign(sign_t::positive)
{
	if (buffer.size())
	{
		if (buffer[0] == '-')
		{
			sign = sign_t::negative;
			std::string lbuffer(buffer.begin()+1, buffer.end());
			add(lbuffer);
		}
		else
		{
			add(buffer);
		}
	}
	else
	{
		add(0);
	}
}

largeInt::~largeInt()
{
	Print("dtor");
	if (nullptr != number)
	{
		delete [] number;
		number = nullptr;
	}
}

void largeInt::grow()
{
	dataType * tmp = new dataType[largeInt::DATA_SIZE + maxSize];
	std::memcpy(tmp, number, maxSize*sizeof(dataType));
	std::swap(tmp,number);
	maxSize += largeInt::DATA_SIZE; 

	delete [] tmp;
}

largeInt::const_iterator begin(const largeInt &nr)
{
	return nr.cbegin();
}

largeInt::const_iterator end(const largeInt &nr)
{
	return nr.cend();
}

std::ostream& operator << (std::ostream &stm, const largeInt& nr)
{
	std::vector <largeInt::dataType> printList {};
	for (auto it : nr)
	{	
		printList.push_back(it);
	}
	if (nr.sign == largeInt::sign_t::negative)
	{
		std::cout << "-";
	}
	for (std::vector<largeInt::dataType>::reverse_iterator it = printList.rbegin(); it != printList.rend(); ++it)
	{
		stm << short(*it);
	}
	return stm;
}

std::istream& operator >> (std::istream &stm, largeInt& nr)
{
	std::string buffer;
	stm >> buffer;
	nr.reset();
	nr.add(buffer);
	return stm;
}

largeInt::iterator largeInt::begin() const
{
	return number;	
}

largeInt::const_iterator largeInt::cbegin() const
{
	return number;
}

largeInt::iterator largeInt::end() const
{
	return number + size;
}

largeInt::const_iterator largeInt::cend() const
{
	return number + size;
}

const largeInt & largeInt::operator=(const largeInt& nr)
{
	if (this != &nr)
	{
		delete [] number;
		size = nr.size;
		maxSize = nr.maxSize;
		number = new dataType[maxSize];
		std::memcpy(number, nr.number, size*sizeof(dataType));
		sign = nr.sign;
	}
	return *this;
}

largeInt & largeInt::operator=(largeInt&& nr)
{
	std::swap(this->number, nr.number);
	size = size;
	maxSize = nr.maxSize;
	sign = nr.sign;
	return *this;
}

bool largeInt::operator== (const largeInt & nr) const
{
	if (this == &nr)
	{
		return true;
	}
	if (this->size != nr.size || this->sign != nr.sign)
	{
		return false;
	}
	for (largeInt::const_iterator it1 = this->cbegin(), it2 = nr.cbegin();
		it1 != this->cend() && it2 != nr.cend(); ++it1, ++it2)
	{
		if (*it1 != *it2)
		{
			return false;
		}
	}
	return true;
}

bool largeInt::operator<  (const largeInt & nr) const
{
	if (this == &nr)
	{
		return false;
	}
	if (this->sign != nr.sign ) 
	{
		if (this->sign == largeInt::sign_t::negative)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (this->size > nr.size)
	{
		return false;
	}	
	if (this->size < nr.size)
	{
		return true;
	}
	for (largeInt::dataSizeType it = this->size-1; it > 0; --it)
	{
		Print ("Comparing this->[",it,"] with nr.number[",it,"] => ", this->number[it], " ", nr.number[it]);
		if (this->number[it] > nr.number[it])
		{
			return false;
		}
		if (this->number[it] < nr.number[it])
		{
			return true;
		}
	}
	if (this->number[0] >= nr.number[0])
	{
		return false;
	}
	if (this->number[0] < nr.number[0])
	{
		return true;
	}
	return false;
}

bool largeInt::operator>  (const largeInt & nr) const
{
	if (this == &nr)
	{
		return false;
	}
	if (this->size < nr.size ) 
	{
		return false;
	}	
	if (this->sign != nr.sign && nr.sign == largeInt::sign_t::negative)
	{
		return true;
	}
	if (this->size > nr.size)
	{
		return true;
	}
	for (largeInt::dataSizeType it1 = this->size-1, it2 = nr.size-1; it1 > 0 && it2 > 0; --it1, --it2)
	{
		if (this->number[it1] < nr.number[it2])
		{
			return false;
		}
		if (this->number[it1] > nr.number[it2])
		{
			return true;
		}
	}
	if (this->number[0] <= nr.number[0])
	{
		return false;
	}
	if (this->number[0] > nr.number[0])
	{
		return true;
	}
	return false;
}

bool largeInt::operator<= (const largeInt & nr) const
{
	return (*this) < nr || (*this) == nr;
}

bool largeInt::operator>= (const largeInt & nr) const
{
	return (*this) > nr || (*this) == nr;
}

const largeInt operator+(const largeInt & a, const largeInt&b)
{
	Print("");
	if (a.sign == b.sign && a.sign == largeInt::sign_t::negative)
	{
		largeInt ret {a.abs() + b.abs()};
		ret.sign = largeInt::sign_t::negative;
		return std::move(ret);
	}
	if (a.sign != b.sign)
	{
		if (a.sign == largeInt::sign_t::positive)
		{
			return std::move(a - b.abs());
		}
		else
		{
			return std::move(a.abs() - b);
		}
	}	
	largeInt c{};
	c.size = 0;
	largeInt::const_iterator cta = a.cbegin(), ctb = b.cbegin();
	largeInt::dataType rest = 0;
	for (; cta != a.cend() && ctb != b.cend(); ++cta, ++ctb)
	{
		if (c.size == c.maxSize)
		{
			c.grow();
		}
		c.number[c.size] = rest + (*cta) + (*ctb);
		rest = c.number[c.size] / 10;
		c.number[c.size] = c.number[c.size] % 10;
		++(c.size);
	}
	if (cta != a.cend() || ctb != b.cend())
	{
		Print("");
		largeInt::const_iterator it {}, itend {};
		if (cta != a.cend())
		{
			it = cta;
			itend = a.cend();
		}
		else
		{
			it = ctb;
			itend = b.cend();
		}
		for(; it != itend; ++it)
		{
			if (c.size == c.maxSize)
			{
				c.grow();
			}
			c.number[c.size] = rest + (*it);
			rest = c.number[c.size] / 10;
			c.number[c.size] = c.number[c.size] % 10;
			++(c.size);
		}
	}
	if (rest)
	{
		if (c.size == c.maxSize)
		{
			c.grow();
		}
		c.number[c.size] = rest;
		++(c.size);
	}
	return c;
}

const largeInt operator+(long long a, const largeInt&b)
{
	return b + largeInt(a);
}

const largeInt operator+(const largeInt & a, long long b)
{
	return b + a;
}

const largeInt operator-(const largeInt &a, const largeInt &b)
{	
	if (a.sign == b.sign && a.sign == largeInt::sign_t::negative)
	{
		return std::move(b.abs() - a);
	}
	if (a.sign != b.sign)
	{
		if (b.sign == largeInt::sign_t::negative)	
		{
			return std::move(a + b.abs());
		}
		else
		{
			largeInt ret {a.abs() + b};
			ret.sign = largeInt::sign_t::negative;
			return std::move(ret);
		}
	}
	if (b > a)
	{
		largeInt ret {b - a};
		ret.sign = largeInt::sign_t::negative;
		return std::move(ret);
	}
	
	if (b == a)
	{
		return std::move(largeInt {0});
	}
	largeInt::dataType rest = 0;	
	largeInt c{};
	c.size = 0;
	largeInt::const_iterator cta = a.cbegin(), ctb = b.cbegin(); 
	for (; cta != a.cend() && ctb != b.cend(); ++cta, ++ctb)
	{
		if (*cta < (*ctb + rest))
		{
			c.number[c.size] = 10 + *cta - *ctb - rest;
			rest = 1; 
		}
		else
		{
			c.number[c.size] = *cta - *ctb - rest;
			rest = 0;
		}
		++(c.size);
	}
	for (; cta != a.cend(); ++cta)
	{
		if (*cta < rest)
		{
			c.number[c.size] = 10 + *cta - rest;
			rest = 1;
		}
		else
		{
			c.number[c.size] = *cta - rest;
			rest = 0;
		}
		++(c.size);
	}
	c.trim();
	if (c.size == 0)
	{
		c.number[c.size] = 0;
		++(c.size);
	}
	return c;
}

const largeInt operator-(long long a, const largeInt &b)
{
	return largeInt{a} - b;
}

const largeInt operator-(const largeInt &a, long long b)
{
	return a - largeInt{b};
}

const largeInt & largeInt::operator++()
{
	if (this->sign == largeInt::sign_t::negative)
	{
		return --(*this);
	}
	inc();

	return *this;
}

const largeInt largeInt::operator++(int)
{
	if (this->sign == largeInt::sign_t::negative)
	{
		return (*this)--;
	}
	inc();
	return *this;
}

const largeInt & largeInt::operator--()
{
	if (this->sign == largeInt::sign_t::negative)
	{
		return ++(*this);
	}
	dec();
	return *this;
}

const largeInt largeInt::operator--(int)
{
	if (this->sign == largeInt::sign_t::negative)
	{
		return (*this)++;
	}
	dec();
	return *this;
}

bool operator== (long long a, const largeInt & nr)
{
	return largeInt {a} == nr;
}	

bool operator<  (long long a, const largeInt & nr)
{
	return largeInt {a} < nr;
}

bool operator>  (long long a, const largeInt & nr)
{
	return largeInt{a} > nr;
}

bool operator<= (long long a, const largeInt & nr)
{
	return largeInt {a} <= nr;
}

bool operator>= (long long a, const largeInt & nr)
{
	return largeInt{a} >= nr;
}

void largeInt::add(long long nr)
{
	if (nr < 0)
	{
		sign = sign_t::negative;
		nr = nr * (-1);
	}
	if (nr == 0)
	{
		if (size == maxSize)
		{
			grow();
		}
		number[size++] = 0;
		return;
	}
	while (nr)
	{
		if (size == maxSize)
		{
			grow();
		}
		number[size++] = nr % 10;
		nr = nr / 10;
	}
}
void largeInt::add(const std::string& buffer)
{
	for (std::string::const_reverse_iterator it = buffer.crbegin(); it != buffer.crend(); ++it)
	{
		if (!std::isdigit(static_cast<unsigned char> (*it)))
		{
			throw std::exception(); 	
		}
		else
		{
			add(int(*it - '0'));
		}
	}
}

const largeInt operator*(const largeInt &a, const largeInt &b)
{
	Print("");
	largeInt c {};
	const largeInt *m1 = nullptr;
	const largeInt *m2 = nullptr;

	if (a < b)
	{
		m1 = &b;
		m2 = &a;
	}
	else
	{
		m1 = &a;
		m2 = &b;
	}
	
	largeInt::dataType rest = 0;
	Print("Operator ", a, " * ",b);
	for (largeInt::dataSizeType cta = 0; cta < m2->size; ++cta)
	{
		Print ("Interm result ", c);
		Print("cta ", cta);
		largeInt::dataSizeType currPos = cta;
		Print("currPos ", currPos);
		for (largeInt::dataSizeType ctb = 0; ctb < m1->size; ++ctb)
		{
			Print("c.number[",currPos,"] ", c.number[currPos]);
			if (c.size == c.maxSize)
			{
				c.grow();
			}
			Print ("Operator = ", rest, " + ", m2->number[cta] , " * ", m1->number[ctb], " + ", (currPos < c.size ? c.number[currPos]:0) );			
			largeInt::dataType rez = rest + m2->number[cta] * m1->number[ctb] + (currPos < c.size ? c.number[currPos]:0);
			Print("rez ", rez);
			rest = rez / 10;
			Print("rest ", rest);
			c.number[currPos] = rez % 10;
			Print("c.number[",currPos,"] ", c.number[currPos]);
			if (currPos == c.size)
			{
				++(c.size);
				if (c.size == c.maxSize)
				{
					c.grow();
				}
				c.number[c.size] = 0;
			}
			++currPos;
			Print("c.size ", c.size);
			Print("currPos ", currPos);
		}
		if (0 != rest)
		{
			c.number[currPos] = rest;
			Print("c.number[",currPos,"] ", c.number[currPos]);
			if (currPos == c.size)
			{
				++(c.size);
				if (c.size == c.maxSize)
				{
					c.grow();
				}
				c.number[c.size] = 0;
			}
			Print("c.size ", c.size);
		}
		rest = 0;
		Print("Intermediary result ", c);
	}
	if (rest != 0)
	{
		c.number[c.size] = rest;
		++c.size;
	}
	largeInt::sign_t ret_sign {a.sign != b.sign? largeInt::sign_t::negative : largeInt::sign_t::positive};
	c.sign = ret_sign;
	return c;
}

const largeInt operator*(long long a, const largeInt &b)
{
	return largeInt{a} * b;
}
const largeInt operator*(const largeInt &a, long long b)\
{
	return largeInt{b} * a;
}

const largeInt largeInt::devide (const largeInt &a, const largeInt &b, const devType tp)
{
	auto cmp = [] (int a1, int b1) { return (a1 >= b1 ? true : false);};
	largeInt c{a}, ret{};
	ret.reset();
	std::vector<largeInt::dataType> div;
	for (largeInt::dataSizeType it = a.size - b.size + 1; it > 0; --it)
	{
		largeInt::dataType dg = 0;
		largeInt::dataType rest = 0;
		while ((c.size - it + 1 > b.size) || (c.size - it + 1 == b.size && compare(c.number + (c.size - b.size), b.number, cmp, b.size)))
		{		
			rest = 0;
			for (largeInt::dataSizeType cit = 0; cit != b.size; ++cit)
			{
				if (c.number[cit + it - 1] < rest + b.number[cit])
				{
					c.number[cit + it - 1] = 10 + c.number[cit + it - 1] - rest - b.number[cit];
					rest = 1;
				}
				else
				{
					c.number[cit + it - 1] = c.number[cit + it - 1] - rest - b.number[cit];
					rest = 0;
				}
			}
			if (c.size - it + 1 > b.size)
			{
				c.number[c.size - 1] -= rest;
			}
			c.trim();
			dg++;	
		}
		if (tp == devType::devider)
		{
			if (0 != dg || div.size())
			{
				div.push_back(dg);
			}
		}
	}
	if (tp == devType::devider)
	{
		for (auto it = div.crbegin(); it != div.crend(); ++it)
		{
			ret.add(*it);
		}
		if (ret.size == 0)
		{
			ret.add(0);
		}
		return ret;
	}
	else
	{
		return c;
	}
}
	
const largeInt operator/(const largeInt &a, const largeInt &b)
{
	Print ("");
	if (a < b)
	{
		return largeInt{0};
	}
	else if (a == b)
	{
		return largeInt{1};
	}
	else
	{
		return largeInt::devide(a, b, largeInt::devType::devider);
	}
	return largeInt{};
}

const largeInt operator/(long long a, const largeInt &b)
{
	return largeInt {a} / b;
}

const largeInt operator/(const largeInt &a, long long b)
{
	return a / largeInt {b};
}
	
const largeInt operator%(const largeInt &a, const largeInt &b)
{
	if (a < b)
	{
		return a;
	}
	if (a == b)
	{
		return 0;
	}
	else
	{
		return largeInt::devide(a, b, largeInt::devType::remainder);
	}
	return largeInt {};
}

const largeInt operator%(long long a, const largeInt &b)
{
	return largeInt {a} % b;
}

const largeInt operator%(const largeInt &a, long long b)
{
	return a % largeInt {b};
}

void largeInt::inc()
{
	dataType rest = 1;
	for (largeInt::dataSizeType it = 0; it < size  && rest; ++it)
	{
		dataType rez = number[it] + rest;
		rest = rez / 10;
		number[it] = rez % 10;
	}
}

void largeInt::dec()
{
	dataType rest = 1;
	if (this->size == 1 && this->number[0] == 0)
	{
		inc();
		this->sign = largeInt::sign_t::negative;
	}
	for (dataSizeType it = 0; it < size  && rest; ++it)
	{
		dataType rez = number[it] - rest;
		if (rez < 0)
		{
			rez = 9;
			rest = 1;
		}
		else
		{
			rest = 0;
		}
		number[it] = rez;
	}
	if (this->number[this->size-1] == 0)
	{
		if (this->size != 1)
		{
			this->size--;	
		}
	}
}

void largeInt::trim()
{
	Print("");
	if (size == 1)
	{
		return;
	}

	dataSizeType count = 0;
	Print("size ", size);
	for (dataSizeType ct = size; ct > 0; --ct)
	{
		Print("ct ", ct);
		Print("number[ct-1] ", number[ct - 1]);
		if (0 == number[ct-1])
		{
			count++;
		}
		else
		{
			break;
		}
	}
	Print("count ", count);
	if (count)
	{
		size -= count;
	}
}
