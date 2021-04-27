#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <zmq.h>

#include "common/common.h"

void communicate(void* socket, struct Arguments* args) {
	struct Benchmarks bench;
	bool first = true;
	void* buffer = malloc(args->size);

	Arguments argsCopy = *args;

	for (; args->count > 0; --args->count) {
		if (first) {

			// Receive data from the server
			if (zmq_recv(socket, buffer, args->size, 0) < args->size) {
				throwError("Error receiving on client-side");
			}
			// wrong measurement to avoid 1s offset of the server side
			setup_benchmarks(&bench);
			bench.single_start = now();
			benchmark(&bench);
			first = false;
		} else {
			bench.single_start = now();

			// Receive data from the server
			if (zmq_recv(socket, buffer, args->size, 0) < args->size) {
				throwError("Error receiving on client-side");
			}

			benchmark(&bench);
		}
	}

	evaluate(&bench, &argsCopy);
	free(buffer);
}

void cleanup(void* context, void* socket) {
	zmq_close(socket);
	zmq_ctx_destroy(context);
}

void* create_socket(void* context, int use_tcp) {
	// The socket we will create.
	void* socket;
	const char* address;

	// Create a new zmq socket. Note that this is not necessarily
	// a socket in the traditional sense, i.e. that performs
	// network or UNIX-domain I/O. It is just the name ZMQ gives
	// to any of its "connected nodes". The final transmission
	// medium is chosen later, in the call to bind().
	// The second argument to the function specifies the network
	// architecture/pattern of the message queue and this socket's
	// role in that pattern. For example, we will use the simple
	// reply-request model for our server/client pair. In this
	// pattern, there is one (or more) replying node (the server),
	// who thus passes ZMQ_REP, and one (or more) requesting nodes
	// (the client), who passes ZMQ_REQ.
	if ((socket = zmq_socket(context, ZMQ_SUB)) == NULL) {
		throwError("Error creating socket");
	}

	// no limit on the inbound queue
	void* option;
	option = malloc(sizeof(int));
	*(char*)option = 0;
	zmq_setsockopt(socket, ZMQ_RCVHWM, option, sizeof(int));

	// address = use_tcp ? "tcp://localhost:6969" : "ipc:///tmp/zmq_ipc";
	address = "ipc:///tmp/zmq_ipc";

	// Just like for the call to bind() on the server-side,
	// we now bind (connect) our socket to an address. In
	// doing so, we also tell zmq the transport medium for
	// our connection, in this case a TCP port on localhost
	// with port 6969.
	if (zmq_connect(socket, address) == -1) {
		throwError("Error binding socket to address");
	}

	zmq_setsockopt(socket, ZMQ_SUBSCRIBE, "", 0);

	free(option);
	return socket;
}

void* create_context() {
	void* context;

	// Create a new zmq context, which is the
	// main "control unit" for zmq.
	if ((context = zmq_ctx_new()) == NULL) {
		throwError("Error creating ZMQ context");
	}

	return context;
}

int main(int argc, char* argv[]) {
	void* context;
	void* socket;
	int use_tcp;

	// For parsing command-line arguments
	struct Arguments args;

	use_tcp = check_flag("tcp", argc, argv);
	parse_arguments(&args, argc, argv);

	context = create_context();
	socket = create_socket(context, use_tcp);

	communicate(socket, &args);

	cleanup(context, socket);

	return EXIT_SUCCESS;
}
