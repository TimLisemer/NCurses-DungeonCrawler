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
//14.05.2020
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

enum debug_level{
   ERROR = 0, WARN = 1, INFO = 2
};

class Logger {
public:

    //static const int ERROR, WARN, INFO;

    //Deactivate Copy Constructer
    Logger(const Logger&) = delete;

    //Create Public Static Instance
    static Logger* instance() {
        if(!m_inst){
            m_inst = new Logger();
        }
        return m_inst;
    }

    //Declare set Function
    void set(debug_level level,const std::string &name);

    void open();
    void close();


    template <typename T> void log(debug_level level,const T &info){
        if(level <= m_LogLevel){
            open();
            auto time = system_clock::to_time_t(system_clock::now());
            m_file << "[" << level << std::put_time(std::localtime(&time), "%F %T]" ) << info << std::endl;
        }
    }


private:
    //consturtor i private (protected)
    Logger();
    ~Logger();

    ofstream m_file;
    int m_LogLevel;
    string m_name;

    //defina a private static attribute of class
    static Logger *m_inst;
    };
}

#endif
