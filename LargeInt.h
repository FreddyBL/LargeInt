/*
	LargeInt library to perform arithmetical operations on large integer numbers:

	Operations included:
		- Addition
		- Substraction
		- Product
		- Exponents
		- Divition and modulo
		- Absolute value
		- Square root
*/



#pragma once
#include <vector>
#include <string>
#include <array>
#include <sstream>




class LargeInt
{

	static const int MAX_DIGITS = 10000;

public:

	LargeInt();
	LargeInt(const std::string&& nstr);
	LargeInt(const std::string& nstr);
	LargeInt(int N);
	std::string to_str() const;
	size_t length() const;
	LargeInt abs() const;

	char sign() const 
	{
		if(m_isNegative)
			return -1;
		else 
			return 1;
	}
	//Arithmetic operators:
	LargeInt operator+(const LargeInt& rhs);
	LargeInt operator-(const LargeInt& rhs);
	LargeInt operator*(const LargeInt& rhs);
	LargeInt operator/(const LargeInt& rhs);
	LargeInt operator%(const LargeInt& rhs);
	LargeInt operator>>(int exponent);

	//Self arithmetic operators
	LargeInt& operator+=(const LargeInt& rhs);
	LargeInt& operator*=(const LargeInt& rhs);
	LargeInt& operator-=(const LargeInt& rhs);
	LargeInt& operator/=(const LargeInt& rhs);
	LargeInt& operator%=(const LargeInt& rhs);

	//Comparison operators:
	bool operator==(const LargeInt& rhs) const;
	bool operator==(const LargeInt&& rhs) const;
	bool operator!=(const LargeInt& rhs) const;
	bool operator!=(const LargeInt&& rhs) const;
	bool operator>(const LargeInt& rhs) const;
	bool operator>(const LargeInt&& rhs) const;
	bool operator<(const LargeInt& rhs) const;
	bool operator<(const LargeInt&& rhs) const;
	bool operator>=(const LargeInt& rhs) const;
	bool operator>=(const LargeInt&& rhs) const;
	bool operator<=(const LargeInt& rhs) const;
	bool operator<=(const LargeInt&& rhs) const;


	//Rvalue reference overloads
	LargeInt operator*(LargeInt&& rhs);
	LargeInt operator/(LargeInt&& rhs);
	LargeInt operator%(LargeInt&& rhs);
	LargeInt operator+(LargeInt&& rhs);
	LargeInt operator-(LargeInt&& rhs);

	//Self:
	LargeInt& operator+=(LargeInt&& rhs);
	LargeInt& operator*=(LargeInt&& rhs);
	LargeInt& operator-=(LargeInt&& rhs);
	LargeInt& operator/=(LargeInt&& rhs);
	LargeInt& operator%=(LargeInt&& rhs);



private:
	bool m_isNegative;
	std::vector<char> m_digitVector = std::vector<char>(MAX_DIGITS, 0);
	size_t m_totalDigits;

	
	void initialize_constructor_str(const std::string& nstr);
	void initialize_constructor_int(int N);
	std::vector<char>::const_iterator vbegin() const;
	std::vector<char>::const_iterator vend() const;
	std::vector<char>::const_reverse_iterator vrbegin() const;
	std::vector<char>::const_reverse_iterator vrend() const;
	LargeInt multiply(const LargeInt& lhs, const LargeInt& rhs);
	LargeInt add(const LargeInt& a, const LargeInt& b);
	LargeInt substract(const LargeInt& lhs, const LargeInt& rhs);
	LargeInt divide(const LargeInt& A, const LargeInt& b, LargeInt& remainder);

};


LargeInt::LargeInt() : m_isNegative{ false }, m_totalDigits{ 0 }
{
	initialize_constructor_int(0);
}
LargeInt::LargeInt(const std::string&& nstr) : m_isNegative{ false }, m_totalDigits{ 0 }
{
	initialize_constructor_str(nstr);
}

LargeInt::LargeInt(const std::string& nstr) : m_isNegative{ false }, m_totalDigits{ 0 }
{
	initialize_constructor_str(nstr);
}

