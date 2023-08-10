
#ifndef LOGGING_LOGGING_HH
#define LOGGING_LOGGING_HH

#include <iostream>
#include <mutex>

namespace klog {

    enum level {
        FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    };

    class Logging {
    public:
        ~Logging();

        void inline set_log_level(level _level)
        { m_log_level = _level; }

        // Logging &operator<< (char c);

        Logging inline &operator<< (const char *msg)
        { if (m_log_level >= m_line_level) std::cout << msg; return *this; }

        template<typename T>
        Logging &operator<< (const T& value) {
            if ( m_line_level > m_log_level )
                return *this;
            std::cout << value;
            return *this;
        }

        Logging inline &operator<< (std::ostream& (*manipulator)(std::ostream&))
        { std::cout << manipulator; return *this; }

        Logging inline &operator<<(Logging& (*manipulator)(Logging &))
        { return manipulator(*this); }

        Logging &operator() (level _level);

    public:
        inline void __unlock()
        { lock.unlock(); }

        inline void __set_time_to_wait(std::chrono::milliseconds time)
        { time_to_wait = time; }

    private:
//        Logging() = default;
        level m_log_level = INFO;
        level m_line_level;

        std::timed_mutex lock;

        /**
         * @brief Time to wait if the logger is not correctly closed or ended,
         * with the @c endl function to end the log line. It is specified in 
         * milliseconds.
         */
        std::chrono::milliseconds time_to_wait = std::chrono::milliseconds(500);

    };

    static Logging console_log;

    inline Logging &endl(Logging &logger)
    { (logger << '\n').__unlock(); return logger; }

    inline Logging &flush(Logging &logger)
    {  return logger << std::endl; }
}

// An alter name for the console_log for easy access.
#define LOG klog::console_log

#define TRACE klog::level::TRACE
#define DEBUG klog::level::DEBUG
#define INFO klog::level::INFO
#define WARN klog::level::WARN
#define ERROR klog::level::ERROR
#define FATAL klog::level::FATAL


#endif //LOGGING_LOGGING_HH
