/* file minunit_example.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "mbpfan.h"
#include "minunit.h"

int tests_run = 0;


struct s_sensors
{
  char* path;
  char* fan_min_path;
  char* fan_man_path;
  unsigned int temperature;
  struct s_sensors *next;
};
typedef s_sensors t_sensors;


static char *test_sensor_paths()
{
  t_sensors* sensors = retrieve_sensors();
  mu_assert("No sensors found", sensors != NULL);
  t_sensors* tmp = sensors;
  while(tmp != NULL)
    {
      mu_assert("Sensor does not have a valid path", tmp->path != NULL);
      if(tmp->path != NULL)
        mu_assert("Sensor does not have valid temperature", tmp->temperature > 0);
      tmp = tmp->next;
    }
  return 0;
}


static char *test_fan_paths()
{
  t_sensors* sensors = retrieve_sensors();
  mu_assert("No sensors found", sensors != NULL);
  t_sensors* tmp = sensors;
  int found_fan_path = 0;
  while(tmp != NULL)
    {
      if(tmp->fan_min_path != NULL)
        found_fan_path++;
      tmp = tmp->next;
    }
  mu_assert("No fans found", found_fan_path != 0);
  return 0;
}

unsigned time_seed()
{
  time_t now = time ( 0 );
  unsigned char *p = (unsigned char *)&now;
  unsigned seed = 0;
  size_t i;
  for ( i = 0; i < sizeof now; i++ )
    seed = seed * ( UCHAR_MAX + 2U ) + p[i];
  return seed;
}

// nothing better than a horrible piece of code to
// stress a little bit the CPU
int stress(int n)
{
  int f = n;
  while (f > 0)
    {
      while(n > 0)
        {
          srand ( time_seed() );
          n--;
        }
      f--;
      n = f;
    }
}

static char *test_get_temp()
{
  t_sensors* sensors = retrieve_sensors();
  mu_assert("No sensors found", sensors != NULL);
  unsigned short temp_1 = get_temp(sensors);
  mu_assert("Invalid Global Temperature Found", temp_1 > 1 && temp_1 < 150);
  stress(2000);
  unsigned short temp_2 = get_temp(sensors);
  mu_assert("Invalid Higher temp test (if fan was already spinning high, this is not worrying)", temp_1 < temp_2);
  return 0;
}


static char *all_tests()
{
  mu_run_test(test_sensor_paths);
  mu_run_test(test_fan_paths);
  mu_run_test(test_get_temp);
  return 0;
}

int tests()
{
  printf("Starting the tests..\n");
  printf("It is normal for them to take a bit to finish.\n");
  char *result = all_tests();
  if (result != 0)
    {
      printf("%s \n", result);
    }
  else
    {
      printf("ALL TESTS PASSED\n");
    }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}