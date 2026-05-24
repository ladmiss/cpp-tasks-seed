#ifndef BASE85ED_H
#define BASE85ED_H

#include <cstdint>
#include <vector>

namespace base85
{

// кодирует набор байтов в base85
std::vector<uint8_t> encode(std::vector<uint8_t> const &bytes);

// декодирует base85 обратно в байты
std::vector<uint8_t> decode(std::vector<uint8_t> const &code);

} // namespace base85

#endif // base85ed_h
