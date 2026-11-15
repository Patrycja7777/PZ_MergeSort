/**
 * @file MergeSort.h
 * @brief Implementacja szablonowej klasy sortowania przez scalanie.
 */

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <cstddef>
#include <vector>

/**
 * @class MergeSort
 * @brief Szablonowa klasa realizująca algorytm sortowania przez scalanie.
 *
 * Klasa pozwala sortować tablice zawierające różne typy danych,
 * np. int, long int, float oraz double.
 *
 * Typ używany w szablonie musi obsługiwać operator porównania <.
 *
 * @tparam T Typ elementów znajdujących się w sortowanej tablicy.
 */
template <typename T>
class MergeSort
{
public:

    /**
     * @brief Sortuje podaną tablicę w kolejności rosnącej.
     *
     * Funkcja wykorzystuje algorytm Merge Sort.
     *
     * Jeżeli przekazany wskaźnik ma wartość nullptr albo tablica
     * zawiera mniej niż dwa elementy, funkcja kończy działanie
     * bez wykonywania sortowania.
     *
     * @param array Wskaźnik na pierwszy element tablicy.
     * @param size Liczba elementów znajdujących się w tablicy.
     */
    static void sort(T* array, std::size_t size)
    {
        if (array == nullptr || size < 2)
        {
            return;
        }

        mergeSort(array, 0, size - 1);
    }

private:

    /**
     * @brief Rekurencyjnie dzieli tablicę na mniejsze fragmenty.
     *
     * Funkcja dzieli wskazany zakres tablicy na dwie części,
     * sortuje każdą z nich, a następnie scala je w jeden
     * posortowany fragment.
     *
     * @param array Wskaźnik na sortowaną tablicę.
     * @param left Indeks pierwszego elementu fragmentu.
     * @param right Indeks ostatniego elementu fragmentu.
     */
    static void mergeSort(
        T* array,
        std::size_t left,
        std::size_t right)
    {
        if (left >= right)
        {
            return;
        }

        const std::size_t middle =
            left + (right - left) / 2;

        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);

        /*
         * Jeżeli ostatni element lewej części jest mniejszy
         * lub równy pierwszemu elementowi prawej części,
         * cały fragment jest już poprawnie posortowany.
         */
        if (!(array[middle + 1] < array[middle]))
        {
            return;
        }

        merge(array, left, middle, right);
    }

    /**
     * @brief Scala dwa posortowane fragmenty tablicy.
     *
     * Pierwszy fragment zajmuje zakres [left, middle],
     * natomiast drugi fragment zakres [middle + 1, right].
     *
     * Elementy są najpierw zapisywane w tablicy pomocniczej,
     * a następnie kopiowane do oryginalnej tablicy.
     *
     * @param array Wskaźnik na sortowaną tablicę.
     * @param left Indeks pierwszego elementu pierwszego fragmentu.
     * @param middle Indeks ostatniego elementu pierwszego fragmentu.
     * @param right Indeks ostatniego elementu drugiego fragmentu.
     */
    static void merge(
        T* array,
        std::size_t left,
        std::size_t middle,
        std::size_t right)
    {
        std::vector<T> temporary;

        temporary.reserve(right - left + 1);

        std::size_t leftIndex = left;
        std::size_t rightIndex = middle + 1;

        /*
         * Porównujemy elementy lewej i prawej części.
         * Mniejszy element trafia do tablicy pomocniczej.
         */
        while (leftIndex <= middle && rightIndex <= right)
        {
            /*
             * Taki zapis powoduje również zachowanie stabilności
             * sortowania dla elementów o tej samej wartości.
             */
            if (!(array[rightIndex] < array[leftIndex]))
            {
                temporary.push_back(array[leftIndex]);
                ++leftIndex;
            }
            else
            {
                temporary.push_back(array[rightIndex]);
                ++rightIndex;
            }
        }

        /*
         * Jeżeli w lewej części pozostały elementy,
         * kopiujemy je do tablicy pomocniczej.
         */
        while (leftIndex <= middle)
        {
            temporary.push_back(array[leftIndex]);
            ++leftIndex;
        }

        /*
         * Jeżeli w prawej części pozostały elementy,
         * również kopiujemy je do tablicy pomocniczej.
         */
        while (rightIndex <= right)
        {
            temporary.push_back(array[rightIndex]);
            ++rightIndex;
        }

        /*
         * Przepisujemy scalone elementy do oryginalnej tablicy.
         */
        for (std::size_t i = 0; i < temporary.size(); ++i)
        {
            array[left + i] = temporary[i];
        }
    }
};

#endif