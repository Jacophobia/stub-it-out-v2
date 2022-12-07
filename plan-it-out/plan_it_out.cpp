#include "arg_parser.h"
#include "display.h"
#include "file_writer.h"
#include "linker.h"
#include "toml_parser.h"
#include "Templates/python3.h"
#include "Templates/to_file_strategy.h"

auto toml_to_code(const int argc, char **argv) -> void
{
    // process the command line arguments
    const arg_parser arg_parser(argc, argv);

    // if the request is just for help or for the version, display
    // the relevant data and return
    if (arg_parser.is_help_request())
    {
        display::help();
        return;
    }
    if (arg_parser.is_version_request())
    {
        display::version();
        return;
    }

    // convert the file from a toml string to a project object
    const auto path = arg_parser.get_filepath();
    const auto settings = arg_parser.get_settings();
    const toml_parser toml_parser(path, settings);
    auto project = toml_parser.parse();

    try
    {
        // link the references in the project object together
        linker linker(settings);
        linker.link(project);
        // map each value to file object, isolating classes and
        // grouping functions
        const std::unique_ptr<to_file_strategy> converter = std::make_unique<python3_template>();
        const auto files = converter->to_files(project);
        // write the content of each file object to a file in the
        // setting_value specified by the user
        file_writer writer;
        writer.write(files);
    }
    catch (std::exception& error)
    {
        display::error(error);
    }

    delete project;
    project = nullptr;
}

auto main(const int argc, char **argv) -> int
{
    try
    {
        toml_to_code(argc, argv);
    }
    catch (std::exception& error)
    {
        display::error(error);
    }
}
