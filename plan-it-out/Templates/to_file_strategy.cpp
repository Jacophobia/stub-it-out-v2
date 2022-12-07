#include "to_file_strategy.h"

auto to_file_strategy::to_files(project *project) -> std::map<std::string, std::string>
{
    std::map<std::string, std::string> files;
    // create class files
    auto [class_curr, class_end] = project->get_class_iter();
    for (; class_curr != class_end; ++class_curr)
    {
        files.emplace(to_file(&class_curr->second));
    }
    // create a function file
    auto [function_curr, function_end] = project->get_function_iter();
    for (; function_curr != function_end; ++function_curr)
    {
        auto [filepath, file_content] = to_file(&function_curr->second);
        files[filepath].append(file_content);
    }

    return files;
}
