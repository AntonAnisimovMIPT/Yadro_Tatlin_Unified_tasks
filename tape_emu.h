#ifndef TAPE_EMU_H
#define TAPE_EMU_H

#include <fstream>
#include <vector>
#include <string>
#include "configurations.h"
#include "dirs_files.h"
#include "ram_emu.h"

class Tape_emu {
public:
    Tape_emu(const std::string& input_name, RAM_emu& ram_emu, Configurations& config_dt, const std::string& conf_file);

    void set_output_files(std::vector<Dirs_Files> output_names);
    void read();
    void read(std::size_t index);
    void write(std::size_t output_file_index);
    void write(std::size_t index_in_RAM, std::size_t output_file_index);
    void rewind();
    void shift_left();
    void shift_right();
    double get_elapsed_time() const;
    std::size_t get_position() const;
    std::size_t get_number_output_files() const;
    std::size_t count_lines();

private:
    double elapsed_time;
    std::size_t position;
    std::ifstream input_file;
    RAM_emu& RAM;
    Configurations& configurations_data;
    std::vector<std::ofstream> output_files;
};

#endif // TAPE_EMU_H
