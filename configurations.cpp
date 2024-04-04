#include "configurations.h"
#include <fstream>

void configurate(const std::string& conf_file_name, Configurations& configs) {
    std::ifstream config_file(conf_file_name);
    config_file >> configs.time_reading 
                >> configs.time_writing 
                >> configs.time_shifting 
                >> configs.time_rewinding;
    configs.is_configurated = true;
}