LargeInt::LargeInt(int N) : m_isNegative{ false }, m_totalDigits{ 0 }
{
	initialize_constructor_int(N);
}


std::string LargeInt::to_str() const
{
	std::stringstream strm;
	if (m_isNegative)
	{
		strm << '-';
	}

	for (int i = m_totalDigits - 1, min = 0; i >= min; i--)
	{

		strm << char(m_digitVector[i] + '0');
	}
	return strm.str();

}
size_t LargeInt::length() const
{
	return m_totalDigits;
}

LargeInt LargeInt::abs() const
{
	LargeInt ret(*this);
	if (ret.m_isNegative)
		ret.m_isNegative = false;
	return ret;
}


LargeInt& LargeInt::operator*=(LargeInt&& rhs) {*this = (*this * rhs); return *this;}
LargeInt& LargeInt::operator/=(LargeInt&& rhs) {*this = (*this / rhs); return *this;}
LargeInt& LargeInt::operator%=(LargeInt&& rhs) {*this = (*this % rhs); return *this;}
LargeInt& LargeInt::operator+=(LargeInt&& rhs) {*this = (*this + rhs); return *this;}
LargeInt& LargeInt::operator-=(LargeInt&& rhs) {*this = (*this - rhs); return *this;}


LargeInt LargeInt::operator*(LargeInt&& rhs) { return (*this * rhs);}
LargeInt LargeInt::operator/(LargeInt&& rhs) { return (*this / rhs);}
LargeInt LargeInt::operator%(LargeInt&& rhs) { return (*this % rhs);}
LargeInt LargeInt::operator+(LargeInt&& rhs) { return (*this + rhs);}
LargeInt LargeInt::operator-(LargeInt&& rhs) { return (*this - rhs);}

LargeInt LargeInt::operator+(const LargeInt & rhs)
{
	LargeInt ret;
	if (m_isNegative && rhs.m_isNegative)
	{
		ret = add(rhs, *this);
		ret.m_isNegative = true;
	}
	else if (m_isNegative && !rhs.m_isNegative)
	{
		ret = substract(rhs, *this);
		if (abs() > rhs.abs())
		{
			ret.m_isNegative = true;
		}
	}
	else if (!m_isNegative && rhs.m_isNegative)
	{
		ret = substract(rhs, *this);
		if (rhs.abs() > abs())
		{
			ret.m_isNegative = true;
		}
	}
	else
	{
		ret = add(rhs, *this);
		ret.m_isNegative = false;
	}
	return ret;
}

LargeInt& LargeInt::operator+=(const LargeInt & rhs)
{
	*this = (*this + rhs);
	return *this;
}
LargeInt & LargeInt::operator*=(const LargeInt & rhs)
{
	*this = (*this * rhs);
	return *this;
}
LargeInt& LargeInt::operator/=(const LargeInt& rhs)
{
	*this = (*this / rhs);
	return *this;
}
LargeInt& LargeInt::operator%=(const LargeInt& rhs)
{
	*this = (*this % rhs);
	return *this;
}
LargeInt LargeInt::operator>>(int exponent)
{
	if (exponent < 0)
		throw "Invalid exponent";

	if (exponent == 0)
	{
		return LargeInt(1);
	}

	else if (exponent == 1)
		return *this;

	LargeInt ret{ 1 };
	for (int i = 0; i < exponent; i++)
	{
		ret *= *this;
	}
	return ret;
}

LargeInt& LargeInt::operator-=(const LargeInt & rhs)
{
	*this = (*this - rhs);
	return *this;

}

LargeInt LargeInt::operator-(const LargeInt & rhs)
{
	LargeInt ret;
	if (m_isNegative && rhs.m_isNegative)
	{
		ret = substract(rhs, *this);
		if (abs() > rhs.abs())
		{
			ret.m_isNegative = true;
		}
	}
	else if (m_isNegative && !rhs.m_isNegative)
	{
		ret = add(rhs, *this);
		ret.m_isNegative = true;
	}
	else if (!m_isNegative && rhs.m_isNegative)
	{
		ret = add(rhs, *this);
		ret.m_isNegative = false;
	}
	else
	{
		ret = substract(*this, rhs);
		if (rhs.abs() > abs())
		{
			ret.m_isNegative = true;
		}
	}
	return ret;
}

