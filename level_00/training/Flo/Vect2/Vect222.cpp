/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect222.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:16:56 by falberti          #+#    #+#             */
/*   Updated: 2025/07/04 15:20:33 by falberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vect222.hpp"

vect2::vect2(int x, int y) : _x(x), _y(y){}
vect2::vect2(const vect2& other) : _x(other._x), _y(other._y){}
vect2& vect2::operator=(const vect2& rhs){
    if (this != &rhs){
        _x = rhs._x;
        _y = rhs._y;
    }
    return *this;
}
vect2::~vect2(){}

int vect2::operator[](int num) const{
    return (num == 0) ? _x : _y;
}

int& vect2::operator[](int num){
    return (num == 0) ? _x : _y;
}

vect2 vect2::operator*(int num){
    return vect2(_x * num, _y * num);
}

vect2 vect2::operator+(int num){
    return vect2(_x + num, _y + num);
}
vect2 vect2::operator/(int num){
    return vect2(_x / num, _y / num);
}
vect2 vect2::operator-(int num){
    return vect2(_x - num, _y - num);
}

vect2 vect2::operator*(const vect2& vec) const{
    return vect2(_x * vec._x, _y * vec._y);
}

vect2 vect2::operator+(const vect2& vec) const{
    return vect2(_x + vec._x, _y + vec._y);
}

vect2 vect2::operator/(const vect2& vec) const{
    return vect2(_x / vec._x, _y / vec._y);
}

vect2 vect2::operator-(const vect2& vec) const{
    return vect2(_x - vec._x, _y - vec._y);
}

vect2& vect2::operator+=(const vect2& vec){
    _x += vec._x;
    _y += vec._y;
    return *this;
}

vect2& vect2::operator+=(int num){
    _x += num;
    _y += num;
    return *this;
}

vect2& vect2::operator-=(const vect2& vec){
    _x -= vec._x;
    _y -= vec._y;
    return *this;
}
vect2& vect2::operator-=(int num){
    _x -= num;
    _y -= num;
    return *this;
}

vect2& vect2::operator/=(const vect2& vec) {
    _x /= vec._x;
    _y /= vec._y;
    return *this;
}
vect2& vect2::operator/=(int num){
    _x /= num;
    _y /= num;
    return *this;
}

vect2& vect2::operator*=(const vect2& vec){
    _x *= vec._x;
    _y *= vec._y;
    return *this;
}

vect2& vect2::operator*=(int num){
    _x *= num;
    _y *= num;
    return *this;
}


vect2 vect2::operator++(int) {
    vect2 temp = *(this);
    _x++;
    _y++;
    return temp;
}
vect2& vect2::operator++(){
    _x++;
    _y++;
    return *this;
}

vect2 vect2::operator--(int){
    vect2 temp = *(this);
    _x--;
    _y--;
    return temp;
}

vect2& vect2::operator--(){
    _x--;
    _y--;
    return *this;
}

bool vect2::operator==(const vect2& vec) const{
    return (_x == vec._x && _y == vec._y) ? true : false;
}
bool vect2::operator!=(const vect2& vec) const{
    return (_x != vec._x || _y != vec._y) ? true : false;
}

void vect2::print(std::ostream& os) const{
    os << "{" << _x << ", " << _y << "}" << std::endl;
}

vect2 operator*(int num, const vect2& vec){
    return vect2(num * vec._x, num * vec._y);
}
vect2 operator+(int num, const vect2& vec){
    return vect2(num + vec._x, num + vec._y);
}
vect2 operator/(int num, const vect2& vec){
    return vect2(num / vec._x, num / vec._y);
}
vect2 operator-(int num, const vect2& vec){
    return vect2(num - vec._x, num - vec._y);
}
        
std::ostream& operator<<(std::ostream &os, const vect2& vec){
    vec.print(os);
    return(os);
}