#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

typedef struct s_table   t_table;

typedef struct s_fork
{
  pthread_mutex_t mutex;
  int             id;
} t_fork;

typedef struct s_philo
{
  int      philo_id;
  long      meals_eaten;
  long     last_meal_time;
  bool     full;
  t_fork   *left_fork;
  t_fork   *right_fork;
  pthread_t thread;
  t_table  *table;
} t_philo;

typedef struct s_table
{
  long            philo_nbr;
  long            time_to_die;
  long            time_to_eat;
  long            time_to_sleep;
  long            meals_limit_count;
  bool            stop_simulation;
  long            start_simulation;
  t_philo         *philos;
  t_fork          *forks;
  pthread_mutex_t print_mutex;
} t_table;


void input_parsing(t_table *table, char **argv);
long ft_atol(const char *str);
const char *input_checker(const char *str);
void error_exit(const char *error);