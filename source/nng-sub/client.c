#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <nng/nng.h>
#include <nng/protocol/pubsub0/sub.h>
#include "nng/supplemental/util/platform.h"

#include "common/common.h"

void communicate(nng_socket* socket, struct Arguments* args) {
	struct Benchmarks bench;
	bool first = true;
	void* buffer = NULL;
	size_t allocatedBufferSize;

	Arguments argsCopy = *args;
	//int i = 0;

	for (; args->count > 0; --args->count) {
		if (first) {

			if (nng_recv(*socket, &buffer, &allocatedBufferSize, NNG_FLAG_ALLOC) != 0) {
				printf("nng_recv failed\n");
			}

			// for each receive, a new buffer is allocated
			// so it has to be deallocated each time as well
			// otherwise memory lead
			nng_free(buffer, allocatedBufferSize);

			// wrong measurement to avoid 1s offset of the server side
			setup_benchmarks(&bench);
			bench.single_start = now();
			benchmark(&bench);
			first = false;
		} else {

			bench.single_start = now();

			//printf("%i\n", i++);

			if (nng_recv(*socket, &buffer, &allocatedBufferSize, NNG_FLAG_ALLOC) != 0) {
				printf("nng_recv failed\n");
			}

			nng_free(buffer, allocatedBufferSize);

			benchmark(&bench);
		}
	}

	evaluate(&bench, &argsCopy);
}

void cleanup(nng_socket* socket) {
	nng_close(*socket);
}

nng_socket* create_socket() {
	// The socket we will create.
	nng_socket* socket =  (nng_socket*)malloc(sizeof(nng_socket));
	int rv;

	if ((rv = nng_sub0_open(socket)) != 0) {
		printf("nng_socket failed\n");
	}

	// subscribe to all topics from the publisher
	nng_setopt(*socket, NNG_OPT_SUB_SUBSCRIBE, (void*) "", 0);

	// set rcv buffer to the possible largest size
	int* receiveBufferSize = (int*) malloc(sizeof(int));
	*receiveBufferSize = 8192;
	nng_setopt(*socket, NNG_OPT_RECVBUF, (void*)receiveBufferSize, sizeof(int));

	rv = NNG_ECONNREFUSED;
	while(rv == NNG_ECONNREFUSED) {
		if ((rv = nng_dial(*socket, "ipc:///tmp/nng_ipc", NULL, 0)) != 0) {
			printf("nng_dial failed\n");
		}
		nng_msleep(50);
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