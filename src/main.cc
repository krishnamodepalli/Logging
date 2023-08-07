

#include "Logging.hh"

int main() {
    LOG.set_log_level(DEBUG);

    LOG(INFO) << "Creating a Point Object.\n";
    LOG(INFO) << "Successfully created a Point object with values " << 3.4f << " " << 3.5f << '\n';
    LOG(INFO) << "The Object is " << p << std::endl;


    return 0;
}
