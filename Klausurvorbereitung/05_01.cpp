#include <iostream>
#include <vector>

template <class T>
void drucke_vector(const std::vector<T> &elemente)
{
    for (const auto &element : elemente)
    {
        std::cout << element << " -> ";
    }
    std::cout << std::endl;
}

int min_sort_in_place(std::vector<int> &input)
{
    int vergleiche = 0;
    const int laenge = input.size();
    for (int index = 0; index < laenge; index++)
    {
        int kleinstes_index = index;
        for (int kleinerer_index = index + 1; kleinerer_index < laenge; kleinerer_index++)
        {
            vergleiche++;
            if (input[kleinerer_index] < input[kleinstes_index])
            {
                kleinstes_index = kleinerer_index;
            }
        }
        if (kleinstes_index != index)
        {
            int kleinstes = input[kleinstes_index];
            input[kleinstes_index] = input[index];
            input[index] = kleinstes;
        }
    }
    return vergleiche;
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
    std::vector<int> zahlen;
    lese_und_fuege_am_ende_ein(zahlen);
    drucke_vector(zahlen);
    std::cout << "Sortiere..." << std::endl;
    auto vergleiche = min_sort_in_place(zahlen);
    std::cout << "Sortiert. (" << vergleiche << " Vergleiche, " << zahlen.size() << " Zahlen)" << std::endl;
    drucke_vector(zahlen);
}