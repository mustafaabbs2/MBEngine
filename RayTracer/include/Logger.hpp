#pragma once


#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <thread>

//this doesn't need to be done, I was just trying to use templates
//This could be done easily with inheritance anyway

template <typename OutputMethod>
class Logger : private OutputMethod {
public:
    Logger() {}
    ~Logger() {}
    void startTimer();
    void endTimer();
    void sleep(size_t seconds);
    void log(const std::string& message);

private:
    std::chrono::milliseconds _duration;
    std::chrono::high_resolution_clock::time_point _start, _stop;
};


template <typename OutputMethod>
    void Logger<OutputMethod>::startTimer() {
        _start = std::chrono::high_resolution_clock::now();
    }

template <typename OutputMethod>
    void Logger<OutputMethod>::endTimer() {
        _stop = std::chrono::high_resolution_clock::now();
        _duration = std::chrono::duration_cast<std::chrono::milliseconds>(_stop - _start);

        std::ostringstream oss;
        oss << "\nTime taken:  " << _duration.count() << " milliseconds" << std::endl;
        OutputMethod::output(oss.str());
    }

template <typename OutputMethod>
    void Logger<OutputMethod>::sleep(size_t seconds)
    {
        std::chrono::seconds sleepDuration(seconds);
        std::this_thread::sleep_for(sleepDuration);

    }

template <typename OutputMethod>
    void Logger<OutputMethod>::log(const std::string& message)
    {
            OutputMethod::output(message);
    }


class ConsoleOutput {
public:
    static void output(const std::string& message);
};

class FileOutput {
public:
    FileOutput();
    ~FileOutput();
    void output(const std::string& message);
private:
    std::ofstream _outfile;
};