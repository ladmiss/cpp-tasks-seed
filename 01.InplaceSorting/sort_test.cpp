#include <algorithm>
#include <vector>

#include <gtest/gtest.h>

#include "sorting.h"

// общая проверка для любой сортировки
template <typename Sorter>
void check_sort(Sorter sorter)
{
    std::vector<std::vector<int>> cases = {
        {},
        {1},
        {4, 2, 5, 1, 3},
        {10, -1, 3, 9, 2, 10, -1},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {7, 7, 7, 7},
        {0, -5, 12, 12, 3, -1, 8}
    };

    for (auto data : cases)
    {
        auto expected = data;
        std::sort(expected.begin(), expected.end());
        sorter(data);
        EXPECT_EQ(data, expected);
    }
}

TEST(InplaceSortingSuite, BubbleSort)
{
    check_sort([](std::vector<int>& data)
    {
        bubble_sort(data.begin(), data.end());
    });
}

TEST(InplaceSortingSuite, QuickSort)
{
    check_sort([](std::vector<int>& data)
    {
        quick_sort(data.begin(), data.end());
    });
}
