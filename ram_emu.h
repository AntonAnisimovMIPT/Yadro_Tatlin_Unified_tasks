#ifndef RAM_EMU_H
#define RAM_EMU_H

#include <vector>
#include <optional>
#include "ram_element.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const std::optional<uint32_t>& value);

class RAM_emu {
public:
    RAM_emu(std::size_t M);

    void add_element(std::optional<uint32_t> added);
    std::size_t get_number_of_cells() const;
    RAM_Element get_min_element() const;
    std::optional<uint32_t> get_value_in_RAM(std::size_t index) const;
    std::optional<uint32_t> get_value_in_RAM() const;
    void set_element_in_RAM(const RAM_Element& ram_elem);
    void clear_RAM();
    void sort_storage();

private:
    std::vector<std::optional<uint32_t>> storage;
    std::size_t RAM_size;
};

#endif // RAM_EMU_H
