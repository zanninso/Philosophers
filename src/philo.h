#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct timeval t_time;

typedef struct  s_fork
{
    pthread_mutex_t lock;
    int             status;
}               t_fork;

typedef struct s_philo
{
    unsigned int id;
    unsigned int eat_counter;
    unsigned int should_eat_counter;
    int status;
}               t_philo;

typedef struct  s_env
{
    t_philo *philos;
    t_fork *forks;
    pthread_t *thread_ids;
    pthread_mutex_t born_lock;
    pthread_mutex_t printer_lock;
    unsigned int philos_number;
    unsigned int should_eat_counter;
    unsigned int sleeping_time;
    unsigned int thinking_time;
    unsigned int eating_time;
    unsigned int die_time;
    unsigned int current_id;
    _Bool        is_end;
}               t_env;


enum 
{
    WAITING_FORKS,
    EATING,
    SLEEPING,
    THINKING
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

int fork_id(unsigned int philo_id, int direction, t_env *env);
void set_forks(unsigned int philo_id, int val, t_env *env);
void set_forks_with_lock(unsigned int philo_id, int val, t_env *env);
void get_forks(unsigned int philo_id, t_env *env);

void *ft_memcpy(void *vdest, void *vsrc, size_t size);

long long	ft_atoi(const char *s);
void *born_philo(void *venv);

#endif