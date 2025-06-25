#include "bigint.hpp"

bigint::bigint() : digits("0")
{

}

bigint::bigint(unsigned int n)
{
	std::ostringstream os;
	os << n;
	digits = os.str();
	std::reverse(digits.begin(), digits.end());
}

void bigint::removezeros()
{
	while (digits.size() > 1 && digits.back() == '0')
		digits.pop_back();
}

bigint::bigint(const std::string &str)
{
	if (!str.size() || !std::all_of(str.begin(), str.end(), ::isdigit))
		digits = "0";
	else
	{
		digits = str;
		std::reverse(digits.begin(), digits.end());
		removezeros();
	}
}

bigint::bigint(const bigint &other)
{
	digits = other.digits;
}

bigint &bigint::operator=(const bigint &other)
{
	if (this != &other)
	{
		digits = other.digits;
	}
	return *this;
}

bigint::~bigint()
{

}

std::string bigint::addstrings(const std::string &s1, const std::string &s2)
{
	int ret = 0, val = 0;
	size_t size = std::max(s1.size(), s2.size());
	std::string final = "";

	for (size_t i = 0; i < size; i++)
	{
		val += i < s1.size() ? s1[i] - '0' : 0;
		val += i < s2.size() ? s2[i] - '0' : 0;
		val += ret;
		ret = val / 10;
		final.push_back(val % 10 + '0');
		val = 0;
	}
	if (ret)
		final.push_back(ret + '0');
	return final;
}

bigint bigint::operator+(const bigint &other)
{
	bigint result;
	result.digits = addstrings(this->digits, other.digits);
	return result;
}

bigint& bigint::operator+=(const bigint &other)
{
	*this = *this + other;
	return *this;
}

bool bigint::operator<(const bigint &other)
{
	if (digits.size() != other.digits.size())
		return digits.size() < other.digits.size();
	return std::lexicographical_compare(digits.rbegin(), digits.rend(),
									other.digits.rbegin(), other.digits.rend());
}

bool bigint::operator>(const bigint &other)
{
	if (digits.size() != other.digits.size())
		return digits.size() > other.digits.size();
	return std::lexicographical_compare(other.digits.rbegin(), other.digits.rend(),
									digits.rbegin(), digits.rend());
}

bool bigint::operator<=(const bigint &other)
{
	if (*this < other || *this == other)
		return true;
	return false;
}

bool bigint::operator>=(const bigint &other)
{
	if (*this > other || *this == other)
		return true;
	return false;
}

bigint bigint::operator>>(const int n)
{
	std::string str = digits;
	std::reverse(str.begin(), str.end());
	for (int i = 0; i < n ; i++)
	{
		if (str.empty())
		{
			str = "0";
			return (bigint(str));
		}
		str.pop_back();
	}
	return (bigint(str));
}

bigint bigint::operator<<(const int n)
{
	std::string str = digits;
	std::reverse(str.begin(), str.end());
	for (int i = 0; i < n; i++)
		str.push_back('0');
	return bigint(str);
}

bigint bigint::operator>>(const bigint &b)
{
	std::stringstream ss;
	std::string str = digits;
	std::reverse(str.begin(), str.end());
	bigint res(str);
	int shift;
	ss << b.digits;
	ss >> shift;
	res = *this >> shift;
	return res;
}

bigint bigint::operator<<(const bigint &b)
{
	std::stringstream ss;
	std::string str = digits;
	std::reverse(str.begin(), str.end());
	bigint res(str);
	int shift;
	ss << b.digits;
	ss >> shift;
	res = *this << shift;
	return res;
}

bigint &bigint::operator<<=(const int n)
{
	*this = *this << n;
	return *this;
}

bigint &bigint::operator>>=(const int n)
{
	*this = *this >> n;
	return *this;
}

bigint &bigint::operator<<=(const bigint &b)
{
	*this = *this << b;
	return *this;
}

bigint &bigint::operator>>=(const bigint &b)
{
	*this = *this >> b;
	return *this;
}

bool bigint::operator==(const bigint &other)
{
	if (*this < other || *this > other)
		return false;
	return true;
}

bool bigint::operator!=(const bigint &other)
{
	if (*this < other || *this > other)
		return true;
	return false;
}

void bigint::print(std::ostream &os) const
{
	std::string s = digits;
	std::reverse(s.begin(), s.end());
	os << s;
}

std::ostream& operator<<(std::ostream &os, const bigint &big)
{
	big.print(os);
	return os;
}