#include <iostream>
#include <CLI11.hpp>

int main(int argc, char** argv)
{
    CLI::App app("County Search");
    std::string filePath;
    app.add_option("county_file_path", filePath, "Path to file")->required();
    CLI11_PARSE(app, argc, argv);

    return 0;
}
