#include <gtest/gtest.h>
#include <vector>
#include "sorting.h"

TEST(InplaceSortingSuite, BubbleSortTest)
{
    std::vector<int> data = {4, 2, 5, 1, 3};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    bubble_sort(data.begin(), data.end());
    EXPECT_EQ(data, expected);
}

TEST(InplaceSortingSuite, QuickSortTest)
{
    std::vector<int> data = {10, -1, 3, 9, 2, 10, -1};
    std::vector<int> expected = {-1, -1, 2, 3, 9, 10, 10};
    quick_sort(data.begin(), data.end());
    EXPECT_EQ(data, expected);
}

TEST(InplaceSortingSuite, EmptyAndSingleElement)
{
    std::vector<int> empty_data;
    quick_sort(empty_data.begin(), empty_data.end());
    EXPECT_TRUE(empty_data.empty());

    std::vector<int> single_data = {42};
    bubble_sort(single_data.begin(), single_data.end());
    EXPECT_EQ(single_data[0], 42);
}