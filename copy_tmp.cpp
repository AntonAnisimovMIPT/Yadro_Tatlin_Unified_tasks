#include <filesystem>
#include <iostream>

void copy_files_from_tmp_to_current() {
    
    std::filesystem::path tmp_dir = "tmp";

    std::filesystem::path target_dir = std::filesystem::current_path();

    for (const auto& entry : std::filesystem::directory_iterator(tmp_dir)) {
        
        if (std::filesystem::is_regular_file(entry.path())) {
            
            std::filesystem::path destination_file = target_dir / entry.path().filename();
            
            if (std::filesystem::exists(destination_file)) {
                
                std::filesystem::remove(destination_file);
                
            }

            std::filesystem::copy_file(entry.path(), destination_file, std::filesystem::copy_options::overwrite_existing);
            
        }
    }
}

int main() {
    copy_files_from_tmp_to_current();
}
