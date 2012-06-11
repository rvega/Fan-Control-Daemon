/**
 * ...handles signals :-)
 */
void signal_handler(int signal);

/**
 * Daemonizes
 */
int go_daemon(void (*function)());