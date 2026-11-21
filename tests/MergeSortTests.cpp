/**
 * @file MergeSortTests.cpp
 * @brief Testy jednostkowe szablonowej klasy MergeSort z użyciem Google Test.
 */

#include "MergeSort.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <random>

/**
 * @brief Funkcje pomocnicze i testy sortowania przez scalanie.
 */
namespace
{
/**
 * @brief Porównuje wynik MergeSort z wynikiem std::sort.
 * @tparam T Typ elementów tablicy.
 * @tparam N Liczba elementów tablicy.
 * @param dane Kopia tablicy, która zostanie posortowana w teście.
 */
template <typename T, std::size_t N>
void sprawdzSortowanie(std::array<T, N> dane)
{
    std::array<T, N> oczekiwane = dane;
    std::sort(oczekiwane.begin(), oczekiwane.end());

    MergeSort<T, N> sorter;
    sorter.sort(dane);

    EXPECT_EQ(dane, oczekiwane);
}

/**
 * @brief Wspólna baza testów wykonywanych dla różnych typów liczbowych.
 * @tparam T Typ liczbowy sprawdzany w danym zestawie testów.
 */
template <typename T>
class MergeSortTest : public ::testing::Test
{
};

/** @brief Typy liczb sprawdzane przez testy typowane. */
using TestowaneTypy = ::testing::Types<int, long int, float, double>;
TYPED_TEST_SUITE(MergeSortTest, TestowaneTypy);

/**
 * @brief Test 1: sprawdza, czy tablica rosnąca pozostaje niezmieniona.
 */
TYPED_TEST(MergeSortTest, RosnacaBezZmian)
{
    std::array<TypeParam, 6> dane = {{-5, -2, 0, 1, 4, 9}};
    const auto przedSortowaniem = dane;
    MergeSort<TypeParam, 6> sorter;

    sorter.sort(dane);

    EXPECT_EQ(dane, przedSortowaniem);
}

/**
 * @brief Test 2: sprawdza sortowanie tablicy w odwrotnej kolejności.
 */
TYPED_TEST(MergeSortTest, OdwrotnaKolejnosc)
{
    sprawdzSortowanie(std::array<TypeParam, 8>{{8, 7, 6, 5, 4, 3, 2, 1}});
}

/**
 * @brief Test 3: sprawdza sortowanie tablicy losowych liczb.
 * @details Stałe ziarno generatora zapewnia powtarzalność danych testowych.
 */
TYPED_TEST(MergeSortTest, LosoweLiczby)
{
    std::array<TypeParam, 40> dane{};
    std::mt19937 generator(20261121u);
    std::uniform_int_distribution<int> losuj(0, 500);
    for (auto& liczba : dane)
    {
        liczba = static_cast<TypeParam>(losuj(generator));
    }

    sprawdzSortowanie(dane);
}

/**
 * @brief Test 4: sprawdza sortowanie wyłącznie liczb ujemnych.
 */
TYPED_TEST(MergeSortTest, TylkoUjemne)
{
    sprawdzSortowanie(std::array<TypeParam, 6>{{-3, -20, -1, -14, -2, -7}});
}

/**
 * @brief Test 5: sprawdza sortowanie liczb ujemnych i dodatnich.
 */
TYPED_TEST(MergeSortTest, UjemneIDodatnie)
{
    sprawdzSortowanie(std::array<TypeParam, 7>{{-8, 5, 0, -3, 12, 1, -1}});
}

/**
 * @brief Test 6: sprawdza obsługę pustej tablicy bez rzucania wyjątku.
 */
TYPED_TEST(MergeSortTest, PustaTablicaBezWyjatku)
{
    std::array<TypeParam, 0> dane{};
    MergeSort<TypeParam, 0> sorter;

    EXPECT_NO_THROW(sorter.sort(dane));
    EXPECT_TRUE(dane.empty());
}

/**
 * @brief Test 7: sprawdza, czy jedyny element tablicy pozostaje bez zmian.
 */
TYPED_TEST(MergeSortTest, JedenElementBezZmian)
{
    std::array<TypeParam, 1> dane = {{42}};
    const auto przedSortowaniem = dane;
    MergeSort<TypeParam, 1> sorter;

    sorter.sort(dane);

    EXPECT_EQ(dane, przedSortowaniem);
}

/**
 * @brief Test 8: sprawdza sortowanie tablicy zawierającej duplikaty.
 */
TYPED_TEST(MergeSortTest, Duplikaty)
{
    sprawdzSortowanie(std::array<TypeParam, 8>{{5, 2, 5, 3, 2, 5, 1, 3}});
}

/**
 * @brief Test 9: sprawdza sortowanie liczb ujemnych z duplikatami.
 */
TYPED_TEST(MergeSortTest, UjemneZDuplikatami)
{
    sprawdzSortowanie(std::array<TypeParam, 8>{{-5, -1, -5, -3, -1, -2, -3, -5}});
}

/**
 * @brief Test 10: sprawdza sortowanie liczb ujemnych i dodatnich z duplikatami.
 */
TYPED_TEST(MergeSortTest, UjemneIDodatnieZDuplikatami)
{
    sprawdzSortowanie(
        std::array<TypeParam, 10>{{-3, 4, -3, 0, 4, -1, 2, 2, 0, -1}}
    );
}

/**
 * @brief Test 11: sprawdza zachowanie dwóch elementów ułożonych rosnąco.
 */
TYPED_TEST(MergeSortTest, DwaElementyRosnaco)
{
    std::array<TypeParam, 2> dane = {{1, 2}};
    const auto przedSortowaniem = dane;
    MergeSort<TypeParam, 2> sorter;

    sorter.sort(dane);

    EXPECT_EQ(dane, przedSortowaniem);
}

/**
 * @brief Test 12: sprawdza sortowanie dużej tablicy zawierającej 256 elementów.
 */
TYPED_TEST(MergeSortTest, PonadStoElementow)
{
    std::array<TypeParam, 256> dane{};
    for (std::size_t i = 0; i < dane.size(); ++i)
    {
        dane[i] = static_cast<TypeParam>(dane.size() - i);
    }

    sprawdzSortowanie(dane);
}

/**
 * @brief Test 13: sprawdza sortowanie 300 liczb obu znaków z duplikatami.
 */
TYPED_TEST(MergeSortTest, PonadStoElementowMieszanychZDuplikatami)
{
    std::array<TypeParam, 300> dane{};
    for (std::size_t i = 0; i < dane.size(); ++i)
    {
        const int wartosc = static_cast<int>((i * 37) % 41) - 20;
        dane[i] = static_cast<TypeParam>(wartosc);
    }

    sprawdzSortowanie(dane);
}

/**
 * @brief Sprawdza sortowanie liczb double z częścią ułamkową.
 */
TEST(MergeSortUlamki, Double)
{
    sprawdzSortowanie(
        std::array<double, 7>{{4.75, -2.5, 0.125, 7.1, 1.25, -2.5, 0.0}}
    );
}

/**
 * @brief Sprawdza sortowanie liczb float z częścią ułamkową.
 */
TEST(MergeSortUlamki, Float)
{
    sprawdzSortowanie(
        std::array<float, 7>{{4.75f, -2.5f, 0.125f, 7.1f, 1.25f, -2.5f, 0.0f}}
    );
}
}