LargeInt LargeInt::operator*(const LargeInt & rhs)
{
	return multiply(*this, rhs);
}

LargeInt LargeInt::operator/(const LargeInt & rhs)
{
	LargeInt r;
	return divide(*this, rhs, r);
}

LargeInt LargeInt::operator%(const LargeInt & rhs)
{
	LargeInt r;
	divide(*this, rhs, r);
	return r;
}

bool LargeInt::operator==(const LargeInt & rhs) const
{
	if (m_totalDigits != rhs.m_totalDigits)
		return false;

	if (m_isNegative && !rhs.m_isNegative)
		return false;

	if (!m_isNegative && rhs.m_isNegative)
		return false;

	for (int i = 0, imax = m_totalDigits; i < imax; i++)
	{
		if (m_digitVector[i] != rhs.m_digitVector[i])
		{
			return false;
		}
	}
	return true;
}
bool LargeInt::operator==(const LargeInt && rhs) const
{
	return (*this == rhs);
}

bool LargeInt::operator!=(const LargeInt & rhs) const
{
	return !(*this == rhs);
}
bool LargeInt::operator!=(const LargeInt && rhs) const
{
	return !(*this == rhs);
}
//*this(lhs) > rhs
bool LargeInt::operator>(const LargeInt & rhs) const
{

	if (m_isNegative && !rhs.m_isNegative)
		return false;

	else if (!m_isNegative && rhs.m_isNegative)
		return true;

	else if (m_totalDigits > rhs.m_totalDigits && (!m_isNegative && !rhs.m_isNegative))
		return true;

	else if (m_totalDigits < rhs.m_totalDigits && (m_isNegative && rhs.m_isNegative))
		return true;

	else if (m_totalDigits == rhs.m_totalDigits)
	{
		for (int i = m_totalDigits - 1, min = 0; i >= min; i--)
		{
			if (m_isNegative && rhs.m_isNegative)
			{
				if (m_digitVector[i] < rhs.m_digitVector[i])
				{
					return true;
				}
				else if (m_digitVector[i] > rhs.m_digitVector[i])
				{
					return false;
				}
			}
			else
			{
				if (m_digitVector[i] > rhs.m_digitVector[i])
				{
					return true;
				}
				else if (m_digitVector[i] < rhs.m_digitVector[i])
				{
					return false;
				}
			}
		}
	}
	return false;
}
bool LargeInt::operator>(const LargeInt && rhs) const
{
	return (*this > rhs);
}
bool LargeInt::operator<(const LargeInt & rhs) const
{
	if (*this == rhs)
		return false;

	return !(*this > rhs);
}
bool LargeInt::operator<(const LargeInt && rhs) const
{
	return (*this < rhs);
}
bool LargeInt::operator>=(const LargeInt & rhs) const
{
	if (*this == rhs)
		return true;

	return (*this > rhs);
}
bool LargeInt::operator>=(const LargeInt && rhs) const
{
	return (*this >= rhs);
}

bool LargeInt::operator<=(const LargeInt & rhs) const
{
	return !(*this > rhs);
}
bool LargeInt::operator<=(const LargeInt && rhs) const
{
	return (*this <= rhs);
}

std::vector<char>::const_iterator LargeInt::vbegin() const
{
	return m_digitVector.cbegin();
}

std::vector<char>::const_iterator LargeInt::vend() const
{
	return (m_digitVector.cbegin() + m_totalDigits);
}

std::vector<char>::const_reverse_iterator LargeInt::vrbegin() const
{
	return (m_digitVector.crend() - m_totalDigits);
}

std::vector<char>::const_reverse_iterator LargeInt::vrend() const
{
	return m_digitVector.crend();
}

