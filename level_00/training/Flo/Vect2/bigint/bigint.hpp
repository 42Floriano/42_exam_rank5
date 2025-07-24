#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>

class bigint {
    private:
        std::string _val;
        void removeZero();
        std::string addStrings(const std::string& s1, const std::string& s2);

    public:
        bigint();
        bigint(unsigned int val);
        bigint(const std::string& val);
        bigint(const bigint& other);
        bigint& operator=(const bigint& rhs);
        ~bigint();

        bigint operator+(const bigint& bi);
        bigint& operator+=(const bigint& bi);

        bool operator==(const bigint& bi) const;
        bool operator!=(const bigint& bi) const;
        bool operator<(const bigint& bi) const;
        bool operator>(const bigint& bi) const;
        bool operator<=(const bigint& bi) const;
        bool operator>=(const bigint& bi) const;

        bigint operator<<(size_t i);
        bigint operator>>(size_t i);
        bigint operator<<(const bigint& bi);
        bigint operator>>(const bigint& bi);

        bigint& operator<<=(size_t i);
        bigint& operator>>=(size_t i);
        bigint& operator<<=(const bigint& bi);
        bigint& operator>>=(const bigint& bi);

        void print(std::ostream& os) const;
        
};

std::ostream& operator<<(std::ostream& os, const bigint& bi);


#endif /*  */
