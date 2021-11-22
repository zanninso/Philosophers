#include "philo.h"

void set_fork_ids(unsigned int philo_id, t_env *env)
{
    unsigned int tmp = philo_id + env->philos_number;
    env->philos[philo_id].right_fork = (tmp + 1) % env->philos_number;
    env->philos[philo_id].left_fork = (tmp - 1) % env->philos_number;
}

inline void set_forks(unsigned int philo_id, int val, t_env *env)
{
    env->forks[env->philos[philo_id].left_fork].status = val;
    env->forks[env->philos[philo_id].right_fork].status = val;
}

inline void set_forks_with_lock(unsigned int philo_id, int val, t_env *env)
{
    const int idx_left = env->philos[philo_id].left_fork;
    const int idx_right = env->philos[philo_id].right_fork;

    pthread_mutex_lock(&env->forks[idx_left].lock);
    env->forks[idx_left].status = val;
    philo_says(idx_left , philo_id, FORK_FRIED_MSG, env);
    pthread_mutex_unlock(&env->forks[idx_left].lock);

    pthread_mutex_lock(&env->forks[idx_right].lock);
    env->forks[idx_right].status = val;
    philo_says(idx_right , philo_id, FORK_FRIED_MSG, env);
    pthread_mutex_unlock(&env->forks[idx_right].lock);
    
}

/*inline void get_forks(unsigned int philo_id, t_env *env)
{
    const int idx_left = env->philos[philo_id].left_fork;
    const int idx_right = env->philos[philo_id].right_fork;

    pthread_mutex_lock(&env->forks[idx_left].lock);
    philo_says(idx_left , philo_id, FORK_TAKEN_MSG, env);
    if (env->forks[idx_left].status == FORK_FREE)
    {
        pthread_mutex_lock(&env->forks[idx_right].lock);
        philo_says(idx_right , philo_id, FORK_TAKEN_MSG, env);
        if (env->forks[idx_right].status == FORK_FREE)
        {
            set_forks(philo_id, FORK_TAKEN, env);
            env->philos[philo_id].status = EATING;
        }
        else
            philo_says(idx_right , philo_id, FORK_FRIED_MSG, env);
        pthread_mutex_unlock(&env->forks[idx_right].lock);
    }
    if(env->philos[philo_id].status != EATING)
        philo_says(idx_left , philo_id, FORK_FRIED_MSG, env);
    pthread_mutex_unlock(&env->forks[idx_left].lock);
}*/


inline void get_forks(unsigned int philo_id, t_env *env)
{
    const int idx_left = env->philos[philo_id].left_fork;
    const int idx_right = env->philos[philo_id].right_fork;
    int     taken_forks_number;

    taken_forks_number = 0;
    pthread_mutex_lock(&env->forks[idx_left].lock);
    if (env->forks[idx_left].status == FORK_FREE)
    {
        env->forks[idx_left].status = FORK_TAKEN;
        taken_forks_number++;
        philo_says(idx_left , philo_id, FORK_TAKEN_MSG, env);
    }
    pthread_mutex_unlock(&env->forks[idx_left].lock);
    
    if (taken_forks_number) 
    {
        pthread_mutex_lock(&env->forks[idx_right].lock);
        if (env->forks[idx_right].status == FORK_FREE)
        {
            env->forks[idx_right].status = FORK_TAKEN;
            taken_forks_number++;
            philo_says(idx_right , philo_id, FORK_TAKEN_MSG, env);
        }
        pthread_mutex_unlock(&env->forks[idx_right].lock);
    }
    if(taken_forks_number == 2)
        env->philos[philo_id].status = EATING;
    else if(taken_forks_number)
    {
        env->forks[idx_left].status = FORK_FREE;
        philo_says(idx_left , philo_id, FORK_FRIED_MSG, env);
    }
}