#include "bigint.hpp"

bigint::bigint() : _val("0"){}

void bigint::removeZero(){
    while (_val.size() > 1 && _val.back() == '0')
        _val.erase(_val.size() - 1);
}

bigint::bigint(unsigned int val){
    std::ostringstream oss;
    oss << val;
    _val = oss.str();
    std::reverse(_val.begin(), _val.end());
}

bigint::bigint(const std::string& input){
    if (input.empty() || !std::all_of(input.begin(), input.end(), ::isdigit))
        _val = "0";
    else {
        std::string rep = input;
        std::reverse(rep.begin(), rep.end());
        _val = rep;
        removeZero();
    }
}
bigint::bigint(const bigint& other) : _val(other._val){}

bigint& bigint::operator=(const bigint& rhs){
    if (this != &rhs){
        _val = rhs._val;
    }
    return *this;
}

bigint::~bigint(){}

std::string bigint::addStrings(const std::string& s1, const std::string& s2){
    std::string final;
    int val = 0;
    int ret = 0;
    size_t i = 0;
    size_t len = std::max(s1.size(), s2.size());

    for (i = 0; i < len; i++){
        int digiA = i < s1.size() ? s1[i] - '0' : 0;
        int digiB = i < s2.size() ? s2[i] - '0' : 0;
        val = digiA + digiB + ret;
        final.push_back((val % 10) + '0');
        ret = val / 10;
    }
    if(ret) final.push_back(ret + '0');
    return final;
}

bigint bigint::operator+(const bigint& bi){
    bigint res;
    res._val = this->addStrings(_val, bi._val);
    return res;
}

bigint& bigint::operator+=(const bigint& bi){
    _val = this->addStrings(_val, bi._val);
    return *this;
}

bool bigint::operator==(const bigint& bi) const{
    return (this->_val == bi._val);
}
bool bigint::operator!=(const bigint& bi) const{
    return (this->_val !=  bi._val);
}
bool bigint::operator<(const bigint& bi) const{
    if (this->_val.size() < bi._val.size())
        return true;
    if (this->_val.size() > bi._val.size())
        return false;
    std::string s1 = this->_val;
    std::string s2 = bi._val;
    std::reverse(s1.begin(), s1.end());
    std::reverse(s2.begin(), s2.end());
    for (size_t i = 0; i < s1.size(); i++){
        if(s1[i] < s2[i])
            return true;
        if(s1[i] > s2[i])
            return false;
        if(s1[i] == s2[i])
            continue;
    }
    return false;
}
bool bigint::operator>(const bigint& bi) const{
        if (this->_val.size() > bi._val.size())
        return true;
    if (this->_val.size() < bi._val.size())
        return false;
    std::string s1 = this->_val;
    std::string s2 = bi._val;
    std::reverse(s1.begin(), s1.end());
    std::reverse(s2.begin(), s2.end());
    for (size_t i = 0; i < s1.size(); i++){
        if(s1[i] > s2[i])
            return true;
        if(s1[i] < s2[i])
            return false;
        if(s1[i] == s2[i])
            continue;
    }
    return false;
}

bool bigint::operator<=(const bigint& bi) const {
    if (this->_val == bi._val)
        return true;
    if (this->_val.size() < bi._val.size())
        return true;
    if (this->_val.size() > bi._val.size())
        return false;
    std::string s1 = this->_val;
    std::string s2 = bi._val;
    std::reverse(s1.begin(), s1.end());
    std::reverse(s2.begin(), s2.end());
    for (size_t i = 0; i < s1.size(); i++){
        if(s1[i] < s2[i])
            return true;
        if(s1[i] > s2[i])
            return false;
        if(s1[i] == s2[i])
            continue;
    }
    return false;
}

bool bigint::operator>=(const bigint& bi) const{
    if (this->_val == bi._val)
        return true;
    if (this->_val.size() > bi._val.size())
        return true;
    if (this->_val.size() < bi._val.size())
        return false;
    std::string s1 = this->_val;
    std::string s2 = bi._val;
    std::reverse(s1.begin(), s1.end());
    std::reverse(s2.begin(), s2.end());
    for (size_t i = 0; i < s1.size(); i++){
        if(s1[i] > s2[i])
            return true;
        if(s1[i] < s2[i])
            return false;
        if(s1[i] == s2[i])
            continue;
    }
    return false;
}

bigint& bigint::operator<<(size_t i){
    std::string to_r = this->_val;
    std::reverse(to_r.begin(), to_r.end());
    for (size_t x = 0; x < i; x++)
        to_r.append("0");
    std::reverse(to_r.begin(), to_r.end());
    this->_val = to_r;
    return *this;
}
bigint& bigint::operator>>(size_t i){
    std::string to_r = this->_val;
    std::reverse(to_r.begin(), to_r.end());
    for (size_t x = 0; x < i; x++)
        to_r.pop_back();
    std::reverse(to_r.begin(), to_r.end());
    this->_val = to_r;
    return *this;
}

bigint& bigint::operator<<(const bigint& bi){
    size_t dix = 1;
    std::string to_r = this->_val;
    std::reverse(to_r.begin(), to_r.end());
    std::string s1 = bi._val;
    size_t len = s1.size();
    for(size_t i = 0; i < len; i++){
        for(size_t y = 0; y < ((size_t)(s1[i] - '0') * dix); y ++){
            to_r.append("0");
        }
        dix *= 10;
    }
     std::reverse(to_r.begin(), to_r.end());
    this->_val = to_r;
    return *this;
}

bigint& bigint::operator>>(const bigint& bi){
    size_t dix = 1;
    std::string to_r = this->_val;
    std::reverse(to_r.begin(), to_r.end());
    std::string s1 = bi._val;
    size_t len = s1.size();
    for(size_t i = 0; i < len; i++){
        for(size_t y = 0; y < ((size_t)(s1[i] - '0') * dix); y ++){
            to_r.pop_back();
        }
        dix *= 10;
    }
     std::reverse(to_r.begin(), to_r.end());
    this->_val = to_r;
    return *this;
}

void bigint::print(std::ostream& os) const{
    std::string to_r = _val;
    std::reverse(to_r.begin(), to_r.end());
    os <<  to_r << std::endl;
}

std::ostream& operator<<(std::ostream& os, const bigint& bi){
    bi.print(os);
    return os;
}