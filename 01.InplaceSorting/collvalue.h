#ifndef COLLVALUE_H
#define COLLVALUE_H

#include <cstddef>
#include <utility>

// небольшая обертка для подсчета операций
template <typename T>
class CollectingValue
{
public:
    static inline std::size_t comps = 0;
    static inline std::size_t swaps = 0;
    static inline std::size_t moves = 0;

    T value;

    // обычный конструктор
    explicit CollectingValue(T val = T()) : value(val) {}

    // копирование тоже считаем перемещением данных
    CollectingValue(const CollectingValue& other) : value(other.value)
    {
        ++moves;
    }

    // перемещение объекта
    CollectingValue(CollectingValue&& other) noexcept : value(std::move(other.value))
    {
        ++moves;
    }

    // присваивание копированием
    CollectingValue& operator=(const CollectingValue& other)
    {
        if (this != &other)
        {
            value = other.value;
            ++moves;
        }
        return *this;
    }

    // присваивание перемещением
    CollectingValue& operator=(CollectingValue&& other) noexcept
    {
        if (this != &other)
        {
            value = std::move(other.value);
            ++moves;
        }
        return *this;
    }

    // сравнение для сортировок
    bool operator<(const CollectingValue& other) const
    {
        ++comps;
        return value < other.value;
    }

    // нужно для std::iota
    CollectingValue& operator++()
    {
        ++value;
        return *this;
    }

    // сброс счетчиков перед новым запуском
    static void reset_stats()
    {
        comps = 0;
        swaps = 0;
        moves = 0;
    }
};

// считаем перестановки
template <typename T>
void swap(CollectingValue<T>& left, CollectingValue<T>& right)
{
    ++CollectingValue<T>::swaps;
    std::swap(left.value, right.value);
}

#endif
