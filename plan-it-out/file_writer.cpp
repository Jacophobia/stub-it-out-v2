#include "file_writer.h"

#include <fstream>

auto file_writer::write(const std::map<std::string, std::string> &files) -> void
{
    for (auto & [filepath, file_content] : files)
    {
        std::ofstream f(filepath);

        f << file_content;
        
        f.close();
    }
}
