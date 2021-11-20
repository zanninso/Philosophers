#include "philo.h"

size_t get_timestamp() 
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

static void philo_says(unsigned int id, const char *msg, t_env *env)
{
    pthread_mutex_lock(&env->printer_lock);
    printf(msg, id);
    pthread_mutex_unlock(&env->printer_lock);
}

_Bool eating(unsigned int id, t_env *env)
{
    const size_t start_time = get_timestamp();
    // add condition to stop trying to eat if is already eat should_eat_counter times.
    get_forks(id, env);
    while (env->philos[id].status == WAITING_FORKS)
    {
        if (env->is_end || (get_timestamp() - start_time) >= env->die_time)
            return (false);
        get_forks(id, env);
    }
    philo_says(id ,"philo %d: am eating\n", env);
    env->philos[id].eat_counter++;
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
    philo_says(id, "philo %d born\n", env);
    while (!env->is_end && eating(id, env))
    {
        philo_says(id ,"philo %d: am sleeping\n", env);
        usleep(env->sleeping_time);
        philo_says(id ,"philo %d: am thinking\n", env);
    }
    env->is_end = true;
    philo_says(id, "%d am die stop working guys\n", env);
    return (NULL);
}