void LargeInt::initialize_constructor_int(int N)
{
	if (N < 0)
	{
		m_isNegative = true;
		N *= -1;
	}
	else if (N == 0)
	{
		m_digitVector[0] = 0;
		m_totalDigits = 1;
		return;
	}
	int idx = 0;
	while (N > 0)
	{
		char digit = N % 10;
		m_digitVector[idx] = digit;
		N /= 10;
		idx++;
	}
	m_totalDigits = idx;
}


void LargeInt::initialize_constructor_str(const std::string & nstr)
{
	if (nstr.empty())
		throw "No number was input.";


	m_isNegative = false;

	auto iteratorRend = nstr.rend();

	size_t len = nstr.length();

	int idx = 0;
	if (nstr[0] == '-') {
		m_isNegative = true;
		--iteratorRend;
		len -= 1;
		if (!len)
		{
			throw "Invalid expression entered.";
		}
		idx++;
	}

	if (nstr[idx] == '0')
	{
		m_totalDigits = 1;
		m_digitVector[0] = 0;
		return;
	}

	if (len >= MAX_DIGITS)
	{
		throw "Maximum number of digits reached";
	}

	m_totalDigits = len;
	int count = 0;
	for (auto rit = nstr.rbegin(); rit != iteratorRend; ++rit)
	{
		if (isdigit(*rit))
		{
			m_digitVector[count] = (*rit - '0');
		}
		else
		{
			throw "Input was not numerical.";
		}
		count++;
	}
}

LargeInt LargeInt::multiply(const LargeInt & lhs, const LargeInt & rhs)
{
	LargeInt ret("0");
	if (lhs.m_totalDigits == 1 && lhs.m_digitVector[0] == 0)
	{
		return ret;
	}
	else if (rhs.m_totalDigits == 1 && rhs.m_digitVector[0] == 0)
	{
		return ret;
	}

	LargeInt max;
	LargeInt min;
	if (lhs.m_totalDigits >= rhs.m_totalDigits)
	{
		max = lhs;
		min = rhs;
	}
	else
	{
		max = rhs;
		min = lhs;
	}
	char carry = 0;
	int global_idx = 0;  int tmp_idx = 0;
	for (int i = 0, imax = min.m_totalDigits; i < imax; i++)
	{
		LargeInt tmp;
		int carry = 0;
		tmp_idx = global_idx;
		for (int k = 0, kmax = max.m_totalDigits; k < kmax; k++)
		{
			char digitProduct = max.m_digitVector[k] * min.m_digitVector[i] + carry;
			tmp.m_digitVector[tmp_idx] = digitProduct % 10;
			digitProduct /= 10;
			carry = digitProduct % 10;
			tmp_idx++;

		}
		tmp.m_totalDigits = max.m_totalDigits + global_idx;
		if (carry)
		{
			tmp.m_digitVector[max.m_totalDigits + global_idx] = carry;
			tmp.m_totalDigits++;
		}

		ret += tmp;
		global_idx++;

	}
	if (max.m_isNegative && min.m_isNegative)
	{
		ret.m_isNegative = false;
	}
	else if (max.m_isNegative || min.m_isNegative)
	{
		ret.m_isNegative = true;
	}
	return ret;
}
LargeInt LargeInt::add(const LargeInt & a, const LargeInt & b)
{
	LargeInt ret;
	char carry = 0;
	if (a.m_totalDigits >= b.m_totalDigits)
	{
		for (int i = 0, max = a.m_totalDigits; i < max; i++)
		{

			char sum = a.m_digitVector[i] + b.m_digitVector[i] + carry;
			carry = 0;
			if (sum >= 10)
			{
				carry = 1;
				sum -= 10;
			}
			ret.m_digitVector[i] = sum;
		}
		if (carry)
		{
			ret.m_digitVector[a.m_totalDigits] = 1;
			ret.m_totalDigits = a.m_totalDigits + 1;
		}
		else
		{
			ret.m_totalDigits = a.m_totalDigits;
		}
	}
	else //b is greater
	{
		for (int i = 0, max = b.m_totalDigits; i < max; i++)
		{

			char sum = a.m_digitVector[i] + b.m_digitVector[i] + carry;
			carry = 0;
			if (sum >= 10)
			{
				carry = 1;
				sum -= 10;
			}
			ret.m_digitVector[i] = sum;
		}
		if (carry)
		{
			ret.m_digitVector[b.m_totalDigits] = 1;
			ret.m_totalDigits = b.m_totalDigits + 1;
		}
		else
		{
			ret.m_totalDigits = b.m_totalDigits;
		}
	}
	return ret;
}

