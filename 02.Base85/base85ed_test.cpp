#include "base85ed.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using Case = std::pair<char const*, char const*>;

const std::vector<Case> small_cases = {
    {"", ""},
    {"F#", "1"},
    {"F){", "12"},
    {"F)}j", "123"},
    {"F)}kW", "1234"}
};

std::vector<uint8_t> to_bytes(char const* text)
{
    std::string s = text;
    return std::vector<uint8_t>(s.begin(), s.end());
}

TEST(Base85Encode, SmallStrings)
{
    for (auto const& item : small_cases)
    {
        EXPECT_EQ(base85::encode(to_bytes(item.second)), to_bytes(item.first));
    }
}

TEST(Base85Decode, SmallStrings)
{
    for (auto const& item : small_cases)
    {
        EXPECT_EQ(base85::decode(to_bytes(item.first)), to_bytes(item.second));
    }
}

TEST(Base85Decode, BadCharacters)
{
    EXPECT_THROW(base85::decode(to_bytes("F) {")), std::invalid_argument);
    EXPECT_THROW(base85::decode(to_bytes("F)\n{")), std::invalid_argument);
}

TEST(Base85Decode, BadLength)
{
    EXPECT_THROW(base85::decode(to_bytes("F")), std::invalid_argument);
    EXPECT_THROW(base85::decode(to_bytes("F)}kW1")), std::invalid_argument);
}

TEST(Base85Decode, Overflow)
{
    EXPECT_THROW(base85::decode(to_bytes("~~~~~")), std::invalid_argument);
}

TEST(Base85Roundtrip, ZeroBytes)
{
    std::vector<uint8_t> zeros(10, 0);
    auto encoded = base85::encode(zeros);

    EXPECT_EQ(encoded, to_bytes("0000000000000"));
    EXPECT_EQ(base85::decode(encoded), zeros);
}

TEST(Base85Roundtrip, LongText)
{
    std::string text = "Man is distinguished, not only by his reason, but by this singular passion...";
    std::vector<uint8_t> bytes(text.begin(), text.end());

    auto encoded = base85::encode(bytes);
    auto decoded = base85::decode(encoded);

    EXPECT_EQ(decoded, bytes);
}

TEST(Base85Roundtrip, AllByteValues)
{
    std::vector<uint8_t> bytes;
    for (int i = 0; i < 256; ++i)
    {
        bytes.push_back(static_cast<uint8_t>(i));
    }

    EXPECT_EQ(base85::decode(base85::encode(bytes)), bytes);
}

TEST(Base85Roundtrip, DifferentLengths)
{
    std::vector<uint8_t> bytes;

    for (std::size_t len = 0; len < 80; ++len)
    {
        bytes.clear();
        for (std::size_t i = 0; i < len; ++i)
        {
            bytes.push_back(static_cast<uint8_t>((i * 37 + len) % 256));
        }

        EXPECT_EQ(base85::decode(base85::encode(bytes)), bytes);
    }
}
