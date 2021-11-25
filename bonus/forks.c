#include "philo.h"

_Bool init_forks(t_env *env)
{
    env->forks = sem_open("forks", O_CREAT, S_IRUSR | S_IWUSR , env->philos_number);
    env->forks_queue = sem_open("forks_queue", O_CREAT, S_IRUSR | S_IWUSR , env->philos_number / 2);
}

void destroy_forks(t_env *env)
{
    sem_close(env->forks);
    sem_close(env->forks_queue);
}

void get_forks(t_philo *philo)
{
    sem_wait(philo->forks_queue);
    sem_wait(philo->forks);
    printf(FORK_TAKEN_MSG, get_timestamp() ,philo->id);
    sem_wait(philo->forks);
    printf(FORK_TAKEN_MSG, get_timestamp(), philo->id);
    sem_post(philo->forks_queue);
}

void drop_forks(t_philo *philo)
{
    sem_post(philo->forks);
    sem_post(philo->forks);
    printf(FORK_FREED_MSG, get_timestamp(), philo->id);
    printf(FORK_FREED_MSG, get_timestamp(), philo->id);
}