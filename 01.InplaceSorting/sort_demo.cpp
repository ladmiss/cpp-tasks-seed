#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "collvalue.h"
#include "sorting.h"

using CountedInt = CollectingValue<int>;

// создает вектор от 0 до n-1
auto make_data(std::size_t n) -> std::vector<CountedInt>
{
    std::vector<CountedInt> data(n);
    std::iota(data.begin(), data.end(), CountedInt(0));
    return data;
}

// перемешивает элементы чтобы сортировкам было что делать
void mix_data(std::vector<CountedInt>& data)
{
    static std::mt19937 gen(42);
    std::shuffle(data.begin(), data.end(), gen);
}

bool sorted_values(std::vector<CountedInt> const& data)
{
    return std::is_sorted(data.begin(), data.end(), [](CountedInt const& left, CountedInt const& right)
    {
        return left.value < right.value;
    });
}

// печатает одну строку с результатами
void print_stats(std::size_t n, char const* name)
{
    std::cout << std::setw(6) << n << "  "
              << std::setw(12) << name << "  "
              << std::setw(12) << CountedInt::comps << "  "
              << std::setw(12) << CountedInt::swaps << "  "
              << std::setw(12) << CountedInt::moves << '\n';
}

bool check_result(std::vector<CountedInt> const& data, std::size_t n, char const* name)
{
    if (sorted_values(data))
    {
        return true;
    }

    std::cerr << "sort failed: " << name << ", n = " << n << '\n';
    return false;
}

int main()
{
    std::vector<std::size_t> sizes = {0, 1, 2, 10, 50, 100, 500, 1000};
    bool ok = true;

    std::cout << std::setw(6) << "n" << "  "
              << std::setw(12) << "algorithm" << "  "
              << std::setw(12) << "comparisons" << "  "
              << std::setw(12) << "swaps" << "  "
              << std::setw(12) << "moves" << '\n';

    for (auto n : sizes)
    {
        auto base = make_data(n);

        auto data = base;
        mix_data(data);
        CountedInt::reset_stats();
        std::sort(data.begin(), data.end());
        print_stats(n, "std::sort");
        ok = check_result(data, n, "std::sort") && ok;

        data = base;
        mix_data(data);
        CountedInt::reset_stats();
        bubble_sort(data.begin(), data.end());
        print_stats(n, "bubble");
        ok = check_result(data, n, "bubble") && ok;

        data = base;
        mix_data(data);
        CountedInt::reset_stats();
        quick_sort(data.begin(), data.end());
        print_stats(n, "quick");
        ok = check_result(data, n, "quick") && ok;

        std::cout << '\n';
    }

    return ok ? 0 : 1;
}
