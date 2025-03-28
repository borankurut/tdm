#include <iostream>

#include "mat3.h"

using namespace tdm;

int main()
{
    std::cout << " Determinant Example \n";
    Mat3 B(342.0f, -42.0f, 53.0f, 11.9f, -31.57f, 0.05f, 99.0f, 21.0f, -3.0f);
    std::cout << "Determinant of " << B << " is:" << B.determinant();

    return 0;
}
