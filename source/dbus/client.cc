#include <cstdlib>
#include <dbus-cxx.h>
#include <vector>

extern "C" {
#include "common/common.h"
}

void communicate(DBus::ObjectProxy::pointer &object, Arguments *args) {

    Benchmarks bench;

    DBus::MethodProxy<std::vector<int>, std::vector<int>> &communicateProxy
            = *(object->create_method<std::vector<int>, std::vector<int>>("dbuscxx.Quickstart", "communicate"));
    std::vector<int> msg;
    msg.reserve(args->size);

    setup_benchmarks(&bench);

    for (int i = 0; i < args->count; i++) {
        bench.single_start = now();
        msg = communicateProxy(msg);
        benchmark(&bench);
    }
    evaluate(&bench, args);
}

int main(int argc, char *argv[]) {

    Arguments args;

    parse_arguments(&args, argc, argv);

    DBus::init();

    DBus::Dispatcher::pointer dispatcher;
    dispatcher = DBus::Dispatcher::create();

    DBus::Connection::pointer connection;
    connection = dispatcher->create_connection(DBus::BUS_SESSION);

    // create an object proxy, which stands in for a real object.
    // a proxy exists over the dbus
    DBus::ObjectProxy::pointer object;
    object = connection->create_object_proxy("dbuscxx.quickstart_0.server", "/dbuscxx/quickstart_0");

    communicate(object, &args);

    return EXIT_SUCCESS;
}
