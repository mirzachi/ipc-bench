#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dbus-cxx.h>
#include <vector>
#include <iostream>


std::vector<int> test(std::vector<int> buffer) {

    std::cout << "test" << std::endl;
    return buffer;
}

int main(int argc, char* argv[]) {
    int ret;

    DBus::init();

    DBus::Dispatcher::pointer dispatcher = DBus::Dispatcher::create();

    DBus::Connection::pointer conn =
            dispatcher->create_connection(DBus::BUS_SESSION);

    ret = conn->request_name("dbuscxx.quickstart_0.server",
                             DBUS_NAME_FLAG_REPLACE_EXISTING);
    if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) return 1;

    DBus::Object::pointer object = conn->create_object("/dbuscxx/quickstart_0");

    object->create_method<std::vector<int>, std::vector<int>>("dbuscxx.Quickstart", "test", sigc::ptr_fun(test));

    sleep(10);

    return EXIT_SUCCESS;
}
