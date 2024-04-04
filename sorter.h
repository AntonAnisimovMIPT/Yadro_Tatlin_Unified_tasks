#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include <string>
#include <cmath>
#include <filesystem>
#include "tape_emu.h"

std::vector<Dirs_Files> generate_files_paths(const std::string& general_directory, Tape_emu& tape, RAM_emu& ram);

void prepare_files(Tape_emu& tape, RAM_emu& ram, std::string target_directory);


class Sorter {
public:
    Sorter(Tape_emu& input_tape, RAM_emu& ram, Configurations& config_dt, const std::string& conf_file);

    void sorting();

private:
    std::vector<std::ofstream> tmp_files;
    std::vector<Tape_emu> tape_emus;
    RAM_emu& ram_emu;
    Tape_emu& tape_emu;
    Dirs_Files out_path;
};

#endif // SORTER_H
