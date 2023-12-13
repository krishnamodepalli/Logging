
#include "klog.hpp"
#include <cstdarg>
#include <cstring>


klog::ksynclog &klog::ksynclog::operator()(log_level _level) {
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
// void klog::ksynclog::set_log_level(log_level _level) { m_log_level = _level; }

klog::ksynclog::~ksynclog() {
    flush(*this);
}


// klog::ksynclog &klog::ksynclog::operator<<(char c) {
//     if ( m_line_level > m_log_level )
//         return *this;
//     std::cout << c;
//     return *this;
// }

size_t klog::ksynclog::fatal(const char *fmt, ...) {
    lock.lock();
    // flushing the buffer;
    flush_buffer();
    printf("FATAL:\t");
    buffer_size = 0;
    std::va_list args;
    va_start(args, fmt);

    auto data = log_buffer + buffer_size;

    auto *ptr = fmt;
    size_t count;

  loop:
    count = 0;
    while (ptr + count) {
        if (*(ptr + count) == '%' || *(ptr + count) == '\\' || *(ptr + count) == '\0')  break;
        count++;
    }
    std::memcpy(data + buffer_size, ptr, count);
    buffer_size += count;
    ptr += count;
    if (*ptr == '\0') goto end;


    ptr += 1;
    if (*ptr == '\\')   append_to_buffer(log_buffer, '\\');
    else if (*(ptr) == '%') append_to_buffer(log_buffer, '%');
    else if (*ptr == 'd' )  append_to_buffer(log_buffer, std::to_string(va_arg(args, int)).c_str());
    else if (*ptr == 'c')   append_to_buffer(log_buffer, va_arg(args, int));
    else if (*ptr == 's')   append_to_buffer(log_buffer, va_arg(args, const char *));

    if (*(ptr++) != '\0') goto loop;
  end:
    printf("%s", log_buffer);
    lock.unlock();
    return buffer_size;
}

size_t klog::ksynclog::error(const char *fmt, ...) {
    if (m_log_level < ERROR) return -1;
    lock.lock();
    // flushing the buffer
    flush_buffer();
    printf("ERROR:\t");
    buffer_size = 0;
    std::va_list args;
    va_start(args, fmt);

    auto data = log_buffer + buffer_size;

    auto *ptr = fmt;
    size_t count;

  loop:
    count = 0;
    while (ptr + count) {
        if (*(ptr + count) == '%' || *(ptr + count) == '\\' || *(ptr + count) == '\0')  break;
        count++;
    }
    std::memcpy(data + buffer_size, ptr, count);
    buffer_size += count;
    ptr += count;
    if (*ptr == '\0') goto end;


    ptr += 1;
    if (*ptr == '\\')   append_to_buffer(log_buffer, '\\');
    else if (*(ptr) == '%') append_to_buffer(log_buffer, '%');
    else if (*ptr == 'd' )  append_to_buffer(log_buffer, std::to_string(va_arg(args, int)).c_str());
    else if (*ptr == 'c')   append_to_buffer(log_buffer, va_arg(args, int));
    else if (*ptr == 's')   append_to_buffer(log_buffer, va_arg(args, const char *));

    if (*(ptr++) != '\0') goto loop;
  end:
    printf("%s", log_buffer);
    // flushing the buffer
    std::memset(log_buffer, '\0', 256);
    lock.unlock();
    return buffer_size;
}

size_t klog::ksynclog::warn(const char *fmt, ...) {
    if (m_log_level < WARN) return -1;
    lock.lock();
    // flushing the buffer
    flush_buffer();
    printf("WARNING:\t");
    buffer_size = 0;
    std::va_list args;
    va_start(args, fmt);

    auto data = log_buffer + buffer_size;

    auto *ptr = fmt;
    size_t count;

  loop:
    count = 0;
    while (ptr + count) {
        if (*(ptr + count) == '%' || *(ptr + count) == '\\' || *(ptr + count) == '\0')  break;
        count++;
    }
    std::memcpy(data + buffer_size, ptr, count);
    buffer_size += count;
    ptr += count;
    if (*ptr == '\0') goto end;


    ptr += 1;
    if (*ptr == '\\')   append_to_buffer(log_buffer, '\\');
    else if (*(ptr) == '%') append_to_buffer(log_buffer, '%');
    else if (*ptr == 'd' )  append_to_buffer(log_buffer, std::to_string(va_arg(args, int)).c_str());
    else if (*ptr == 'c')   append_to_buffer(log_buffer, va_arg(args, int));
    else if (*ptr == 's')   append_to_buffer(log_buffer, va_arg(args, const char *));

    if (*(ptr++) != '\0') goto loop;
  end:
    printf("%s", log_buffer);
    // flushing the buffer
    std::memset(log_buffer, '\0', 256);
    lock.unlock();
    return buffer_size;
}

size_t klog::ksynclog::info(const char *fmt, ...) {
    if (m_log_level < INFO) return -1;
    lock.lock();
    // flushing the buffer
    flush_buffer();
    printf("INFO:\t");
    buffer_size = 0;
    std::va_list args;
    va_start(args, fmt);

    auto data = log_buffer + buffer_size;

    auto *ptr = fmt;
    size_t count;

  loop:
    count = 0;
    while (ptr + count) {
        if (*(ptr + count) == '%' || *(ptr + count) == '\\' || *(ptr + count) == '\0')  break;
        count++;
    }
    std::memcpy(data + buffer_size, ptr, count);
    buffer_size += count;
    ptr += count;
    if (*ptr == '\0') goto end;


    ptr += 1;
    if (*ptr == '\\')   append_to_buffer(log_buffer, '\\');
    else if (*(ptr) == '%') append_to_buffer(log_buffer, '%');
    else if (*ptr == 'd' )  append_to_buffer(log_buffer, std::to_string(va_arg(args, int)).c_str());
    else if (*ptr == 'c')   append_to_buffer(log_buffer, va_arg(args, int));
    else if (*ptr == 's')   append_to_buffer(log_buffer, va_arg(args, const char *));

    if (*(ptr++) != '\0') goto loop;
  end:
    printf("%s", log_buffer);
    // flushing the buffer
    std::memset(log_buffer, '\0', 256);
    lock.unlock();
    return buffer_size;
}

size_t klog::ksynclog::debug(const char *fmt, ...) {
    if (m_log_level < DEBUG) return -1;
    lock.lock();
    // flushing the buffer
    flush_buffer();
    printf("DEBUG:\t");
    buffer_size = 0;
    std::va_list args;
    va_start(args, fmt);

    auto data = log_buffer + buffer_size;

    auto *ptr = fmt;
    size_t count;

  loop:
    count = 0;
    while (ptr + count) {
        if (*(ptr + count) == '%' || *(ptr + count) == '\\' || *(ptr + count) == '\0')  break;
        count++;
    }
    std::memcpy(data + buffer_size, ptr, count);
    buffer_size += count;
    ptr += count;
    if (*ptr == '\0') goto end;


    ptr += 1;
    if (*ptr == '\\')   append_to_buffer(log_buffer, '\\');
    else if (*(ptr) == '%') append_to_buffer(log_buffer, '%');
    else if (*ptr == 'd' )  append_to_buffer(log_buffer, std::to_string(va_arg(args, int)).c_str());
    else if (*ptr == 'c')   append_to_buffer(log_buffer, va_arg(args, int));
    else if (*ptr == 's')   append_to_buffer(log_buffer, va_arg(args, const char *));

    if (*(ptr++) != '\0') goto loop;
  end:
    printf("%s", log_buffer);
    // flushing the buffer
    std::memset(log_buffer, '\0', 256);
    lock.unlock();
    return buffer_size;
}

size_t klog::ksynclog::trace(const char *fmt, ...) {
    if (m_log_level < TRACE) return -1;
    lock.lock();
    // flushing the buffer
    flush_buffer();
    printf("TRACE:\t");
    buffer_size = 0;
    std::va_list args;
    va_start(args, fmt);

    auto data = log_buffer + buffer_size;

    auto *ptr = fmt;
    size_t count;

  loop:
    count = 0;
    while (ptr + count) {
        if (*(ptr + count) == '%' || *(ptr + count) == '\\' || *(ptr + count) == '\0')  break;
        count++;
    }
    std::memcpy(data + buffer_size, ptr, count);
    buffer_size += count;
    ptr += count;
    if (*ptr == '\0') goto end;


    ptr += 1;
    if (*ptr == '\\')   append_to_buffer(log_buffer, '\\');
    else if (*(ptr) == '%') append_to_buffer(log_buffer, '%');
    else if (*ptr == 'd' )  append_to_buffer(log_buffer, std::to_string(va_arg(args, int)).c_str());
    else if (*ptr == 'c')   append_to_buffer(log_buffer, va_arg(args, int));
    else if (*ptr == 's')   append_to_buffer(log_buffer, va_arg(args, const char *));

    if (*(ptr++) != '\0') goto loop;
  end:
    printf("%s", log_buffer);
    // flushing the buffer
    std::memset(log_buffer, '\0', 256);
    lock.unlock();
    return buffer_size;
}

