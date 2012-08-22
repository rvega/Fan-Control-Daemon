/**
 * This is the MinUnit testing framework - http://www.jera.com/techinfo/jtns/jtn002.html
 */
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)

extern int tests_run;

static char *test_sensor_paths();
static char *test_fan_paths();
static char *test_get_temp();
static char *test_config_file();

static char *all_tests();

int tests();