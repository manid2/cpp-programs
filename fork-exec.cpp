#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const char *ch_proc_name = "./lfe_exe";

int main(int argc, char *argv[])
{
	printf("lfe: process start\n");
	pid_t ch_pid = fork();
	if (ch_pid > 0) {
		printf("lfe: in parent process\n");

		while (1) {
			sleep(5);
			const char *gcov_prefix = getenv("GCOV_PREFIX");
			const char *gcov_prefix_strip =
			    getenv("GCOV_PREFIX_STRIP");
			printf("lfe: printing environment variables, "
			       "GCOV_PREFIX=[%s]; GCOV_PREFIX_STRIP=[%s];\n",
			       gcov_prefix ? gcov_prefix : "",
			       gcov_prefix_strip ? gcov_prefix_strip : "");
		}
	} else if (ch_pid < 0) {
		perror("lfe: error when fork()!\n");
		return EXIT_FAILURE;
	} else {
		printf("lfe: in child process\n");
		argv[0] = (char *)ch_proc_name;
		execv(argv[0], argv);
		// The exec() functions return only if an error has occurred.
		perror("lfe: error when execv()\n");
		return (EXIT_FAILURE + 1);
	}

	// wait for all child processes
	int status;
	pid_t wait_result;
	while ((wait_result = wait(&status)) != -1) {
		printf("Process %lu returned result: %d\n",
		       (unsigned long)wait_result, status);
	}
	printf("All children have finished.\n");
	return EXIT_SUCCESS;
}
