#include "bigint.hpp"

bigint::bigint() : _val("0"){}


bigint::bigint(unsigned int i){
    std::ostringstream oss;
    oss << i;
    _val = oss.str();
    std::reverse(_val.begin(), _val.end());
}

bigint::bigint(const std::string& val){
    bool isDigi = true;
    for(std::string::const_iterator it = val.begin(); it < val.end(); ++it)
        if (!::isdigit(*it))
            isDigi = false;
    if (val.empty() || isDigi == false)
        _val = "0";
    else {
    _val = val;
    std::reverse(_val.begin(), _val.end());
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


void bigint::removeZero(){
    while(_val.size() && _val[_val.size() - 1] == '0')
        _val.erase(_val.size() - 1);
}

std::string bigint::addStrings(const std::string s1, const std::string s2){
    std::string final;
    size_t result = 0, rest = 0, len = 0;
    len = (s1.size() > s2.size()) ? s1.size() : s2.size();
    for (size_t i = 0; i < len ; i++){
        int s1_r = (i < s1.size()) ? s1[i] - '0' : 0; 
        int s2_r = (i < s2.size()) ? s2[i] - '0' : 0;
        result = s1_r + s2_r + rest;
        final.push_back((result % 10) + '0');
        rest = result / 10;
    }
    if (rest) final.push_back(rest + '0');
    return final;
}

bigint bigint::operator+(const bigint& bi){
    bigint res(addStrings(_val, bi._val));
    return res;
}

bigint& bigint::operator+=(const bigint& bi){
    _val = addStrings(_val, bi._val);
    return *this;
}

void bigint::print(std::ostream& os) const{
    std::string res = _val;
    std::reverse(res.begin(), res.end());
    os << res << std::endl;
}

std::ostream& operator<<(std::ostream& os, const bigint& bi){
    bi.print(os);
    return os;
}