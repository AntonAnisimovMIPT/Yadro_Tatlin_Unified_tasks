#include "ram_emu.h"
#include <cmath>
#include <algorithm>

std::ostream& operator<<(std::ostream& os, const std::optional<uint32_t>& value) {
    if (value.has_value()) {
        os << value.value();
    } else {
        os << "empty"; 
    }
    return os;
}

RAM_emu::RAM_emu(std::size_t M) : RAM_size(M) {}

void RAM_emu::add_element(std::optional<uint32_t> added) { 
    if (std::size(storage) < get_number_of_cells()) {

        storage.push_back(added);

    } else {

        // при переполнении памяти она очищается, особенность реализации алгоритма
        storage.clear();
        storage.push_back(added);

    }
}

std::size_t RAM_emu::get_number_of_cells() const {
    return std::ceil(RAM_size / static_cast<std::size_t>(sizeof(std::uint32_t)));
}

RAM_Element RAM_emu::get_min_element() const {

    if (!storage.empty()) {
        auto min_element_it = std::min_element(storage.begin(), storage.end(), 

        // для работы с std::optional для функции сравнения нужно написать собственный компаратор
            [](const auto& a, const auto& b) {

                if (!a) return false;
                if (!b) return true;
                return *a < *b;

            });

        auto min_index = static_cast<std::size_t>(std::distance(storage.begin(), min_element_it));
        RAM_Element max_element = { .value = *min_element_it, .index = min_index };
        return max_element;    

    } else {

        std::cout << "Storage is empty! The operation of finding the maximum element is incorrect.\n";
        return { .value = std::nullopt, .index = 0 }; 

    }
}

std::optional<uint32_t> RAM_emu::get_value_in_RAM(std::size_t index) const {

    if (index >= storage.size()) {

        std::cout << "incorrect index in RAM\n";

    }

    auto it = std::next(storage.begin(), index);
    return *it;
}

std::optional<uint32_t> RAM_emu::get_value_in_RAM() const {
    return storage.back();
}

void RAM_emu::set_element_in_RAM(const RAM_Element& ram_elem) {

    if (!storage.empty()) {

        storage[ram_elem.index] = ram_elem.value;

    } else {

        std::cout << "storage is empty!\n";

    }
}

void RAM_emu::clear_RAM() {
    storage.clear();
}

void RAM_emu::sort_storage() {

    std::sort(storage.begin(), storage.end(), std::less<std::optional<uint32_t>>());
    
}
