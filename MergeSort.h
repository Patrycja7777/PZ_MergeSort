/**
* @file MergeSort.h
 * @brief Sortowanie tablic o stałym rozmiarze przez scalanie.
 */

#ifndef MERGESORT_H
#define MERGESORT_H

#include <array>
#include <cstddef>

/**
 * @brief Stabilne sortowanie tablicy przez scalanie.
 * @tparam T Typ elementów tablicy.
 * @tparam N Liczba elementów tablicy.
 */
template <typename T, std::size_t N>
class MergeSort
{
public:
    /**
     * @brief Sortuje tablicę w porządku niemalejącym.
     * @param[in,out] dane Tablica do posortowania.
     */
    void sort(std::array<T, N>& dane) const;

private:
    /** @brief Rekurencyjnie sortuje zakres [od, doIndeksu). */
    void uporzadkuj(std::array<T, N>& dane,
                    std::array<T, N>& pomocnicza,
                    std::size_t od, std::size_t doIndeksu) const;

    /** @brief Scala uporządkowane zakresy [od, podzial) i [podzial, doIndeksu). */
    void polacz(std::array<T, N>& dane,
                std::array<T, N>& pomocnicza,
                std::size_t od, std::size_t podzial,
                std::size_t doIndeksu) const;
};

#include "MergeSort.cpp"

#endif