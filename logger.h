/**
 * \author Michael Roth
 * \date 11.03.2020
 * \brief Logging Facility
 *
 *  This is a simple Logging Facility which writes logs to a text file.
 *
 * Logging is achieved via a template function inside the class, which takes a
 * loggable argument as parameter. This argument must have a << operator to
 * write to a stream.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
using std::ofstream;
using std::string;

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
using std::flush;
using std::localtime;
using std::put_time;
using std::chrono::system_clock;

namespace logging {

class Logger {
public:

    static const int ERROR, WARN, INFO;

    //Deactivate Copy Constructer
    Logger(const Logger&) = delete;

    //Create Public Static Instance
    static Logger& instance() {
        return m_inst;
    }

    //Declare set Function
    void set(const std::string &name, int maxLogLevel);


    template <typename T> void log(const int &level, const T &info) {
      //Get System Time
      auto time = system_clock::to_time_t(system_clock::now());
      //Check if Loglevel is within the declared MaxLogLevel and is Valid
      if(level <= m_LogLevel && level >= 0)
          switch (level) {
              case 0: m_file << "[" << "ERROR " << std::put_time(std::localtime(&time), "%F %T] ") << info << std::endl;
                      break;
              case 1: m_file << "[" << "WARN " << std::put_time(std::localtime(&time), "%F %T] ") << info << std::endl;
                      break;
              case 2: m_file << "[" << "INFO " << std::put_time(std::localtime(&time), "%F %T] ") << info << std::endl;
                      break;
          }
    }

private:

    //Private Con and Destructer so we can achieve the Singleton Pattern
    Logger();
    ~Logger();
    ofstream m_file;
    int m_LogLevel;
    string m_name;

    static Logger m_inst;
    };
}

#endif
