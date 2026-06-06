#include "Gauss_solve.h"
#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    int n = ab.rows();
    if (ab.cols() != n + 1)
    {
        throw std::invalid_argument("Матрица должна быть расширенной: размер N x (N+1)");
    }

    for (int i = 0; i < n; ++i)
    {
        int max_row = i;
        double max_val = std::abs(ab(i, i));
        for (int k = i + 1; k < n; ++k)
        {
            if (std::abs(ab(k, i)) > max_val)
            {
                max_val = std::abs(ab(k, i));
                max_row = k;
            }
        }

        if (max_val < 1e-12)
        {
            throw std::runtime_error("Матрица вырожденная или близка к таковой");
        }

        if (max_row != i)
        {
            ab.row(i).swap(ab.row(max_row));
        }

        double pivot = ab(i, i);
        ab.row(i) /= pivot;

        for (int k = i + 1; k < n; ++k)
        {
            double factor = ab(k, i);
            ab.row(k) -= factor * ab.row(i);
        }
    }

    GaussVector x(n);
    for (int i = n - 1; i >= 0; --i)
    {
        x(i) = ab(i, n);
        for (int k = i + 1; k < n; ++k)
        {
            x(i) -= ab(i, k) * x(k);
        }
    }

    return x;
}