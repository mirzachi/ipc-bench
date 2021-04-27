#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "common/common.h"

void communicate(int socketFd, struct Arguments* args) {
	int rc;
	int message;
	void* buffer;

	buffer = malloc(args->size);

	memset(buffer, '*', args->size);

	sleep(1);

	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 2000;

	for (message = 0; message < args->count; ++message) {

		// Send data to the client
		rc = nn_send(socketFd, buffer, args->size, 0);

		if (rc < 0) {
			/*  There are several legitimate reasons this can fail.
					We note them for debugging purposes, but then ignore
					otherwise.  If the socket is closed or failing, we will
					notice in recv above, and exit then. */
			fprintf (stderr, "nn_send: %s (ignoring)\n",
							 nn_strerror (nn_errno ()));
		}
		nanosleep(&ts, &ts);
		//printf("Server %d\n", message);

	}

	free(buffer);
}

void cleanup(int socketFd) {
	nn_close(socketFd);
}

int create_socket() {
	// The socket we will create.
	int socketFd;
	const char* address;

	/*  Create the socket. */
	socketFd = nn_socket (AF_SP, NN_PUB);
	if (socketFd < 0) {
		fprintf (stderr, "nn_socket: %s\n", nn_strerror (nn_errno ()));
		return (-1);
	}

	// 2MB limit on the outbound queue
	void* option;
	option = malloc(sizeof(int));
	*(int*)option = 12000000;
	nn_setsockopt (socketFd, NN_SOL_SOCKET , NN_SNDBUF, option, sizeof(int));

	address = "ipc:///tmp/nanomsg_ipc";

	if (nn_bind(socketFd, address) < 0) {
		fprintf (stderr, "nn_connect: %s\n", nn_strerror (nn_errno ()));
		nn_close (socketFd);
		return (-1);
	}

	return socketFd;
}


int main(int argc, char* argv[]) {
	int socketFd;

	// For parsing command-line arguments
	struct Arguments args;

	parse_arguments(&args, argc, argv);

	socketFd = create_socket();

	communicate(socketFd, &args);

	cleanup(socketFd);

	return EXIT_SUCCESS;
}
