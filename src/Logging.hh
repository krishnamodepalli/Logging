
#ifndef LOGGING_LOGGING_HH
#define LOGGING_LOGGING_HH

#include <iostream>
#include <mutex>

enum level {
    FATAL, ERROR, WARN, INFO, DEBUG, TRACE
};

namespace Log {

    static std::mutex console_lock;

    class Logging {
    public:
        ~Logging();

        void set_log_level(level _level);

        Logging &operator<< (char c);

        Logging &operator<< (const char *msg);

        template<typename T>
        Logging &operator<< (const T& value) {
            if ( m_line_level > m_log_level )
                return *this;
            std::cout << value;
            return *this;
        }

        Logging &operator<< (std::ostream& (*manipulator)(std::ostream&));

        Logging &operator() (level _level);

        static Logging LOG;
    private:
//        Logging() = default;
        level m_log_level = DEBUG;
        level m_line_level;

    };

    static Logging console_log;
}

#define LOG Log::console_log


#endif //LOGGING_LOGGING_HH
