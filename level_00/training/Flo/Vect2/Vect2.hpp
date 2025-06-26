/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floriano <floriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:31:37 by falberti          #+#    #+#             */
/*   Updated: 2025/06/26 12:01:13 by floriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
#define VECT2_HPP

# include <iostream>

class vect2 {
    private:
        int _x;
        int _y;
    public:
        vect2(int x = 0, int y = 0);
        vect2(const vect2& other);
        vect2& operator=(const vect2& rhs);
        ~vect2();

        vect2& operator+=(const vect2& vec);
        vect2& operator+=(int num);
        vect2& operator-=(const vect2& vec);
        vect2& operator-=(int num);
        vect2& operator*=(const vect2& vec);
        vect2& operator*=(int num);

        
        bool operator==(const vect2& vec) const;
        bool operator!=(const vect2& vec) const;

        vect2& operator++();
        vect2& operator--();
        vect2 operator++(int);
        vect2 operator--(int);
        

        int operator[](int pos) const;
        int& operator[](const int pos);

        vect2 operator+(int num) const;
        vect2 operator+(const vect2& vec) const;
        vect2 operator-(int num) const;
        vect2 operator-(const vect2& vec) const;
        vect2 operator*(int num) const;
        vect2 operator*(const vect2& vec) const;

        void print(std::ostream& os) const;
        friend std::ostream& operator<<(std::ostream& os, const vect2& vec);
        friend vect2 operator+(int num, const vect2& vec);
        friend vect2 operator-(int num, const vect2& vec);
        friend vect2 operator*(int num, const vect2& vec);

};

#endif