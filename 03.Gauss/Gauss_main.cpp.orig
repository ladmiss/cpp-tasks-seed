#include <iostream>
#include "util.h"
#include "Gauss_solve.h"

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Использование: " << argv[0] << " <input.csv>\n";
        return 1;
    }

    try
    {
        GaussMatrix ab = load_csv_to_matrix(argv[1]);
        
        GaussVector x = Gauss_solve(ab);

        std::cout << "x\n";
        for (int i = 0; i < x.size(); ++i)
        {
            std::cout << x(i) << "\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}