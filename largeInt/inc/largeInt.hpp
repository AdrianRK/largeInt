/*
 * =====================================================================================
 *
 *       Filename:  largeInt.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/05/2018 00:22:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef LARGEINT_INC_LARGEINT_HPP
#define LARGEINT_INC_LARGEINT_HPP

class largeInt;

std::ostream& operator << (std::ostream &stm, const largeInt& nr);
std::istream& operator >> (std::istream &stm, largeInt& nr);

bool operator== (long long a, const largeInt & nr);	
bool operator<  (long long a, const largeInt & nr);	
bool operator>  (long long a, const largeInt & nr);	
bool operator<= (long long a, const largeInt & nr);
bool operator>= (long long a, const largeInt & nr);

const largeInt operator+(const largeInt & a, const largeInt &b);
const largeInt operator+(long long a, const largeInt&b);
const largeInt operator+(const largeInt & a, long long b);

const largeInt operator-(const largeInt &a, const largeInt &b);
const largeInt operator-(long long a, const largeInt &b);
const largeInt operator-(const largeInt &a, long long b);

const largeInt operator*(const largeInt &a, const largeInt &b);
const largeInt operator*(long long a, const largeInt &b);
const largeInt operator*(const largeInt &a, long long b);

const largeInt operator/(const largeInt &a, const largeInt &b);
const largeInt operator/(long long a, const largeInt &b);
const largeInt operator/(const largeInt &a, long long b);

const largeInt operator%(const largeInt &a, const largeInt &b);
const largeInt operator%(long long a, const largeInt &b);
const largeInt operator%(const largeInt &a, long long b);
	

class largeInt
{
private:
	using dataType = short;
	using dataSizeType = std::size_t;
public:
	largeInt();
	largeInt(const largeInt&);
	largeInt(const std::string &);
	largeInt(largeInt&&);
	largeInt(long long);
	~largeInt();

	const largeInt & operator=(const largeInt& nr);
	largeInt & operator=(largeInt&& nr);
	bool operator== (const largeInt & nr) const;	
	bool operator<  (const largeInt & nr) const;	
	bool operator>  (const largeInt & nr) const;	
	bool operator<= (const largeInt & nr) const;
	bool operator>= (const largeInt & nr) const;

	bool operator== (long long nr) const { return *this == largeInt {nr};}
	bool operator<  (long long nr) const { return *this <  largeInt {nr};}
	bool operator>  (long long nr) const { return *this >  largeInt {nr};}	
	bool operator<= (long long nr) const { return *this <= largeInt {nr};}
	bool operator>= (long long nr) const { return *this >= largeInt {nr};}
	
	const largeInt & operator++();
	const largeInt operator++(int);
	const largeInt & operator--();
	const largeInt operator--(int);

	friend bool operator== (long long a, const largeInt & nr);	
	friend bool operator<  (long long a, const largeInt & nr);	
	friend bool operator>  (long long a, const largeInt & nr);	
	friend bool operator<= (long long a, const largeInt & nr);
	friend bool operator>= (long long a, const largeInt & nr);


	friend const largeInt operator+(const largeInt & a, const largeInt &b);
	friend const largeInt operator+(long long a, const largeInt&b);
	friend const largeInt operator+(const largeInt & a, long long b);
	
	friend const largeInt operator-(const largeInt &a, const largeInt &b);
	friend const largeInt operator-(long long a, const largeInt &b);
	friend const largeInt operator-(const largeInt &a, long long b);
	
	friend const largeInt operator*(const largeInt &a, const largeInt &b);
	friend const largeInt operator*(long long a, const largeInt &b);
	friend const largeInt operator*(const largeInt &a, long long b);
	
	friend const largeInt operator/(const largeInt &a, const largeInt &b);
	friend const largeInt operator/(long long a, const largeInt &b);
	friend const largeInt operator/(const largeInt &a, long long b);
	
	friend const largeInt operator%(const largeInt &a, const largeInt &b);
	friend const largeInt operator%(long long a, const largeInt &b);
	friend const largeInt operator%(const largeInt &a, long long b);
	
	const largeInt abs() const {largeInt ret{*this}; ret.sign = sign_t::positive; return std::move(ret);}

	using iterator = dataType *;
	using const_iterator = const dataType *;
	iterator begin() const;
	const_iterator cbegin() const;
	iterator end() const;
	const_iterator cend() const;

	friend std::ostream& operator << (std::ostream &stm, const largeInt& nr);
	friend std::istream& operator >> (std::istream &stm, largeInt& nr);

	std::string serialize() const;

private:
	enum class sign_t
	{
		positive,
		negative	
	};

	enum class devType
	{
		devider,
		remainder
	};
		
	void grow();
	void trim();
	void add(long long nr);
	void reset() {size = 0; sign = sign_t::positive;}
	void inc();
	void dec();
	void add(const std::string&);
	const static largeInt devide (const largeInt &a, const largeInt &b, const devType tp);
	void PrintDBG() const;
	dataType * number;
	dataSizeType size;
	dataSizeType maxSize;
	sign_t sign;
	static constexpr dataSizeType DATA_SIZE = 100;
};

#endif

