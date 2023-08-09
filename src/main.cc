

#include "Logging.hh"

int main() {
    LOG.set_log_level(DEBUG);
    LOG(INFO) << "hi" << klog::endl;
    LOG(ERROR) << "This is a critical Error" << klog::endl;


    return 0;
}
