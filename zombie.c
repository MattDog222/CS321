#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
// @author Matthew Wilder
int main(void) {
	pid_t pid;
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Error\n");
		return -1;
	}
	else if (pid == 0) { 
		// child
		return 0;
	} else {
		// wait for 15 seconds
		sleep(15); 
		printf("Parent exiting");
		return 0;
	}
}