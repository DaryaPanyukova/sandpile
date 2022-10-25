#include <cstring>

#include <string>
#include <sstream>

#include "Sandpile.h"


std::string
GenerateFileName(std::string& path, std::string& default_name,
                 uint16_t number) {
    return path + "\\" + default_name + "_" + std::to_string(number) + ".bmp";
}


void
ReadToGrid(std::string& path, uint64_t**& grid, size_t height, size_t width) {
    grid = new size_t* [height];
    for (size_t i = 0; i < height; ++i) {
        grid[i] = new uint64_t[width];
        for (size_t j = 0; j < width; ++j) {
            grid[i][j] = 0;
        }
    }

    std::ifstream file(path);
    std::string line;
    while (getline(file, line)) {
        std::stringstream str_in(line);
        std::string tmp;

        size_t x, y, amount;
        str_in >> x >> y >> amount;
        grid[y][x] = amount;
    }
}


void ClearFolder(std::string& output_path, std::string& default_name,
                 std::string& final_file) {
    for (int32_t i = 0;; ++i) {
        std::string filename = GenerateFileName(output_path, default_name, i);
        std::ifstream file(filename);
        if (file) {
            file.close();
            std::remove(filename.c_str());
        } else {
            break;
        }
    }

    std::ifstream file(final_file);
    if (file) {
        file.close();
        std::remove(final_file.c_str());

    }
}


bool FileExists(std::string& filename) {
    std::ifstream file(filename);
    if (file) {
        file.close();
        return true;
    } else {
        return false;
    }
}


int main(int argc, char** argv) {
    size_t max_iter, frequency, width, height;
    std::string input_file;
    std::string output_path;
    for (size_t i = 1; i < argc; ++i) {
        char* term = argv[i];
        if (strcmp(term, "--length") == 0) {
            height = atoi(argv[++i]);
        } else if (strcmp(term, "--width") == 0) {
            width = atoi(argv[++i]);
        } else if (strcmp(term, "--input") == 0) {
            input_file = argv[++i];
        } else if (strcmp(term, "--output") == 0) {
            output_path = argv[++i];
        } else if (strcmp(term, "--max-iter") == 0) {
            max_iter = atoi(argv[++i]);
        } else if (strcmp(term, "--freq") == 0) {
            frequency = atoi(argv[++i]);
        }
    }


    uint64_t** grid;
    ReadToGrid(input_file, grid, height, width);
    Sandpile sandpile(width, height, grid);

    std::string default_name = "state";
    std::string final_file = output_path + "\\final.bmp";
    ClearFolder(output_path, default_name, final_file);

    for (size_t i = 0; i < max_iter && !sandpile.Stable(); ++i) {
        sandpile.DoIteration();
        if (frequency != 0 && i % frequency == 0) {
            GenerateFileName(output_path, default_name,
                             i == 0 ? 0 : i / frequency);
            std::string output_file =
                    GenerateFileName(output_path, default_name,
                                     i == 0 ? 0 : i / frequency);
            sandpile.Save(output_file);
        }
    }

    sandpile.Save(final_file);
}