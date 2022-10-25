#include <iostream>
#include <iomanip>

int powerof(int x, int y) {
    int res = 1;
    for (int i = 0; i < y; i++) {
        res *= x;
    }
    return res;
}

int main() {
    int x = 10;
    int y = 3;

    int res = powerof(x, y);

    std::cout << "\n\t" << x << " elevated to " << y << " is " << res << std::endl;

    //double z = 0.29;
    float z = 0.29;
    int w = (int) (z * x * x);

    if (z * x * x == 29)
        std::cout << "\n\t" << z << "*" << x * x << " is 29" << std::endl;
    else
        std::cout << "\n\t" << z << "*" << x * x << " is not 29 "
                  << std::endl;           
}
