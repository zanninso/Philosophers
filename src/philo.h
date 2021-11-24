#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define TRY_TAKE_FORK_MSG "%15lu %lu is trying to take a fork\n"
#define FORK_TAKEN_MSG "%15lu %lu has taken a fork\n"
#define FORK_FRIED_MSG "%15lu %lu has fried a fork\n"
#define EATING_MSG "%15lu %lu is eating\n"
#define SLEEPING_MSG "%15lu %lu is sleeping\n"
#define THINKING_MSG "%15lu %lu is thinking\n"
#define DIED_MSG "%15lu %lu died\n"

typedef struct timeval t_time;

typedef struct  s_fork
{
    pthread_mutex_t lock;
    int             status;
    size_t             last_user;
}               t_fork;

typedef struct s_philo
{
    size_t  *should_eat_counter;
    t_fork  *left_fork;
    t_fork  *right_fork;
    _Bool   *simulation_terminated;
    pthread_mutex_t check_death_lock;
    size_t  id;
    size_t  eat_counter;
    size_t  expected_death_time;
    size_t  sleeping_time;
    size_t  eating_time;
    size_t  die_time;
    int     status;
}               t_philo;

typedef struct  s_env
{
    t_philo     *philos;
    t_fork      *forks;
    pthread_t   *thread_ids;
    size_t      philos_number;
    size_t      should_eat_counter;
    size_t      sleeping_time;
    size_t      thinking_time;
    size_t      eating_time;
    size_t      die_time;
    _Bool       simulation_terminated;
}               t_env;


enum 
{
    LIVE,
    DIED
};

enum
{
    RIGHT,
    LEFT,
};

enum
{
    false,
    true
};

enum
{
    FORK_TAKEN,
    FORK_FREE
};

void set_fork_ids(size_t philo_id, t_env *env);
_Bool get_forks(t_philo *philo);
void drop_forks(t_philo *philo);

void *ft_memcpy(void *vdest, void *vsrc, size_t size);

long long	ft_atoi(const char *s);
void *born_philo(void *venv);

size_t get_timestamp();
void ft_sleep(size_t time);
void init_philo(size_t id, t_env *env);


#endif