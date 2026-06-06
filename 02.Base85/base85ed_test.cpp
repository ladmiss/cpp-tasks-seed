#include <gtest/gtest.h>

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string>

#include "base85ed.h"

const std::vector<std::pair<const char *, const char * >> short_cases =
{
    { "",     ""     },
    { "F#",   "1"    },
    { "F){",  "12"   },
    { "F)}j", "123"  },
    { "F)}kW","1234" }
};

static std::vector<uint8_t> cstr2v(const char *s)
{
    return std::vector<uint8_t>(
               s,
               s + std::string(s).size()
           );
}

TEST(Base85ShortsEncode, TrivialShortEncodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

TEST(Base85ShortsDecode, TrivialShortDecodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

// подлые тесты :)

TEST(Base85SneakyTests, InvalidCharacters)
{
    EXPECT_THROW(base85::decode(cstr2v("F) {")), std::invalid_argument);
    EXPECT_THROW(base85::decode(cstr2v("F)\n{")), std::invalid_argument);
}

TEST(Base85SneakyTests, InvalidLength)
{
    EXPECT_THROW(base85::decode(cstr2v("F")), std::invalid_argument);
    EXPECT_THROW(base85::decode(cstr2v("F)}kW1")), std::invalid_argument);
}

TEST(Base85SneakyTests, ChunkOverflow)
{
    EXPECT_THROW(base85::decode(cstr2v("~~~~~")), std::invalid_argument);
}

TEST(Base85SneakyTests, ZeroBytes)
{
    std::vector<uint8_t> zeros(10, 0);
    auto encoded = base85::encode(zeros);

    EXPECT_EQ(encoded, cstr2v("0000000000000"));
    EXPECT_EQ(base85::decode(encoded), zeros);
}

TEST(Base85SneakyTests, LongTextRoundtrip)
{
    std::string text = "Man is distinguished, not only by his reason, but by this singular passion...";
    auto text_v = cstr2v(text.c_str());

    auto encoded = base85::encode(text_v);
    auto decoded = base85::decode(encoded);

    EXPECT_EQ(decoded, text_v);
}