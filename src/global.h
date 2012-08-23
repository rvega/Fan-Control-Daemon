#ifndef _GLOBAL_H_
#define _GLOBAL_H_

extern int daemonize;
extern int verbose;

extern const char* program_name;
extern const char* program_pid;

struct s_sensors {
    char* path;
    char* fan_output_path;
    char* fan_manual_path;
    unsigned int temperature;
    struct s_sensors *next;
};

typedef s_sensors t_sensors;
#endif