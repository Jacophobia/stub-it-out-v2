


#include "arg_parser.h"
#include "display.h"
#include "linker.h"
#include "toml_parser.h"

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

        // write the content of each file object to a file in the
        // setting_value specified by the user
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
