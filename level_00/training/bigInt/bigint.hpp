#ifndef BIGINT_HPP
# define BIGINT_HPP

#include <iostream>
#include <sstream>
#include <algorithm>

class bigint {
	private :
		std::string digits;
		void removezeros();
		std::string addstrings(const std::string &s1, const std::string &s2);

	public :
		bigint();
		bigint(unsigned int n);
		bigint(const std::string &str);
		bigint(const bigint& other);
		bigint &operator=(const bigint& other);
		~bigint();

		bigint operator+(const bigint &other);
		bigint& operator+=(const bigint &other);
		bool operator<(const bigint &other);
		bool operator>(const bigint &other);
		bigint operator<<(const int n);
		bigint operator>>(const int n);
		bigint operator<<(const bigint &b);
		bigint operator>>(const bigint &b);
		bigint &operator<<=(const int n);
		bigint &operator>>=(const int n);
		bigint &operator<<=(const bigint &b);
		bigint &operator>>=(const bigint &b);
		bool operator<=(const bigint &other);
		bool operator>=(const bigint &other);
		bool operator==(const bigint &other);
		bool operator!=(const bigint &other);
		void print(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream &os, const bigint &big);

#endif