#ifndef SORTING_H
#define SORTING_H
#include <iterator>
#include "collvalue.h"

// ----------------------------- Пузырёк --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;
    for (auto i = begin; i != end - 1; ++i) 
    {
        bool swapped = false;
        for (auto j = begin; j != end - 1 - std::distance(begin, i); ++j) 
        {
            if (*(j + 1) < *j) 
            {
                using std::swap; 
                swap(*j, *(j + 1));
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// --------------------------- QuickSort ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    auto distance = std::distance(begin, end);
    if (distance <= 1) return;

    auto pivot_it = begin + distance / 2;
    auto pivot = *pivot_it;
    auto left = begin;
    auto right = end - 1;

    while (left <= right) 
    {
        while (*left < pivot) ++left;
        while (pivot < *right) --right;

        if (left <= right) 
        {
            using std::swap;
            swap(*left, *right);
            ++left;
            --right;
        }
    }

    if (begin < right + 1) quick_sort(begin, right + 1);
    if (left < end) quick_sort(left, end);
}

#endif