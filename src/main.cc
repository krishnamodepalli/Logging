

#include "Logging.hh"
#include <thread>

void printer() {
    LOG(INFO) << "hi" << '\n';
    LOG(ERROR) << "This is a critical Error" << klog::endl;
}

int main() {
    LOG.set_log_level(DEBUG);
    LOG.__set_time_to_wait(std::chrono::milliseconds(2000));

    std::thread t1(printer);
    std::thread t2(printer);

    t1.join();
    t2.join();


    return 0;
}
