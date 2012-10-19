/**
 *  Copyright (C) (2012) Daniel Graziotin <dgraziotin@task3.cc>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

/**
 * Code formatted with astyle -A3 -s --break-blocks=all --add-brackets *.c *.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mbpfan.h"
#include "daemon.h"
#include "global.h"
#include "minunit.h"
#include <syslog.h>

int daemonize = 1;
int verbose = 0;

const char *program_name = "mbpfan";
const char *program_pid = "/var/run/mbpfan.pid";

void print_usage(int argc, char *argv[])
{
    if (argc >=1) {
        printf("Usage: %s OPTION(S) \n", argv[0]);
        printf("Options:\n");
        printf("\t-h Show this help screen\n");
        printf("\t-f Run in foreground\n");
        printf("\t-t Run the tests\n");
        printf("\t-v Be (a lot) verbose\n");
        printf("\n");
    }
}



int main(int argc, char *argv[])
{

    int c;

    while( (c = getopt(argc, argv, "hftv|help")) != -1) {
        switch(c) {
        case 'h':
            print_usage(argc, argv);
            exit(0);
            break;
        case 'f':
            daemonize = 0;
            break;
        case 't':
            tests();
            exit(0);
            break;
        case 'v':
            verbose = 1;
            break;
        default:
            print_usage(argc, argv);
            exit(0);
            break;
        }
    }

    /**
     * Check for root
     */

    uid_t uid=getuid(), euid=geteuid();

    if (uid != 0 || euid != 0) {
        syslog(LOG_INFO, "Mbpfan needs root privileges. Please run mbpfan as root. Exiting.");
        printf("Mbpfan not started with root privileges. Please run mbpfan as root. Exiting.\n");
        exit(0);
    }

    /**
     * Check for coretemp and applesmc modules
     * Credits: http://stackoverflow.com/questions/12978794
     */

    FILE *fd = popen("lsmod | grep coretemp", "r");

    char buf[16];

    if (!(fread (buf, 1, sizeof (buf), fd) > 0)) {
        syslog(LOG_INFO, "Mbpfan needs coretemp module. Please load it and run mbpfan again. Exiting.");
        printf("Mbpfan needs coretemp module. Please load it and run mbpfan again. Exiting.\n");
    }

    fd = popen("lsmod | grep applesmc", "r");

    if (!(fread (buf, 1, sizeof (buf), fd) > 0)) {
        syslog(LOG_INFO, "Mbpfan needs applesmc module. Please load it and run mbpfan again. Exiting.");
        printf("Mbpfan needs applescm module. Please load it and run mbpfan again. Exiting.\n");
    }

    // pointer to mbpfan() function in mbpfan.c
    void (*fan_control)() = mbpfan;
    go_daemon(fan_control);
    exit(0);
}