/**
 * @file mergesort.cpp
 * @brief Określa przebieg podziału danych i wybierania elementów podczas scalania.
 */

#ifndef MERGESORT_IMPLEMENTATION_INCLUDED
#define MERGESORT_IMPLEMENTATION_INCLUDED

#include "MergeSort.h"

template <typename T, std::size_t N>
void MergeSort<T, N>::sort(std::array<T, N>& dane) const
{
    if (N < 2)
    {
        return;
    }

    std::array<T, N> pomocnicza{};
    uporzadkuj(dane, pomocnicza, 0, N);
}

template <typename T, std::size_t N>
void MergeSort<T, N>::uporzadkuj(std::array<T, N>& dane,
                                std::array<T, N>& pomocnicza,
                                std::size_t od,
                                std::size_t doIndeksu) const
{
    const std::size_t liczbaElementow = doIndeksu - od;
    if (liczbaElementow < 2)
    {
        return;
    }

    const std::size_t podzial = od + liczbaElementow / 2;

    uporzadkuj(dane, pomocnicza, od, podzial);
    uporzadkuj(dane, pomocnicza, podzial, doIndeksu);
    polacz(dane, pomocnicza, od, podzial, doIndeksu);
}

template <typename T, std::size_t N>
void MergeSort<T, N>::polacz(std::array<T, N>& dane,
                            std::array<T, N>& pomocnicza,
                            std::size_t od, std::size_t podzial,
                            std::size_t doIndeksu) const
{
    std::size_t lewaPozycja = od;
    std::size_t prawaPozycja = podzial;

    for (std::size_t miejsce = od; miejsce < doIndeksu; ++miejsce)
    {
        /**
        * @brief Po wyczerpaniu prawej części wybór pada na lewą.
        *
        * Porównanie wartości następuje tylko wtedy, gdy obie są dostępne.
        */
        const bool wybierzLewa =
            lewaPozycja < podzial &&
            (prawaPozycja == doIndeksu ||
             dane[lewaPozycja] <= dane[prawaPozycja]);

        if (wybierzLewa)
        {
            pomocnicza[miejsce] = dane[lewaPozycja];
            ++lewaPozycja;
        }
        else
        {
            pomocnicza[miejsce] = dane[prawaPozycja];
            ++prawaPozycja;
        }
    }

    for (std::size_t miejsce = od; miejsce < doIndeksu; ++miejsce)
    {
        dane[miejsce] = pomocnicza[miejsce];
    }
}

#endif
