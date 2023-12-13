
#ifndef LOGGING_LOGGING_HH
#define LOGGING_LOGGING_HH

#include <iostream>
#include <mutex>
#include <cstring>

namespace klog {

    enum log_level {
        FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    };

    class ksynclog {
    public:
        ksynclog() = default;
        ~ksynclog();

        void inline set_log_level(log_level _level)
        { m_log_level = _level; }

        // ksynclog &operator<< (char c);

        ksynclog inline &operator<< (const char *msg)
        { if (m_log_level >= m_line_level) std::cout << msg; return *this; }

        template<typename T>
        ksynclog &operator<< (const T& value) {
            if ( m_line_level > m_log_level )
                return *this;
            // std::cout << value;
            // adding to the log_buffer
            // log_buffer.append(std::to_string(value));
            append_to_buffer(log_buffer, std::to_string(value).c_str());
            return *this;
        }

        ksynclog inline &operator<< (std::ostream& (*manipulator)(std::ostream&))
        { std::cout << manipulator; return *this; }

        ksynclog inline &operator<<(ksynclog& (*manipulator)(ksynclog &))
        { return manipulator(*this); }

        ksynclog &operator() (log_level _level);

        size_t fatal(const char *fmt, ...);
        size_t error(const char *fmt, ...);
        size_t warn(const char *fmt, ...);
        size_t info(const char *fmt, ...);
        size_t debug(const char *fmt, ...);
        size_t trace(const char *fmt, ...);

    public:
        inline void __set_time_to_wait(std::chrono::milliseconds time)
        { time_to_wait = time; }

        friend ksynclog &endl(ksynclog &);

    private:
        inline void __unlock()
        { lock.unlock(); }

        inline void flush_buffer()
        { std::memset(log_buffer, '\0', 256); }

        inline void append_to_buffer(char *buffer, const char c)
        { buffer[buffer_size++] = c; }

        inline void append_to_buffer(char *buffer, const char *str)
        {   std::memcpy(buffer+buffer_size, str, std::strlen(str));
            buffer_size += std::strlen(str);    }

    private:
//        ksynclog() = default;
        log_level m_log_level = INFO;
        log_level m_line_level;

        std::timed_mutex lock;

        /**
         * @brief Time to wait if the logger is not correctly closed or ended,
         * with the @c endl function to end the log line. It is specified in 
         * milliseconds.
         */
        std::chrono::milliseconds time_to_wait = std::chrono::milliseconds(500);


        char log_buffer[256];
        size_t buffer_size = 0;
    };

    static ksynclog console_log;

    inline ksynclog &endl(ksynclog &logger)
    { std::cout << logger.log_buffer << '\n';logger.buffer_size = 0; logger.__unlock(); return logger; }

    inline ksynclog &flush(ksynclog &logger)
    {  return logger << std::endl; }

}

// An alter name for the console_log for easy access.
#define LOG klog::console_log

#define TRACE klog::log_level::TRACE
#define DEBUG klog::log_level::DEBUG
#define INFO klog::log_level::INFO
#define WARN klog::log_level::WARN
#define ERROR klog::log_level::ERROR
#define FATAL klog::log_level::FATAL


#endif //LOGGING_LOGGING_HH
