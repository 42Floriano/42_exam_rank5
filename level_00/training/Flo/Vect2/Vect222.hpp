/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect222.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:17:09 by falberti          #+#    #+#             */
/*   Updated: 2025/07/04 15:20:51 by falberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT222_HPP
#define VECT222_HPP

#include <iostream>

class vect2 {
    private:
        int _x;
        int _y;
    public:
        vect2(int x = 0, int y = 0);
        vect2(const vect2& other);
        vect2& operator=(const vect2& rhs);
        ~vect2();

        int operator[](int num) const;
        int& operator[](int num);

        vect2 operator*(int num);
        vect2 operator+(int num);
        vect2 operator/(int num);
        vect2 operator-(int num);

        vect2 operator*(const vect2& vec) const;
        vect2 operator+(const vect2& vec) const;
        vect2 operator/(const vect2& vec) const;
        vect2 operator-(const vect2& vec) const;

        vect2& operator+=(const vect2& vec);
        vect2& operator+=(int num);

        vect2& operator-=(const vect2& vec);
        vect2& operator-=(int num);

        vect2& operator/=(const vect2& vec);
        vect2& operator/=(int num);

        vect2& operator*=(const vect2& vec);
        vect2& operator*=(int num);

        vect2 operator++(int);
        vect2& operator++();

        vect2 operator--(int);
        vect2& operator--();

        bool operator!=(const vect2& vec) const;
        bool operator==(const vect2& vec) const;
        
        void print(std::ostream& os) const;
        friend vect2 operator*(int num, const vect2& vec);
        friend vect2 operator+(int num, const vect2& vec);
        friend vect2 operator/(int num, const vect2& vec);
        friend vect2 operator-(int num, const vect2& vec);
        friend std::ostream& operator<<(std::ostream &os, const vect2& vec);
};

#endif