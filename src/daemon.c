/**
 * Credits: http://peterlombardo.wikidot.com/linux-daemon-in-c
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include "mbpfan.h"
#include "global.h"

#define DAEMON_NAME "mbpfan"
#define PID_FILE "/var/run/mbpfan.pid"


void signal_handler(int signal)
{

        switch(signal) {
        case SIGHUP:
                //TODO: restart myself
                syslog(LOG_WARNING, "Received SIGHUP signal.");
                exit(0);
                break;
        case SIGTERM:
                syslog(LOG_WARNING, "Received SIGTERM signal.");
                //TODO: free resources
                exit(0);
                break;
        case SIGINT:
                syslog(LOG_WARNING, "Received SIGINT signal.");
                //TODO: free resources
                exit(0);
        default:
                syslog(LOG_WARNING, "Unhandled signal (%d) %s", signal, strsignal(signal));
                break;
        }
}


void go_daemon(void (*function)())
{

        // Setup signal handling before we start
        signal(SIGHUP, signal_handler);
        signal(SIGTERM, signal_handler);
        signal(SIGINT, signal_handler);

        syslog(LOG_INFO, "%s starting up", DAEMON_NAME);

        // Setup syslog logging - see SETLOGMASK(3)
        if(verbose) {
                setlogmask(LOG_UPTO(LOG_DEBUG));
                openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
        } else {
                setlogmask(LOG_UPTO(LOG_INFO));
                openlog(DAEMON_NAME, LOG_CONS, LOG_USER);
        }


        pid_t pid;
        pid_t sid;

        if (daemonize) {

                pid = fork();
                if (pid < 0) {
                        exit(EXIT_FAILURE);
                }
                if (pid > 0) {
                        exit(EXIT_SUCCESS);
                }

                umask(0);

                // new SID for the child process
                sid = setsid();
                if (sid < 0) {
                        exit(EXIT_FAILURE);
                }

                if ((chdir("/")) < 0) {
                        exit(EXIT_FAILURE);
                }

                /* Close out the standard file descriptors */
                close(STDIN_FILENO);
                close(STDOUT_FILENO);
                close(STDERR_FILENO);
        }


        function();

        if(daemonize)
                syslog(LOG_INFO, "%s daemon exiting", DAEMON_NAME);

        return;
}
