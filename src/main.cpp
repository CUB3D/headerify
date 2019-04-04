#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Syntax: headerify [Input]");
    }

    // Read in the given file

    std::filesystem::path input{argv[1]};
    int size = std::filesystem::file_size(input);

    std::ifstream reader{input, std::ios::binary};
    std::ofstream writer{input.replace_extension(".h"), std::ios::binary};
    
    std::string inputName = std::string{argv[1]};
    
    std::string outputName = inputName.replace(inputName.find('.'), inputName.length() - inputName.find('.'), ".h")
        .replace(inputName.find('.'), 1, "_");
    std::stringstream outputNameUpper;
    std::for_each(outputName.begin(), outputName.end(), [&](char& c) {
        outputNameUpper << (char) std::toupper(c);
    });
    std::string outputNameC = outputNameUpper.str();

    printf("Creating header of '%s' with size '%d'\n", input.c_str(), size);

    // Add the prelude
    writer << "#ifndef " << outputNameC << "\n"
           << "#define " << outputNameC << "\n\n"
           << "const char " << outputNameC << "[] = {" << "\n"
           << "    ";


    writer << std::hex;
    char data;
    int count{0};
    while(reader.good()) {
        reader.read(&data, 1);
        writer << "0x";

        // Pad the number to be a fixed width of 4 chars
        if(data < 16) {
            writer << "0";
        }

        writer << (int) data;
        count++;

        if(reader.good()) {
            // Add a comma if we still have bytes left
            writer << ",";

            // If we have printed too many bytes on this line then start a new line and indent
            if(count >= 16) {
                writer << "\n    ";
                count = 0;
            } else {
                // otherwise just continue this line
                writer << " ";
            }
        } else {
            writer << "\n";
        }
    }
    writer << std::dec;

    // Add the footer
    writer << "};\n\n"
           << "const size_t " << outputNameC << "_length = sizeof(" << outputNameC << ");\n"
           << "#endif " << outputNameC << "\n";

    writer.flush();
    writer.close();


    return 0;
}