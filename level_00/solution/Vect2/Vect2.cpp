#include "vect2.hpp"

// Constructor
vect2::vect2(int x, int y) : x(x), y(y) {}

// Addition operator
vect2 vect2::operator+(const vect2& other) const {
    return vect2(x + other.x, y + other.y);
}

// Subtraction operator
vect2 vect2::operator-(const vect2& other) const {
    return vect2(x - other.x, y - other.y);
}

// Multiplication by scalar
vect2 vect2::operator*(int scalar) const {
    return vect2(x * scalar, y * scalar);
}

// Equality operator
bool vect2::operator==(const vect2& other) const {
    return x == other.x && y == other.y;
}

// Access components with []
int vect2::operator[](int index) const {
    return (index == 0) ? x : y;
}

void vect2::print(std::ostream& os) const {
    os << "{" << x << ", " << y << "}";
}

// Friend function to print the vector
std::ostream& operator<<(std::ostream& os, const vect2& v) {
    v.print(os);
    return os;
}