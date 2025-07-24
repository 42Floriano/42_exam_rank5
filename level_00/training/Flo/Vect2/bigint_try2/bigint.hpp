#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>

class bigint {
    private:
        std::string _val;
        void removeZero();
        std::string addStrings(const std::string s1, const std::string s2);
    public:
        bigint();
        bigint(unsigned int i);
        bigint(const std::string& val);
        bigint(const bigint& bi);
        bigint& operator=(const bigint& rhs);
        ~bigint();

        bigint operator+(const bigint& bi);
        bigint& operator+=(const bigint& bi);

        void print(std::ostream &os) const;
};

std::ostream& operator<<(std::ostream& os, const bigint& bi);

#endif