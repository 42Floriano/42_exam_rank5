#include "bigint.hpp"

bigint::bigint() : _val("0"){}
bigint::bigint(unsigned int i){
    std::ostringstream oss;
    oss << i;
    _val = oss.str();
}

void bigint::removeZero(){
    while (_val.size() > 1 && _val.back() == '0'){
        _val.erase(_val.size() - 1);
    }
}

bigint::bigint(const std::string& str){
    if (!str.size() || !std::all_of(str.begin(), str.end(), ::isdigit))
        _val = "0";
    _val = str;
    removeZero();
}

bigint::bigint(const bigint& bi) : _val(bi._val){}

bigint& bigint::operator=(const bigint& rhs){
    if(this != &rhs){
        _val = rhs._val;
    }
    return *this;
}

bigint::~bigint(){}

void bigint::print(std::ostream& os) const{
    for (size_t i = 0; i < _val.size(); i++){
        os << _val[i];
    }
    os << std::endl;
}

std::string bigint::addString(const std::string& s1, const std::string& s2){
    
}

// bigint& bigint::operator+=(const bigint& bi){
//     (void) bi;
//     return *this;
// }

std::ostream& operator <<(std::ostream& os, const bigint& bi){
    bi.print(os);
    return os;
}