#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <string>

struct Configurations {
    double time_reading;
    double time_writing;
    double time_shifting;
    double time_rewinding;
    bool is_configurated = false;
};

void configurate(const std::string& conf_file_name, Configurations& configs);

#endif // CONFIGURATIONS_H
