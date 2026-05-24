#include "base85ed.h"

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace
{

constexpr char alphabet[] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";
constexpr uint8_t bad_char = 255;

struct DecodeTable
{
    uint8_t values[256];

    DecodeTable()
    {
        std::fill(values, values + 256, bad_char);

        for (uint8_t i = 0; i < 85; ++i)
        {
            values[static_cast<unsigned char>(alphabet[i])] = i;
        }
    }
};

const DecodeTable table;

uint32_t read_block(std::vector<uint8_t> const &bytes, std::size_t start, std::size_t count)
{
    uint32_t value = 0;

    // собираем блок как число из четырех байтов
    for (std::size_t i = 0; i < 4; ++i)
    {
        value <<= 8;

        if (i < count)
        {
            value |= bytes[start + i];
        }
    }

    return value;
}

void write_block(std::vector<uint8_t> &out, uint32_t value, std::size_t count)
{
    // возвращаем нужное число байтов из блока
    for (std::size_t i = 0; i < count; ++i)
    {
        auto shift = static_cast<unsigned>((3 - i) * 8);
        out.push_back(static_cast<uint8_t>((value >> shift) & 0xFF));
    }
}

} // namespace

std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> out;
    out.reserve((bytes.size() + 3) / 4 * 5);

    for (std::size_t pos = 0; pos < bytes.size(); pos += 4)
    {
        std::size_t part = std::min<std::size_t>(4, bytes.size() - pos);
        uint32_t value = read_block(bytes, pos, part);

        char block[5];
        for (int i = 4; i >= 0; --i)
        {
            block[i] = alphabet[value % 85];
            value /= 85;
        }

        // неполный последний блок дает на один символ больше чем байтов
        for (std::size_t i = 0; i < part + 1; ++i)
        {
            out.push_back(static_cast<uint8_t>(block[i]));
        }
    }

    return out;
}

std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &code)
{
    std::vector<uint8_t> out;
    out.reserve((code.size() + 4) / 5 * 4);

    for (std::size_t pos = 0; pos < code.size(); pos += 5)
    {
        std::size_t part = std::min<std::size_t>(5, code.size() - pos);

        if (part == 1)
        {
            throw std::invalid_argument("bad base85 length");
        }

        uint64_t value = 0;

        // недостающие символы в конце считаем максимальной цифрой
        for (std::size_t i = 0; i < 5; ++i)
        {
            uint8_t digit = 84;

            if (i < part)
            {
                digit = table.values[code[pos + i]];
                if (digit == bad_char)
                {
                    throw std::invalid_argument("bad base85 character");
                }
            }

            value = value * 85 + digit;
        }

        if (value > 0xFFFFFFFFULL)
        {
            throw std::invalid_argument("base85 block is too large");
        }

        write_block(out, static_cast<uint32_t>(value), part - 1);
    }

    return out;
}
