#include "logger.h"

namespace logging {

    const int Logger::ERROR = 0;
    const int Logger::WARN = 1;
    const int Logger::INFO = 2;

    Logger::~Logger() {
        m_file << flush;
        m_file.close();
    }

    Logger::Logger() {}

    void Logger::set(const std::string &name, int level) {
        m_LogLevel = level;
        m_name = name;
        //Close any Open files
        m_file.close();

        //std::ofstream::out = File Open for Writing
        //std::ofstream::trunc = Any contents that existed in the file before it is open are discarded.
        m_file.open(m_name, std::ofstream::out | std::ofstream::trunc);
        //Make Sure File is Open
        if (!m_file.is_open()) {
            std::cout << "error with file\n";
            throw std::runtime_error("Log file could not be opened!");
        }
    }

}
