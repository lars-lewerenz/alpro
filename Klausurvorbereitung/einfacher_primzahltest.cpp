#include <iostream>

bool is_prime(const size_t &input)
{
    long i = 2;
    while (i * i <= input)
    {
        if (input % i == 0)
        {
            return false;
        }
        i++;
    }
    return true;
}

int main()
{
    std::cout << "Welche Zahl soll getestet werden?" << std::endl;
    size_t zahl = -1;
    std::cin >> zahl;
    if (is_prime(zahl))
    {
        std::cout << "Diese Zahl ist tatsaechlich eine Primzahl." << std::endl;
    }
    else
    {
        std::cout << "Diese Zahl ist keine Primzahl" << std::endl;
    }
}