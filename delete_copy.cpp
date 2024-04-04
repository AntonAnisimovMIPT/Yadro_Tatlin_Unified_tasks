#include <iostream>
#include <filesystem>
#include <string>
#include <regex>

void delete_files_in_directory(const std::string& directory_path, const std::string& file_format) {
    
    if (!std::filesystem::exists(directory_path)) {
        std::cerr << "Directory does not exist!!!\n";
        return;
    }

    
    std::regex file_regex(file_format);

    
    for (const auto& file : std::filesystem::directory_iterator(directory_path)) {
        
        if (file.is_regular_file()) {
            
            std::string filename = file.path().filename().string();
            
            if (std::regex_match(filename, file_regex)) {
                
                std::filesystem::remove(file.path());

            }
        }
    }
}

int main() {
    
    std::string directory_path = ".";
    std::string file_format = R"(\d+\.txt)"; 

    delete_files_in_directory(directory_path, file_format);

}