LargeInt LargeInt::substract(const LargeInt & lhs, const LargeInt & rhs)
{
	LargeInt max;
	LargeInt min;
	if (lhs.abs() > rhs.abs())
	{
		max = lhs;
		min = rhs;
	}
	else
	{
		max = rhs;
		min = lhs;
	}

	LargeInt ret;
	char carry = 0;
	for (int i = 0, upper = max.m_totalDigits; i < upper; i++)
	{

		char sub = max.m_digitVector[i] - min.m_digitVector[i] - carry;
		if (sub < 0)
		{
			sub += 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		ret.m_digitVector[i] = sub;
	}
	int step = 0;
	for (int i = max.m_totalDigits - 1, min = 0; i >= min; i--)
	{
		if (ret.m_digitVector[i] != 0)
			break;
		step++;
	}
	if (step == max.m_totalDigits)
	{
		ret = LargeInt("0");
		ret.m_totalDigits = 1;
	}
	else
	{
		ret.m_totalDigits = max.m_totalDigits - step;
	}
	return ret;
}

LargeInt LargeInt::divide(const LargeInt & A, const LargeInt & b, LargeInt & remainder)
{
	if (b == 0)
	{
		throw "Division by zero";
	}

	//Hello
	if (A.abs() < b.abs())
	{
		remainder = A;
		return LargeInt(0);
	}
	if (A == b)
	{
		remainder = LargeInt(0);
		return LargeInt(1);
	}
	int chunk_size = b.m_totalDigits;
	auto itA = (A.vbegin() + A.m_totalDigits - chunk_size);
	LargeInt tmpA = 0;
	LargeInt dec = 1;

	std::vector<LargeInt> factorTable = std::vector<LargeInt>(10, 0);
	for (int i = 0; i <= 9; i++)
	{
		factorTable[i] = multiply(b, i);
		factorTable[i].m_isNegative = false;
	}

	for (int i = 0; i < chunk_size; i++)
	{
		tmpA += dec * (*itA);
		itA++;
		dec *= 10;
	}
	auto ritA = (A.vrbegin() + chunk_size);
	if (tmpA < b)
	{
		tmpA *= 10;
		tmpA += *ritA;
		ritA++;
	}

	std::vector<char> ans = std::vector<char>(A.m_totalDigits, 0);
	LargeInt ret = 0;
	int curIdx = 0;

	int i = 9;
	for (; i >= 0; i--)
	{
		if (factorTable[i] <= tmpA)
		{
			ans[curIdx] = i;
			curIdx++;
			break;
		}
	}
	for (; ritA != A.vrend(); ++ritA)
	{
		tmpA -= factorTable[i];
		tmpA = (tmpA * 10) + *ritA;
		i = 9;
		for (; i >= 0; i--)
		{
			if (factorTable[i] <= tmpA)
			{
				ans[curIdx] = i;
				curIdx++;
				break;
			}
		}
	}
	tmpA -= factorTable[i];
	ans.resize(curIdx);
	int idx = 0;
	for (auto rit = ans.rbegin(); rit != ans.rend(); ++rit)
	{
		ret.m_digitVector[idx] = *rit;
		idx++;
	}
	ret.m_totalDigits = curIdx;

	if (A.m_isNegative && b.m_isNegative)
	{
		ret.m_isNegative = false;
		if (!(tmpA.m_totalDigits == 1 && tmpA.m_digitVector[0] == 0))
		{
			tmpA.m_isNegative = false;
		}
	}
	else if (A.m_isNegative || b.m_isNegative)
	{
		ret.m_isNegative = true;
		if (!(tmpA.m_totalDigits == 1 && tmpA.m_digitVector[0] == 0))
		{
			tmpA.m_isNegative = true;
		}
	}
	remainder = tmpA;
	return ret;
}

