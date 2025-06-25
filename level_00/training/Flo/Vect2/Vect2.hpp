/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falberti <falberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:31:37 by falberti          #+#    #+#             */
/*   Updated: 2025/06/25 14:58:13 by falberti         ###   ########.fr       */
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

        int operator[](int pos) const;
        int& operator[](const int pos);

        void print(std::ostream& os) const;
        friend std::ostream& operator<<(std::ostream& os, const vect2& vec);

};

#endif