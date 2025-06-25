#include "Vect2.hpp"

vect2::vect2(int x, int y) : x(x), y(y)
{

}

vect2::vect2(const vect2 &other)
{
	x = other.x;
	y = other.y;
}

vect2& vect2::operator=(const vect2& other)
{
	if (this != &other)
	{
		this->x = other.x;
		this->y = other.y;
	}
	return *this;
}

vect2::~vect2()
{

}

vect2& vect2::operator++()
{
	this->x++;
	this->y++;
	return *this;
}

vect2 vect2::operator++(int)
{
	vect2 temp(*this);
	++(*this);
	return temp;
}

vect2& vect2::operator--()
{
	this->x--;
	this->y--;
	return *this;
}

vect2 vect2::operator--(int)
{
	vect2 temp(*this);
	--(*this);
	return temp;
}

vect2 vect2::operator+(const vect2& other) const
{
	return vect2(this->x + other.x, this->y + other.y);
}

vect2 vect2::operator+(int num) const
{
	return vect2(this->x + num, this->y + num);
}

vect2& vect2::operator+=(const vect2& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

vect2& vect2::operator+=(int num)
{
	this->x += num;
	this->y += num;
	return *this;
}
		
vect2 vect2::operator-(const vect2& other) const
{
	return vect2(this->x - other.x, this->y - other.y);
}

vect2 vect2::operator-(int num) const
{
	return vect2(this->x - num, this->y - num);
}

vect2& vect2::operator-=(const vect2& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

vect2& vect2::operator-=(int num)
{
	this->x -= num;
	this->y -= num;
	return *this;
}

bool vect2::operator==(const vect2& other) const
{
	return (this->x == other.x && this->y == other.y);
}

bool vect2::operator!=(const vect2& other) const
{
	return !(this->x == other.x && this->y == other.y);
}

vect2 vect2::operator*(const int num) const
{
	return vect2(this->x * num, this->y * num);
}

vect2 vect2::operator*(const vect2& other) const
{
	return vect2(this->x * other.x, this->y * other.y);
}

int vect2::operator[](const int pos) const
{
	return (pos == 0) ? x : y;
}

int& vect2::operator[](const int pos)
{
	return (pos == 0) ? x : y;
}

void vect2::print(std::ostream &os) const
{
	os << "{" << x << ", " << y << "}" << std::endl;
}

vect2 operator+(int num, const vect2& v)
{
	return vect2(num + v[0], num + v[1]);
}

vect2 operator-(int num, const vect2& v)
{
	return vect2(num - v[0], num - v[1]);
}

vect2 operator*(int num, const vect2& v)
{
	return vect2(num * v[0], num * v[1]);
}

std::ostream& operator<<(std::ostream& os, const vect2& vec)
{
	vec.print(os);
	return(os);
}