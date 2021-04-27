#include <cstdlib>
#include <dbus-cxx.h>
#include <vector>
#include <atomic>

extern "C" {
#include "common/common.h"
}

std::atomic<int> counter = 0;

std::vector<int> communicate(std::vector<int> msg) {
    counter++;
    return msg;
}

int main(int argc, char *argv[]) {

    Arguments args;

    parse_arguments(&args, argc, argv);

    DBus::init();

    DBus::Dispatcher::pointer dispatcher = DBus::Dispatcher::create();

    DBus::Connection::pointer conn =
            dispatcher->create_connection(DBus::BUS_SESSION);

    auto ret = conn->request_name("dbuscxx.quickstart_0.server",
                                  DBUS_NAME_FLAG_REPLACE_EXISTING);
    if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) return 1;

    DBus::Object::pointer object = conn->create_object("/dbuscxx/quickstart_0");

    object->create_method<std::vector<int>, std::vector<int>>("dbuscxx.Quickstart", "communicate",
                                                              sigc::ptr_fun(communicate));

    // wait until all messages have been returned
    while (counter < args.count) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return EXIT_SUCCESS;
}

