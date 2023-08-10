
#include "Logging.hh"


klog::Logging &klog::Logging::operator()(level _level) {
    // lock.lock();     This doesn't help much for the synchronization.
    if ( ! lock.try_lock_for(std::chrono::milliseconds(time_to_wait)) ) {
        lock.unlock();      // Unlocking the previous lock.
        lock.lock();        // Locking for the next line.
    }

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

// Defined as inline in the header.
// void klog::Logging::set_log_level(level _level) { m_log_level = _level; }

klog::Logging::~Logging() {
    flush(*this);
}


// klog::Logging &klog::Logging::operator<<(char c) {
//     if ( m_line_level > m_log_level )
//         return *this;
//     std::cout << c;
//     return *this;
// }

