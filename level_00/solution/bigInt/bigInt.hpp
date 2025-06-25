#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <algorithm>

class bigint {
private:
    std::string digits; // Stores the number in reverse (i.e., least significant digit first)

    // Private helper functions
    static std::string addStrings(const std::string& a, const std::string& b);
    void removeLeadingZeros();

public:
    // Constructors
    bigint();
    bigint(unsigned int num);
    bigint(const std::string& str);

    // Addition operators
    bigint operator+(const bigint& other) const;
    bigint& operator+=(const bigint& other);

    // Comparison operators
    bool operator==(const bigint& other) const;
    bool operator!=(const bigint& other) const;
    bool operator<(const bigint& other) const;
    bool operator>(const bigint& other) const;
    bool operator<=(const bigint& other) const;
    bool operator>=(const bigint& other) const;

    // Digit shift operators
    bigint operator<<(unsigned int shift) const;
    bigint operator>>(unsigned int shift) const;

	std::string getDigits(void) const;
};
// Output stream operator
std::ostream& operator<<(std::ostream& os, const bigint& num);

#endif // BIGINT_HPP