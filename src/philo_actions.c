#include "philo.h"

void ft_sleep(size_t time)
{
    const size_t goal_time = get_timestamp() + time;

    while (goal_time > get_timestamp())
        usleep(10);
}

size_t get_timestamp() 
{
    static size_t start_time;
    t_time  now;

    gettimeofday(&now, NULL);
    if (start_time == 0)
        start_time = (((long long)now.tv_sec)*1000) + (now.tv_usec/1000);
    return ((((long long)now.tv_sec)*1000) + (now.tv_usec/1000) - start_time);
}

void init_philo(size_t id, t_env *env)
{
    const int n = env->philos_number;

    env->philos[id].id = id;
    env->philos[id].right_fork = &env->forks[(id + n - !(id % 2)) % n];
    env->philos[id].left_fork = &env->forks[(id + n - (id % 2)) % n];
    env->philos[id].eat_counter = 0;
    env->philos[id].die_time = env->die_time;
    env->philos[id].eating_time = env->eating_time;
    env->philos[id].sleeping_time = env->sleeping_time;
    env->philos[id].status = LIVE;
    env->philos[id].simulation_terminated = &env->simulation_terminated;
    pthread_mutex_init(&env->philos[id].check_death_lock, NULL);
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
        drop_forks(philo);
        pthread_mutex_unlock(&philo->check_death_lock);
    }
    return (false);
}

void *born_philo(void *vphilo)
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
    if (philo->status == DIED)
        printf(DIED_MSG, get_timestamp(), id);
    return (NULL);
}
