/**
 * @file main.cpp
 * @brief Uruchamia porządkowanie dwóch zestawów liczb i prezentuje ich kolejność.
 */

#include "MergeSort.h"

#include <array>
#include <iostream>

/**
 * @brief Przygotowuje dane całkowite i ułamkowe oraz wypisuje wyniki ich sortowania.
 * @return Kod 0 oznaczający zakończenie programu.
 */
int main()
{
    std::array<int, 6> liczbyCalkowite = {{12, -7, 5, 0, 9, -2}};
    std::array<double, 5> liczbyRzeczywiste = {{4.75, -2.5, 0.8, 7.1, 1.25}};

    MergeSort<int, 6> porzadkowanieInt;
    MergeSort<double, 5> porzadkowanieDouble;

    porzadkowanieInt.sort(liczbyCalkowite);
    porzadkowanieDouble.sort(liczbyRzeczywiste);

    std::cout << "int:";
    for (std::size_t i = 0; i < liczbyCalkowite.size(); ++i)
    {
        std::cout << ' ' << liczbyCalkowite[i];
    }

    std::cout << "\ndouble:";
    for (std::size_t i = 0; i < liczbyRzeczywiste.size(); ++i)
    {
        std::cout << ' ' << liczbyRzeczywiste[i] << ';';
    }

    std::cout << '\n';
    return 0;
}
