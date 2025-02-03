#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>

template <class T>
void drucke_vector(const std::vector<T> &elemente)
{
    for (const auto &element : elemente)
    {
        std::cout << element << " -> ";
    }
    std::cout << std::endl;
}

std::vector<size_t> merge(const std::vector<size_t> &left, const std::vector<size_t> &right)
{
    std::vector<size_t> list(left.size() + right.size());
    int i = 0, j = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] < right[j])
        {
            list[i + j] = left[i];
            i++;
        }
        else
        {
            list[i + j] = right[j];
            j++;
        }
    }

    while (i < left.size())
    {
        list[i + j] = left[i];
        i++;
    }

    while (j < right.size())
    {
        list[i + j] = right[j];
        j++;
    }

    return list;
}

std::vector<size_t> merge_sort(const std::vector<size_t> &input)
{
    if (input.size() <= 1)
    {
        return input;
    }
    int middle = input.size() / 2;

    // Zweites Argument ist exklusiv
    std::vector<size_t> left(input.begin(), input.begin() + middle);
    std::vector<size_t> right(input.begin() + middle, input.end());
    return merge(merge_sort(left), merge_sort(right));
}

int main()
{
    std::srand(unsigned(std::time(nullptr)));
    std::vector<size_t> zahlen(10000000);
    std::generate(zahlen.begin(), zahlen.end(), std::rand);

    // drucke_vector(zahlen);
    std::cout << "Sortiere..." << std::endl;
    zahlen = merge_sort(zahlen);
    std::cout << "Sortiert. (" << std::endl;
    // drucke_vector(zahlen);
}