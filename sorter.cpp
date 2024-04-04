#include "sorter.h"

std::vector<Dirs_Files> generate_files_paths(const std::string& general_directory, Tape_emu& tape, RAM_emu& ram) {
    
    std::vector<Dirs_Files> files_paths;
    auto number_files = std::ceil(static_cast<double>(tape.count_lines())/static_cast<double>(ram.get_number_of_cells()));
    
    for (int i = 0; i < number_files; ++i) {

        files_paths.push_back({general_directory, std::to_string(i)+".txt"});

    }
    return files_paths;
}

// данная функция создает в папке нужное количество временных файлов в отсортированном виде
void prepare_files(Tape_emu& tape, RAM_emu& ram, std::string target_directory) {

    if (!std::filesystem::exists(target_directory))
        std::filesystem::create_directory(target_directory); 

    auto number_files = std::ceil(static_cast<double>(tape.count_lines())/static_cast<double>(ram.get_number_of_cells()));
    auto number_values = tape.count_lines();

    for (size_t file_index = 0; file_index < number_files; file_index++) {
       
        if (file_index != number_files - 1)
        {
            for (size_t i = 0; i < ram.get_number_of_cells(); i++) {
                tape.read();
            }

            ram.sort_storage();

            for (size_t i = 0; i < ram.get_number_of_cells(); i++) {
                tape.write(i, file_index);
            }
        }
        else {

            auto remain_indexes = number_values - ram.get_number_of_cells() * file_index;
            for (size_t i = 0; i < remain_indexes; i++) {
                tape.read();
            }

            ram.sort_storage();

            for (size_t i = 0; i < remain_indexes; i++) {
                tape.write(i, file_index);
            }
        }

    }
    tape.rewind(); 
    
}

Sorter::Sorter(Tape_emu& input_tape, RAM_emu& ram, Configurations& config_dt, const std::string& conf_file) : tape_emu(input_tape), ram_emu(ram) {
    out_path = { .directory = ".", .filename = "output.txt"};
    std::vector<Dirs_Files> output{out_path};
    auto tmp_files = generate_files_paths("tmp", tape_emu, ram_emu);
    for (auto files : tmp_files) {
        tape_emus.emplace_back(files.filename, ram_emu, config_dt, conf_file); 
    }

    for (size_t index = 0; index < tape_emus.size(); index++) {
        tape_emus[index].set_output_files(output);
    }
}

void Sorter::sorting() {
    
    ram_emu.clear_RAM();
    auto upper_bound_iterations = tape_emu.count_lines();

    for (size_t i = 0; i < upper_bound_iterations; i++) {

        // для первой итерации алгоритм имеет особенность ввиду разницы работы перегруженных функций read()
        if (i == 0) {
            for (size_t index = 0; index < tape_emus.size(); index++) {
                tape_emus[index].read();
            }

            auto min_value = ram_emu.get_min_element().value;
            auto min_element_index = ram_emu.get_min_element().index;

            // по умолчанию записывающая лента - первая лента
            tape_emus[0].write(min_element_index, 0);
            tape_emus[min_element_index].read(min_element_index); 

        } else {
            for (size_t index = 0; index < tape_emus.size(); index++) {

                auto min_value = ram_emu.get_min_element().value;
                auto min_element_index = ram_emu.get_min_element().index;

                // по умолчанию записывающая лента - первая лента

                tape_emus[0].write(min_element_index, 0);
                tape_emus[min_element_index].read(min_element_index); 
            }
        }
    }
}
