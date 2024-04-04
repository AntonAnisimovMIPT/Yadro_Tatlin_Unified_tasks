#include "tape_emu.h"
#include <filesystem>
#include <iostream>

Tape_emu::Tape_emu(const std::string& input_name, RAM_emu& ram_emu, Configurations& config_dt, const std::string& conf_file)
    : input_file(input_name), RAM(ram_emu), configurations_data(config_dt), position(0), elapsed_time(0) {

    if (!config_dt.is_configurated) {
        configurate(conf_file, configurations_data);
    }
}

void Tape_emu::set_output_files(std::vector<Dirs_Files> output_names) {
    for (const auto& file_info : output_names) {

        std::filesystem::create_directories(file_info.directory);
        output_files.emplace_back(file_info.directory + "/" + file_info.filename);

    }
}

void Tape_emu::read() {
    std::string reading_line;

    if (std::getline(input_file, reading_line)) {

        auto digit_line = std::stoul(reading_line);
        RAM.add_element(digit_line);

        elapsed_time += configurations_data.time_reading;

        // т.к. сдвиг действительно есть из-за std::getline
        ++position; 
        elapsed_time += configurations_data.time_shifting;

    } else {

        // если дошли до конца, то элемент в оперативной памяти меняется std::nullopt, особенность реализации алгортима
        RAM.add_element(std::nullopt);
    }
}

void Tape_emu::read(std::size_t index) {
    std::string reading_line;

    if (std::getline(input_file, reading_line)) {

        auto digit_line = std::stoul(reading_line);
        RAM_Element ram_elem{ .value = digit_line, .index = index };
        RAM.set_element_in_RAM(ram_elem);


        elapsed_time += configurations_data.time_reading;
        // т.к. сдвиг действительно есть из-за std::getline
        ++position;
        elapsed_time += configurations_data.time_shifting;

    } else {

        // если дошли до конца, то элемент в оперативной памяти меняется std::nullopt, особенность реализации алгортима
        RAM_Element ram_elem{ .value = std::nullopt, .index = index }; 
        RAM.set_element_in_RAM(ram_elem);
    }
}

void Tape_emu::write(std::size_t output_file_index) {
    if (RAM.get_value_in_RAM() != std::nullopt) {
        output_files[output_file_index] << RAM.get_value_in_RAM() << "\n";
    }
}

void Tape_emu::write(std::size_t index_in_RAM, std::size_t output_file_index) {
    if (RAM.get_value_in_RAM(index_in_RAM) != std::nullopt) {
        output_files[output_file_index] << RAM.get_value_in_RAM(index_in_RAM) << "\n";
    }
}

void Tape_emu::rewind() {

    input_file.clear();
    // после перемотки считывающая головка устанавливается на начало ленты
    input_file.seekg(0, std::ios::beg);
    elapsed_time += configurations_data.time_rewinding;
    position = 0; 

}

void Tape_emu::shift_left() {
    if (position > 0) {

        --position;
        input_file.seekg(-static_cast<std::streamoff>(sizeof(std::uint32_t)), std::ios_base::cur);
        elapsed_time += configurations_data.time_shifting;

    } else {

        std::cout << "It's impossible to move to left, because the beginning of the file has already been reached.\n";
    
    }
}

void Tape_emu::shift_right() {

    // для смещения вправо немного сложнее логика проверок, т.к. щаранее мы не знаем номер последней позиции

    auto current_pos = input_file.tellg();

    input_file.seekg(0, std::ios::end);
    auto file_size = input_file.tellg();

    input_file.seekg(current_pos); 

    if (current_pos + static_cast<std::streamoff>(sizeof(std::uint32_t)) < file_size) {
        input_file.seekg(static_cast<std::streamoff>(sizeof(std::uint32_t)), std::ios_base::cur);
        ++position;
        elapsed_time += configurations_data.time_shifting;
    } else {
        std::cout << "It's impossible to move to right, because the end of the file has already been reached.\n";
    }
}

double Tape_emu::get_elapsed_time() const {
    return elapsed_time;
}

std::size_t Tape_emu::get_position() const {
    return position;
}

std::size_t Tape_emu::get_number_output_files() const {
    return output_files.size();
}

std::size_t Tape_emu::count_lines() {
    
    std::streampos current_pos = input_file.tellg();
    std::size_t line_count = 0;
    std::string line;

    while (std::getline(input_file, line)) {
        ++line_count;
    }

    input_file.clear();
    input_file.seekg(current_pos); 
    return line_count;
}
