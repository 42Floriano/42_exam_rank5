#ifndef VECT22_HPP
#define VECT22_HPP

#include <iostream>

class vect2 {
    private:
        int _x;
        int _y;
    public:
        vect2(int x = 0, int y = 0);
        vect2(const vect2& vec);
        vect2& operator=(const vect2& rhs);
        ~vect2();

        int operator[](const int num) const;
        int& operator[](const int num);

        vect2 operator+(int num) const;
        vect2 operator+(const vect2 vec) const;
        vect2 operator*(int num) const;
        vect2 operator*(const vect2 vec) const;
        vect2 operator-(int num) const;
        vect2 operator-(const vect2 vec) const;

        vect2& operator+=(const vect2& vec);
        vect2& operator+=(const int num);

        vect2& operator-=(const vect2& vec);
        vect2& operator-=(const int num);

        bool operator==(const vect2 vec) const;
        bool operator!=(const vect2 vec) const;

        vect2& operator++();
        vect2 operator++(int);
        vect2& operator--();
        vect2 operator--(int);

        void print(std::ostream& os) const;
        friend vect2 operator+(int num, const vect2 vec);
        //friend vect2 operator+(const vect2 vec, int num);
        friend vect2 operator*(int num, const vect2 vec);
        //friend vect2 operator*(const vect2 vec, int num);
        friend vect2 operator-(int num, const vect2 vec);
        //friend vect2 operator-(const vect2 vec, int num);
        friend std::ostream& operator<<(std::ostream& os, const vect2& vec);
};

#endif