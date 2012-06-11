#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mbpfan.h"
#include "daemon.h"
#include "global.h"

int daemonize = 1;
int verbose = 0;

void print_usage(int argc, char *argv[])
{
        if (argc >=1) {
                printf("Usage: %s OPTION(S) \n", argv[0]);
                printf("Options:\n");
                printf("\t-h Show this help screen\n");
                printf("\t-f Run in foreground\n");
                printf("\t-v Be (a lot) verbose\n");
                printf("\n");
        }
}

int main(int argc, char *argv[])
{

        int c;
        while( (c = getopt(argc, argv, "hfv|help")) != -1) {
                switch(c) {
                case 'h':
                        print_usage(argc, argv);
                        exit(0);
                        break;
                case 'f':
                        daemonize = 0;
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

        // pointer to mbpfan() function in mbpfan.c
        void (*function)() = mbpfan;
        go_daemon(function);
        exit(0);
}