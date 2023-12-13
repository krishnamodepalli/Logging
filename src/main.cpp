

#include "klog.hpp"
#include <thread>

void printer() {
    LOG.error("Hello");
}

int main() {
    LOG.set_log_level(DEBUG);
    LOG.__set_time_to_wait(std::chrono::milliseconds(2000));

    printer();



    return 0;
}
