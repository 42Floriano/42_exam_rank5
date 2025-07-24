#include <iostream>
#include "bigint.hpp"

int main() {
    // Création de bigints
    bigint num1("200"), num2("942"), num3, num4(100);
    bigint num5 = num2;
    const bigint numC(60);

    // Test des opérateurs arithmétiques
    std::cout << num1 << num2 << num3 << num4 << num5 << numC << std::endl;
    std::cout << "num1 + num2 = " << (num1 + num2) << std::endl;
    num3 = num1;
    num3 += num2;
    std::cout << "num3 += num2: " << num3 << std::endl;

    bigint num8("999"), num9("999");
    
    // Test des comparaisons
    std::cout << "num8 == num9: " << (num8 == num9) << std::endl;
    std::cout << "num8 != num9: " << (num8 != num9) << std::endl;
    std::cout << "num8 < num9: " << (num8 < num9) << std::endl;
    std::cout << "num8 <= num9: " << (num8 <= num9) << std::endl;
    std::cout << "num8 > num9: " << (num8 > num9) << std::endl;
    std::cout << "num8 >= num9: " << (num8 >= num9) << std::endl;

    bigint num10("42");
    // Test des décalages avec entiers
    std::cout << "num1 << 2 = " << (num10 << 2) << std::endl;
    std::cout << "num1 >> 2 = " << (num10 >> 3) << std::endl;

    bigint num11("10");
    // // Test des décalages avec bigint
    std::cout << "num1 << num5 = " << (num10 << num1) << std::endl;
    std::cout << "num1 >> num5 = " << (num10 >> num1) << std::endl;

    // // Test des décalages avec bigint constant
    // std::cout << "num1 << numC = " << (num1 << numC) << std::endl;
    // std::cout << "num1 >> numC = " << (num1 >> numC) << std::endl;

    // // Test des affectations combinées avec décalages
    // num3 = num1;
    // num3 <<= 2;
    // std::cout << "num3 <<= 2: " << num3 << std::endl;
    // num3 >>= 1;
    // std::cout << "num3 >>= 1: " << num3 << std::endl;

    // // Test des affectations combinées avec bigint
    // num3 = num1;
    // num3 <<= num5;
    // std::cout << "num3 <<= num5: " << num3 << std::endl;
    // num3 >>= num5;
    // std::cout << "num3 >>= num5: " << num3 << std::endl;

    return 0;
}