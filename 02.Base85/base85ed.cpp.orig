#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "base85ed.h"

namespace 
{
    const char b85chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

    struct ReverseMap 
    {
        uint8_t map[256];
        ReverseMap() 
        {
            for (int i = 0; i < 256; ++i) map[i] = 255;
            for (int i = 0; i < 85; ++i) 
            {
                map[static_cast<unsigned char>(b85chars[i])] = i;
            }
        }
    };

    const ReverseMap rmap;
}

std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> result;
    result.reserve((bytes.size() + 3) / 4 * 5);

    for (size_t i = 0; i < bytes.size(); i += 4) 
    {
        uint32_t acc = 0;
        size_t chunk_len = std::min(static_cast<size_t>(4), bytes.size() - i);
        
        for (size_t j = 0; j < 4; ++j) 
        {
            acc = (acc << 8) | (j < chunk_len ? bytes[i + j] : 0);
        }

        char out[5];
        for (int j = 4; j >= 0; --j) 
        {
            out[j] = b85chars[acc % 85];
            acc /= 85;
        }

        for (size_t j = 0; j <= chunk_len; ++j) 
        {
            result.push_back(out[j]);
        }
    }
    return result;
}

std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    std::vector<uint8_t> result;
    result.reserve((b85str.size() + 4) / 5 * 4);

    for (size_t i = 0; i < b85str.size(); i += 5) 
    {
        uint64_t acc = 0;
        size_t chunk_len = std::min(static_cast<size_t>(5), b85str.size() - i);

        if (chunk_len == 1) 
        {
            throw std::invalid_argument("Invalid base85 string length: isolated single character");
        }

        for (size_t j = 0; j < 5; ++j) 
        {
            int idx = 84;
            if (j < chunk_len) {
                uint8_t c = b85str[i + j];
                idx = rmap.map[c];
                if (idx == 255) 
                {
                    throw std::invalid_argument("Invalid character in base85 string");
                }
            }
            acc = acc * 85 + idx;
        }

        if (acc > 0xFFFFFFFF) 
        {
            throw std::invalid_argument("Base85 chunk overflow");
        }

        size_t out_bytes = chunk_len - 1;
        for (size_t j = 0; j < out_bytes; ++j) 
        {
            result.push_back(static_cast<uint8_t>((acc >> (24 - j * 8)) & 0xFF));
        }
    }
    return result;
}