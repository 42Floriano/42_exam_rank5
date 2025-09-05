#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

class bigint{
    private:
        std::string _val;
    public:
    bigint();
    bigint(const std::string& str);
    bigint(unsigned int i);
    bigint(const bigint& other);
    ~bigint();
    void removeZero();
    std::string addString(const std::string& s1, const std::string& s1);

    bigint& operator=(const bigint& rhs);
    // bigint operator+(const bigint& bi) const;
    // bigint& operator+=(const bigint& bi);
    // bool operator==(const bigint& bi) const;
    // bool operator!=(const bigint& bi) const;
    // bool operator<=(const bigint& bi) const;
    // bool operator>=(const bigint& bi) const;
    // bool operator<(const bigint& bi) const;
    // bool operator>(const bigint& bi) const;
    // bigint& operator<<(int i);
    // bigint& operator>>(int i);
    // bigint& operator<<(const bigint& bi);
    // bigint& operator>>(const bigint& bi);
    // bigint& operator<<=(int i);
    // bigint& operator>>=(int i);
    // bigint& operator<<=(const bigint& bi);
    // bigint& operator>>=(const bigint& bi);
    void print(std::ostream& os) const;
    friend std::ostream& operator <<(std::ostream& os, const bigint& bi);
};

#endif