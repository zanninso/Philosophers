#include "philo.h"

inline size_t get_timestamp() 
{
    t_time  now;
    gettimeofday(&now, NULL);
    return (((long long)now.tv_sec)*1000)+(now.tv_usec/1000);
}

unsigned int get_id(t_env *env)
{
    unsigned int id;
    pthread_mutex_lock(&env->born_lock);
    id = env->current_id++;
    pthread_mutex_unlock(&env->born_lock);
    return (id);
}

void philo_says(unsigned int id, size_t time, const char *msg, t_env *env)
{
    pthread_mutex_lock(&env->printer_lock);
    printf(msg, time, id);
    pthread_mutex_unlock(&env->printer_lock);
}

static inline _Bool eating(unsigned int id, t_env *env)
{
    env->philos[id].status = WAITING_FORKS;
    // add condition to stop trying to eat if is already eat should_eat_counter times.
    while (true)
    {
        if (env->is_end || (get_timestamp() - env->philos[id].time_start_eating) > env->die_time)
            return (false);
        get_forks(id, env);
        if (env->philos[id].status != WAITING_FORKS)
            break;
        // usleep(1000);
    }
    philo_says(id , get_timestamp(), EATING_MSG, env);
    env->philos[id].eat_counter++;
    env->philos[id].time_start_eating = get_timestamp();
    usleep(env->eating_time);
    set_forks_with_lock(id, FORK_FREE, env);
    return (true);
}


void *born_philo(void *venv)
{
    unsigned int id;
    t_env *env;

    env = venv;
    id = get_id(env);
    philo_says(id, get_timestamp(), BORN_MSG, env);
    env->philos[id].time_start_eating = get_timestamp();
    while (eating(id, env))
    {
        philo_says(id ,get_timestamp(), SLEEPING_MSG, env);
        usleep(env->sleeping_time);
        philo_says(id ,get_timestamp(), THINKING_MSG, env);
    }
    env->is_end = true;
    philo_says(id, get_timestamp(), DIED_MSG, env);
    return (NULL);
}
