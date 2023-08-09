
#ifndef LOGGING_LOGGING_HH
#define LOGGING_LOGGING_HH

#include <iostream>
#include <mutex>

enum level {
    FATAL, ERROR, WARN, INFO, DEBUG, TRACE
};

namespace klog {

    static std::mutex console_lock;

    class Logging {
    public:
        ~Logging();

        void set_log_level(level _level);

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

    private:
//        Logging() = default;
        level m_log_level = DEBUG;
        level m_line_level;

    };

    static Logging console_log;

    static inline Logging &endl(Logging &logger)
    { return logger << '\n'; }

    static inline Logging &flush(Logging &logger)
    {  return logger << std::endl; }
}

// An alter name for the console_log for easy access.
#define LOG klog::console_log


#endif //LOGGING_LOGGING_HH
