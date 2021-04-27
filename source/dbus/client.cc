#include <stdlib.h>
#include <dbus-cxx.h>
#include <vector>
#include <iostream>
#include <chrono>

using namespace std::chrono;

void communicate(DBus::ObjectProxy::pointer& object, char* argv[]) {

	DBus::MethodProxy<std::vector<int>, std::vector<int>>& test_proxy
			= *(object->create_method<std::vector<int>, std::vector<int>>("dbuscxx.Quickstart","test"));
	std::vector<int> buffer;
	buffer.reserve(8192);

	auto start = high_resolution_clock::now();
	for (int i = 0; i < 10000; i++) {
		std::cout << "Proxy invocation" << std::endl;
		buffer = test_proxy(buffer);
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << duration.count() << std::endl;
}

int main(int argc, char* argv[]) {
	DBus::init();

	DBus::Dispatcher::pointer dispatcher;
	dispatcher = DBus::Dispatcher::create();

	DBus::Connection::pointer connection;
	connection = dispatcher->create_connection( DBus::BUS_SESSION );

	// create an object proxy, which stands in for a real object.
	// a proxy exists over the dbus
	DBus::ObjectProxy::pointer object;
	object = connection->create_object_proxy("dbuscxx.quickstart_0.server", "/dbuscxx/quickstart_0");

	communicate(object, argv);

	return EXIT_SUCCESS;
}
