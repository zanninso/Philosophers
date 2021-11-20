#include "philo.h"

int fork_id(unsigned int philo_id, int direction, t_env *env)
{
    if (direction == RIGHT)
        return((philo_id + 1) % env->philos_number);
    return((philo_id + env->philos_number - 1) % env->philos_number);
}

void set_forks(unsigned int philo_id, int val, t_env *env)
{
    env->forks[fork_id(philo_id, LEFT, env)].status = val;
    env->forks[fork_id(philo_id, RIGHT, env)].status = val;
}

void set_forks_with_lock(unsigned int philo_id, int val, t_env *env)
{
    const int idx_left = fork_id(philo_id, LEFT, env);
    const int idx_right = fork_id(philo_id, RIGHT, env);

    pthread_mutex_lock(&env->forks[idx_left].lock);
    pthread_mutex_lock(&env->forks[idx_right].lock);

    env->forks[idx_left].status = val;
    env->forks[idx_right].status = val;
    
    pthread_mutex_unlock(&env->forks[idx_right].lock);
    pthread_mutex_unlock(&env->forks[idx_left].lock);
}

void get_forks(unsigned int philo_id, t_env *env)
{
    const int idx_left = fork_id(philo_id, LEFT, env);
    const int idx_right = fork_id(philo_id, RIGHT, env);

    pthread_mutex_lock(&env->forks[idx_left].lock);
    if (env->forks[idx_left].status == FORK_FREE)
    {
        pthread_mutex_lock(&env->forks[idx_right].lock);
        if (env->forks[idx_right].status == FORK_FREE)
        {
            set_forks(philo_id, FORK_TAKEN, env);
            env->philos[philo_id].status = EATING;
        }
        pthread_mutex_unlock(&env->forks[idx_right].lock);
    }
    pthread_mutex_unlock(&env->forks[idx_left].lock);
}
