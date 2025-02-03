#include <vector>
#include <iostream>
#include <string>

template <class T>
void drucke_vector(const std::vector<T> &elemente)
{
    for (const auto &element : elemente)
    {
        std::cout << element << std::endl;
    }
}

void betrag(std::vector<int> &zahlen)
{
    for (int &zahl : zahlen)
    {
        if (zahl < 0)
        {
            zahl = -zahl;
        }
    }
}

void lese_und_fuege_am_ende_ein(std::vector<int> &bisher)
{
    int aktuell = -1;
    while (aktuell != 42)
    {
        std::cout << "Naechste Zahl:" << std::endl;
        std::cin >> aktuell;
        bisher.push_back(aktuell);
    }
    std::cout << "Alle Zahlen gelesen" << std::endl;
}

int main()
{
    std::vector<int> zahlen = {1, 2, 3, -4};
    drucke_vector(zahlen);
    betrag(zahlen);
    drucke_vector(zahlen);
    std::vector<std::string> zeichen = {"Hallo", "Du", "Wurst"};
    drucke_vector(zeichen);
    lese_und_fuege_am_ende_ein(zahlen);
    drucke_vector(zahlen);
}