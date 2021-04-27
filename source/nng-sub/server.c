#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>

#include "common/common.h"

void communicate(nng_socket* socket, struct Arguments* args) {
	int message, rv;
	void* buffer;

	// has to be allocated each ti
	//buffer = nng_alloc(args->size);
	buffer = malloc(args->size);
	memset(buffer, '*', args->size);

	sleep(1);

	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 2000;

	for (message = 0; message < args->count; ++message) {

		// Send data to the client
		//printf("1\n");
		rv = nng_send(*socket, buffer, args->size, 0);
		//printf("2\n");

		if ( rv != 0) {
			printf("rv: %i", rv);
			throwError("Error sending on server-side");
		}
		//printf("%i\n", message);
		nanosleep(&ts, &ts);
	}
	free(buffer);
	//printf("3\n");
}

void cleanup(nng_socket* socket) {
	nng_close(*socket);
}

nng_socket* create_socket() {
	// The socket we will create.
	nng_socket* socket =  (nng_socket*)malloc(sizeof(nng_socket));

	if ((nng_pub0_open(socket)) != 0) {
		printf("nng_socket failed");
	}

	if ((nng_listen(*socket, "ipc:///tmp/nng_ipc", NULL, 0)) != 0) {
		printf("nng_listen failed");
	}

	return socket;
}


int main(int argc, char* argv[]) {
	nng_socket *socket;

	// For parsing command-line arguments
	struct Arguments args;

	parse_arguments(&args, argc, argv);

	socket = create_socket();

	communicate(socket, &args);

	cleanup(socket);

	return EXIT_SUCCESS;
}
