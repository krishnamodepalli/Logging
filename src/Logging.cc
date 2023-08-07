//
// Created by krish on 8/6/2023.
//

#include "Logging.hh"


Log::Logging &Log::Logging::operator()(level _level) {
    std::cout.flush();
    m_line_level = _level;
    if ( m_log_level < m_line_level )
        return *this;
    if ( _level == TRACE ) *this << "[TRACE] ";
    else if ( _level == DEBUG ) *this << "[DEBUG] ";
    else if ( _level == INFO ) *this << "[INFO] \t";
    else if ( _level == WARN ) *this << "[WARN] \t";
    else if ( _level == ERROR ) *this << "[ERROR] ";
    else if ( _level == FATAL ) *this << "[FATAL] ";
    return *this;
}

void Log::Logging::set_log_level(level _level) { m_log_level = _level; }

Log::Logging::~Logging() {
    std::cout.flush();
}

Log::Logging &Log::Logging::operator<<(std::ostream &(*manipulator)(std::ostream &)) {
    std::cout << manipulator;
    return *this;
}

Log::Logging &Log::Logging::operator<<(const char *msg) {
    if ( m_line_level > m_log_level )
        return *this;

    std::cout << msg;
    return *this;
}

Log::Logging &Log::Logging::operator<<(char c) {
    if ( m_line_level > m_log_level )
        return *this;
    std::cout << c;
    return *this;
}

