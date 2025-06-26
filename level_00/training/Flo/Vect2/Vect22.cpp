#include "Vect22.hpp"

vect2::vect2(int x, int y) :  _x(x), _y(y){}
vect2::vect2(const vect2& vec) : _x(vec._x), _y(vec._y){}
vect2& vect2::operator=(const vect2& rhs){
    if (this != &rhs){
        this->_x = rhs._x;
        this->_y = rhs._y;
    }
    return *this;
}
vect2::~vect2(){}

int vect2::operator[](const int num) const{
    return (num == 0) ? this->_x : this->_y;
}

int& vect2::operator[](const int num){
    return (num == 0) ? _x : _y;
}

vect2 vect2::operator+(int num) const{
    return vect2(_x + num, _y + num);
}
vect2 vect2::operator+(const vect2 vec) const{
    return vect2(_x + vec._x, _y + vec._y);
}
vect2 vect2::operator*(int num) const{
    return vect2(_x * num, _y * num);
}
vect2 vect2::operator*(const vect2 vec) const{
    return vect2(_x * vec._x, _y * vec._y);
}
vect2 vect2::operator-(int num) const{
    return vect2(_x - num, _y - num);
}
vect2 vect2::operator-(const vect2 vec) const{
    return vect2(_x - vec._x, _y - vec._y);
}

vect2& vect2::operator+=(const vect2& vec){
    _x += vec._x;
    _y += vec._y;
    return *this;
}

vect2& vect2::operator+=(const int num){
    _x += num;
    _y += num;
    return *this;
}

vect2& vect2::operator-=(const vect2& vec){
    _x -= vec._x;
    _y -= vec._y;
    return *this;
}

vect2& vect2::operator-=(const int num){
    _x -= num;
    _y -= num;
    return *this;
}

bool vect2::operator==(const vect2 vec) const{
    return (_x == vec._x && _y == vec._y) ? true : false;
}
bool vect2::operator!=(const vect2 vec) const{
    return (_x != vec._x || _y != vec._y) ? true : false;
}


vect2& vect2::operator++(){
    this->_x++;
    this->_y++;
    return *this;
}

vect2 vect2::operator++(int){
    vect2 temp(*this);
    this->_x++;
    this->_y++;
    return temp;
}

vect2& vect2::operator--(){
    this->_x--;
    this->_y--;
    return *this;
}

vect2 vect2::operator--(int){
    vect2 temp(*this);
    this->_x--;
    this->_y--;
    return temp;
}

void vect2::print(std::ostream& os) const{
    os << "{" << _x << ", " << _y << "}" << std::endl;
}

vect2 operator+(int num, const vect2 vec){
    return vect2(vec._x + num, vec._y + num);
}
// vect2 operator+(const vect2 vec, int num){
//     return vect2(vec._x + num, vec._y + num);
// }
vect2 operator*(int num, const vect2 vec){
    return vect2(vec._x * num, vec._y * num);
}
// vect2 operator*(const vect2 vec, int num){
//     return vect2(vec._x * num, vec._y * num);
// }
vect2 operator-(int num, const vect2 vec){
    return vect2(num - vec._x, num - vec._y);
}
// vect2 operator-(const vect2 vec, int num){
//     return vect2(vec._x - num, vec._y - num);
// }
std::ostream& operator<<(std::ostream& os, const vect2& vec){
    vec.print(os);
    return os;
}