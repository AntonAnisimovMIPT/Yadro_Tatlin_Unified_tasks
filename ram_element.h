#ifndef RAM_ELEMENT_H
#define RAM_ELEMENT_H

#include <optional>
#include <cstdint>

struct RAM_Element {
    std::optional<uint32_t> value;
    std::size_t index;
};

#endif // RAM_ELEMENT_H
