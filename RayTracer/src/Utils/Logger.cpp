
#include "Logger.hpp"

void ConsoleOutput::output(const std::string& message) {
        std::cout << message << std::endl;
    }

FileOutput::FileOutput() {
        if (std::filesystem::exists("log.txt"))
            std::filesystem::remove("log.txt");
    }

FileOutput::~FileOutput() {
        _outfile.close();
    }

void FileOutput::output(const std::string& message) {
        _outfile = std::ofstream("log.txt", std::ofstream::app);
        _outfile << message << std::endl;

    }
