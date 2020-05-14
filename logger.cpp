#include "logger.h"

namespace logging {

Logger::~Logger() {}

Logger::Logger() {}

void Logger::set(debug_level level, const std::string &name) {
    m_LogLevel = level;
    m_name = name;
}

void Logger::close() {
    m_file << flush;
    //Close any Open files
    m_file.close();
}

void Logger::open() {
    m_file.open(m_name, std::ios_base::app);
    if (!m_file.is_open()) {
        std::cout << "error with file\n";
        throw std::runtime_error("Log file could not be opened!");
    }
}

};
