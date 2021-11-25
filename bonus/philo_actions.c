#include "philo.h"

_Bool init_philos(t_env *env)
{
    const size_t n = env->philos_number;
    size_t id;

    env->philos = malloc(env->philos_number * sizeof(t_philo));
    if (env->philos)
        while (env->nb_init_plocks < n)
        {
            id = env->nb_init_plocks;
            if (pthread_mutex_init(&env->philos[id].check_death_lock, NULL))
                return (false);
            env->philos[id].id = id;
            env->philos[id].right_fork = &env->forks[(id + n - !(id % 2)) % n];
            env->philos[id].left_fork = &env->forks[(id + n - (id % 2)) % n];
            env->philos[id].eat_counter = 0;
            env->philos[id].die_time = env->die_time;
            env->philos[id].eating_time = env->eating_time;
            env->philos[id].sleeping_time = env->sleeping_time;
            env->philos[id].status = LIVE;
            env->philos[id].simulation_terminated = &env->simulation_terminated;
            env->philos[id].expected_death_time = 0;
            env->nb_init_plocks++;
        }
    return (env->philos != NULL);
}

void destroy_philos(t_env *env)
{
    size_t i;

    if (env->philos)
    {
        i = 0;
        while (i < env->nb_init_plocks)
        {
            pthread_mutex_destroy(&env->philos[i].check_death_lock);
            i++;
        }
        free(env->philos);
    }
}

static inline _Bool eating(t_philo *philo)
{
    // add condition to stop trying to eat if is already eat should_eat_counter times.
    if (get_forks(philo))
    {
        pthread_mutex_lock(&philo->check_death_lock);
        if (philo->status == LIVE && !*philo->simulation_terminated)
        {
            philo->eat_counter++;
            philo->expected_death_time = get_timestamp() +  philo->die_time;
            pthread_mutex_unlock(&philo->check_death_lock);
            printf(EATING_MSG , get_timestamp(), philo->id);
            ft_sleep(philo->eating_time);
            drop_forks(philo);
            return(true);
        }
        pthread_mutex_unlock(&philo->check_death_lock);
        drop_forks(philo);
    }
    return (false);
}

void *routine(void *vphilo)
{
    const size_t id = ((t_philo*)vphilo)->id;
    t_philo *philo;

    philo = vphilo;
    philo->expected_death_time = get_timestamp() + philo->die_time;
    while (!*philo->simulation_terminated && eating(philo))
    {
        printf(SLEEPING_MSG, get_timestamp(), id);
        ft_sleep(philo->sleeping_time);
        printf(THINKING_MSG, get_timestamp(), id);
    }
    if (philo->status == DEAD)
        printf(DEAD_MSG, get_timestamp(), id);
    return (NULL);
}
