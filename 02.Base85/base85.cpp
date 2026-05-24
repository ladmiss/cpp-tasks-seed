#include "base85ed.h"

#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

std::vector<uint8_t> read_input()
{
    constexpr std::streamsize buf_size = 64 * 1024;
    std::vector<uint8_t> data;
    std::vector<char> buf(buf_size);

    std::ios::sync_with_stdio(false);

    // читаем поток до конца
    while (std::cin)
    {
        std::cin.read(buf.data(), buf_size);
        auto got = std::cin.gcount();

        if (got > 0)
        {
            auto first = reinterpret_cast<uint8_t *>(buf.data());
            auto last = reinterpret_cast<uint8_t *>(buf.data() + got);
            data.insert(data.end(), first, last);
        }
    }

    return data;
}

void write_output(std::vector<uint8_t> const &data)
{
    std::ios::sync_with_stdio(false);

    // пишем результат без лишнего форматирования
    if (!data.empty())
    {
        std::cout.write(reinterpret_cast<char const *>(data.data()), data.size());
    }

    std::cout.flush();
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cerr << "use -e or -d\n";
        return 1;
    }

    std::function<std::vector<uint8_t>(std::vector<uint8_t> const &)> action;
    std::string mode = argv[1];

    if (mode == "--encode" || mode == "-e")
    {
        action = base85::encode;
    }
    else if (mode == "--decode" || mode == "-d")
    {
        action = base85::decode;
    }
    else
    {
        std::cerr << "unknown argument " << mode << "\n";
        return 1;
    }

    auto input = read_input();
    auto output = action(input);
    write_output(output);

    return 0;
}
