#include <array>
#include <queue>
#include <iostream>

template <class T>
void drucke_vector(const std::vector<T> &elemente)
{
    for (const auto &element : elemente)
    {
        std::cout << element << " -> ";
    }
    std::cout << std::endl;
}

template <int N>
class GerichteterGraph
{
public:
    void fuege_kante_ein(const int &start, const int &ende)
    {
        fuege_knoten_ein(start);
        fuege_knoten_ein(ende);
        adjazenzmatrix[start][ende] = true;
    }

    void loesche_kante(const int &start, const int &ende)
    {
        adjazenzmatrix[start][ende] = false;
    }

    bool existiert_kante(const int &start, const int &ende) const
    {
        return adjazenzmatrix[start][ende];
    }

    bool existiert_knoten(const int &index) const
    {
        return knoten[index];
    }

    void fuege_knoten_ein(const int &index)
    {
        knoten[index] = true;
    }

    void loese_knoten(const int &index)
    {
        for (int ende = 0; ende < N; ende++)
        {
            loesche_kante(index, ende);
        }
        knoten[index] = false;
    }

    void drucke() const
    {
        std::cout << "Adjazenzliste:" << std::endl;
        for (int index = 0; index < N; index++)
        {
            if (existiert_knoten(index))
            {
                std::cout << "- " << index << ": ";
                for (int ende = 0; ende < N; ende++)
                {
                    if (existiert_kante(index, ende))
                    {
                        std::cout << " " << ende;
                    }
                }
                std::cout << std::endl;
            }
        }
    }

    std::vector<int> breitensuche(const int &start)
    {
        std::vector<int> reachable;
        std::array<bool, N> markiert = {false};
        std::queue<int> queue;

        reachable.push_back(start);
        markiert[start] = true;
        queue.push(start);

        while (!queue.empty())
        {
            int aktuell = queue.front();
            queue.pop();
            for (int index = 0; index < N; index++)
            {
                if (markiert[index] || !(existiert_kante(aktuell, index)))
                {
                    continue;
                }
                markiert[index] = true;
                queue.push(index);
                reachable.push_back(index);
            }
        }
        return reachable;
    }

    std::vector<int> tiefensuche(std::array<bool, N> &markiert, const int &start)
    {
        std::vector<int> reachable;
        reachable.push_back(start);
        markiert[start] = true;
        for (int index = 0; index < N; index++)
        {
            if (markiert[index] or !(existiert_kante(start, index)))
            {
                continue;
            }
            std::vector<int> dfs = tiefensuche(markiert, index);
            reachable.insert(reachable.end(), dfs.begin(), dfs.end());
        }
        return reachable;
    }

private:
    std::array<std::array<bool, N>, N> adjazenzmatrix = {std::array<bool, N>({false})};
    std::array<bool, N> knoten = {false};
};

static const int KNOTENANZAHL = 12;

int main()
{
    GerichteterGraph<KNOTENANZAHL> graph;

    std::cout << "Existiert die Kante (1, 2)? -> " << graph.existiert_kante(1, 2) << std::endl;
    graph.fuege_kante_ein(1, 2);
    graph.fuege_kante_ein(1, 3);
    graph.fuege_kante_ein(3, 4);
    graph.fuege_kante_ein(3, 5);
    graph.fuege_kante_ein(4, 6);
    graph.fuege_kante_ein(1, 5);

    std::cout << "Existiert die Kante (1, 2)? -> " << graph.existiert_kante(1, 2) << std::endl;

    graph.drucke();

    std::cout << "Breitensuche:" << std::endl;
    drucke_vector(graph.breitensuche(1));

    std::cout << std::endl;

    std::cout << "Tiefensuche:" << std::endl;
    std::array<bool, KNOTENANZAHL> markierungen({false});
    drucke_vector(graph.tiefensuche(markierungen, 1));
}