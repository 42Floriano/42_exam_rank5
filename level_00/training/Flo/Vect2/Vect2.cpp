/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:37:52 by falberti          #+#    #+#             */
/*   Updated: 2025/06/25 15:26:37 by falberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vect2.hpp"

vect2::vect2(int x, int y) : _x(x), _y(y){}
vect2::vect2(const vect2& other) : _x(other._x), _y(other._y){}
vect2& vect2::operator=(const vect2& rhs){
    if (this != &rhs){
        this->_x = rhs._x;
        this->_y = rhs._y;
    }
    return *this;
}
vect2::~vect2(){}

int vect2::operator[](const int pos) const{
    return (pos == 0) ? _x : _y;
}
int& vect2::operator[](const int pos){
    return (pos == 0) ? _x : _y;
}

vect2 vect2::operator+(int num) const{
    return vect2(_x + num, _y + num);
}
vect2 vect2::operator+(const vect2& vec) const{
    return vect2(_x + vec._x, _y + vec._y);
}

vect2 vect2::operator-(int num) const{
    return vect2(_x - num, _y - num);
}
vect2 vect2::operator-(const vect2& vec) const{
    return vect2(_x - vec._x, _y - vec._y);
}
vect2 vect2::operator*(int num) const{
    return vect2(_x * num, _y * num);
}
vect2 vect2::operator*(const vect2& vec) const{
    return vect2(_x * vec._x, _y * vec._y);
}

vect2 operator+(int num, const vect2& vec){
    return vect2(vec[0] + num, vec[1] + num);
}
vect2 operator-(int num, const vect2& vec){
    return vect2(num - vec[0], num - vec[1]);
}
vect2 operator*(int num, const vect2& vec){
    return vect2(vec[0] * num, vec[1] * num);
}



void vect2::print(std::ostream& os) const{
    os << "{" << _x << ", " << _y << "}" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const vect2& vec){
    vec.print(os);
    return(os);
}