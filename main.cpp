#include "ram_emu.h"
#include "tape_emu.h"
#include "sorter.h"


int main(int argc, char** argv) {
    std::string input = "input.txt";

    /* 
        я мог перенести считывание размера оперативной памяти и в отдельное значение в файле конфигураций,
        т.к. в задании про это не говорится, то решил оставить возможным делать проброс этого значения через 
        внешний скрипт, к тому же это удобнее и для дальнейшег тестирования под разные размеры лент
    */ 

    auto RAM_size = std::stoul(argv[2]);


    RAM_emu ram_emu(RAM_size); 
    Configurations confs;
    auto conffile = "configurations.txt";

    Tape_emu tape(input, ram_emu, confs, conffile);
    auto tmps_paths = generate_files_paths("tmp", tape, ram_emu);
    tape.set_output_files(tmps_paths);

    std::string action = argv[1];
    if (action == "prepare") {
        prepare_files(tape, ram_emu, "tmp");
    } else if (action == "sort") {
        Sorter srt(tape, ram_emu, confs, conffile);
        srt.sorting();
    }

    return 0;
}
