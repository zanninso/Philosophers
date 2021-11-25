#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>


#define TRY_TAKE_FORK_MSG "%15lu %lu is trying to take a fork\n"
#define FORK_TAKEN_MSG "%15lu %lu has taken a fork\n"
#define FORK_FREED_MSG "%15lu %lu has freed a fork\n"
#define EATING_MSG "%15lu %lu is eating\n"
#define SLEEPING_MSG "%15lu %lu is sleeping\n"
#define THINKING_MSG "%15lu %lu is thinking\n"
#define DEAD_MSG "%15lu %lu DEAD\n"

typedef struct timeval t_time;

typedef struct  s_env
{
    sem_t       *forks;
    sem_t       *forks_queue;
    size_t      nb_meals;
    size_t      philos_number;
    size_t      sleeping_time;
    size_t      eating_time;
    size_t      die_time;
    size_t      id;
}               t_env;


enum 
{
    LIVE,
    DEAD
};

enum
{
    false,
    true
};

enum
{
    PRINTER_INIT,
    PRINTER_DESTROY,
    PRINTER_PRINT,
};

enum
{
    FORK_TAKEN,
    FORK_FREE
};

_Bool init_forks(t_env *env);
void destroy_forks(t_env *env);
void set_fork_ids(size_t philo_id, t_env *env);
_Bool get_forks(t_philo *philo);
void drop_forks(t_philo *philo);

_Bool init_philos(t_env *env);
void destroy_philos(t_env *env);
void *routine(void *venv);

void *ft_memcpy(void *vdest, void *vsrc, size_t size);
long long	ft_atoi(const char *s);
size_t get_timestamp();
void ft_sleep(size_t time);
ft_print(int action, const char *msg, size_t time, size_t id);

#endif