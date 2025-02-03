#include <iostream>

double radiziere(const double &input, const float &toleranz)
{
    double t = input;
    while (((t * t) - input) >= toleranz or (input - t * t) >= toleranz)
    {
        t = 0.5 * (t + input / t);
    }
    return t;
}

double radiziere(const double &input)
{
    float klein = 1e-5;
    return radiziere(input, klein);
}

int main()
{
    std::cout << "Welche Zahl soll radiziert werden?" << std::endl;
    double zahl = -1.0;
    std::cin >> zahl;
    double wurzel = radiziere(zahl);
    std::cout << "Die Wurzel von " << std::to_string(zahl) << " ist " << std::to_string(wurzel) << std::endl;
}