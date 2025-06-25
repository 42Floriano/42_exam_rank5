#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2 {
private:
    int x, y;

public:
    // Constructor
    vect2(int x = 0, int y = 0);

    // Addition operator
    vect2 operator+(const vect2& other) const;

    // Subtraction operator
    vect2 operator-(const vect2& other) const;

    // Multiplication by scalar
    vect2 operator*(int scalar) const;

    // Equality operator
    bool operator==(const vect2& other) const;

    // Access components with []
    int operator[](int index) const;
    // Friend function to print the vector
	void print(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const vect2& v);
#endif // VECT2_HPP