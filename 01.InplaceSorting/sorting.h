#ifndef SORTING_H
#define SORTING_H

#include <algorithm>
#include <iterator>

// сортировка пузырьком
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return;
    }

    for (auto right = end; right != begin; --right)
    {
        bool changed = false;

        for (auto it = begin; std::next(it) != right; ++it)
        {
            auto next = std::next(it);
            if (*next < *it)
            {
                using std::swap;
                swap(*it, *next);
                changed = true;
            }
        }

        if (!changed)
        {
            break;
        }
    }
}

// быстрая сортировка
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    auto len = end - begin;
    if (len <= 1)
    {
        return;
    }

    auto pivot = *(begin + len / 2);
    auto left = begin;
    auto right = end - 1;

    while (left <= right)
    {
        while (*left < pivot)
        {
            ++left;
        }

        while (pivot < *right)
        {
            --right;
        }

        if (left <= right)
        {
            using std::swap;
            swap(*left, *right);
            ++left;
            --right;
        }
    }

    quick_sort(begin, right + 1);
    quick_sort(left, end);
}

#endif
