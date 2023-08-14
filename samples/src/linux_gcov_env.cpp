// C++ program to print gcov environment variables for debugging.
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// extern gcov flush
extern "C" void __gcov_flush(void);

/* handle signal, dump gcov and exit. */
void sig_handler(int sig) {
    switch(sig){
        case SIGINT:
        case SIGTERM:
        case SIGUSR1:
        printf("received signal=[%d]\n", sig);
        break;
        default:
        printf("received unexpected signal=[%d]!!!\n", sig);
        return;
    }
    const char *gcov_prefix = getenv("GCOV_PREFIX");
    const char *gcov_prefix_strip = getenv("GCOV_PREFIX_STRIP");
    printf("printing environment variables, "
            "GCOV_PREFIX=[%s]; GCOV_PREFIX_STRIP=[%s];\n",
            gcov_prefix ? gcov_prefix : "",
            gcov_prefix_strip ? gcov_prefix_strip : "");
    printf("dumping gcov data files i.e. .gcda files\n");
    __gcov_flush();
    //printf("exiting process\n"); // exiting is not needed
    //_exit(sig);
}

/*
 * test code main func
 *
 * created specifically to add signal handlers and dump gcov data files
 * as gcov generates data files only on process exit.
 */
int main(int argc, char **argv) {
    int ret = EXIT_SUCCESS;
    signal(SIGINT, sig_handler); // Register SIGINT
    signal(SIGTERM, sig_handler); // Register SIGTERM
    signal(SIGUSR1, sig_handler); // Register SIGUSR1
    /* NOTE:
     * * Calling setenv within the test process is better than setting
     *   environment variables in shell as it localizes the process environment
     *   and works well when the process is started by a fork() & exec().
     * * In case of fork() and exec() the environment variables will be same as
     *   they are in parent process which may not be under our control.
     * * Environment variables are copied from the shell/parent process when
     *   the process is started and cannot be changed/added from outside it. */
    setenv("GCOV_PREFIX", get_current_dir_name(), 1);
    setenv("GCOV_PREFIX_STRIP", "6", 1);
    // add your logic here
    while(1){}; // use this when debugging.
    return ret;
}
