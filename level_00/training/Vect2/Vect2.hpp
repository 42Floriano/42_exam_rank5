#ifndef VECT2_HPP
# define VECT2_HPP

# include <iostream>
class vect2 {
	private :
		int x, y;
	public :
		vect2(int x = 0, int y = 0);
		vect2(const vect2& other);
		vect2& operator=(const vect2& other);
		~vect2();

		
		vect2& operator++();
		vect2 operator++(int);
		vect2& operator--();
		vect2 operator--(int);
		
		vect2 operator+(const vect2& other) const;
		vect2 operator+(int num) const;
		vect2& operator+=(const vect2& other);
		vect2& operator+=(int num);
		vect2 operator-(const vect2& other) const;
		vect2 operator-(int num) const;
		vect2& operator-=(const vect2& other);
		vect2& operator-=(int num);
		bool operator==(const vect2& other) const;
		bool operator!=(const vect2& other) const;
		vect2 operator*(const int num) const;
		vect2 operator*(const vect2& other) const;
		int operator[](const int pos) const;
		int& operator[](const int pos);
		void print(std::ostream &os) const;
		friend std::ostream& operator<<(std::ostream& os, const vect2& vec);
		friend vect2 operator+(int num, const vect2& v);
		friend vect2 operator*(int num, const vect2& v);
		friend vect2 operator-(int num, const vect2& v);
};

#endif