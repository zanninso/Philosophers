#include "philo.h"

_Bool get_args(int ac, char **av, t_env *env)
{
    if (ac < 5)
        return (false);
    env->philos_number = ft_atoi(av[1]);
    env->die_time = ft_atoi(av[2]);
    env->eating_time = ft_atoi(av[3]);
    env->sleeping_time = ft_atoi(av[4]);
    if (ac > 5)
        env->nb_meals = ft_atoi(av[5]);
    return true;
}

void watch_death(t_env *env)
{
    size_t i;

    while (true)
    {
        i = 0;
        while (i < env->philos_number)
        {
            pthread_mutex_lock(&env->philos[i].check_death_lock);
            if (get_timestamp() > env->philos[i].expected_death_time)
            {
                env->philos[i].status = DEAD;
                env->simulation_terminated = true;
                pthread_mutex_unlock(&env->philos[i].check_death_lock);
                return;
            }
            pthread_mutex_unlock(&env->philos[i].check_death_lock);
            i++;
        }
    }
}

void kill_process(t_env *env, pid_t *pids)
{
    while (env->id)
    {
        env->id--;
        kill(pids[env->id], SIGKILL);
    }
}

_Bool lunch_process(t_env *env, pid_t *pids)
{
    while (env->id < env->philos_number)
    {
        env->id++;
        pids[env->id - 1] = fork();
        if (pids[env->id - 1] == 0)
            routine(env);
        if (pids[env->id - 1] == -1)
        {
            kill_process(env, pids);
            return (false);
        }
    }
    return (true);
}

void wait_process(t_env *env, pid_t *pids)
{
    size_t i;
    int status;
    _Bool waiting;

    waiting = true;
    while (waiting)
    {
        i = 0;
        waiting = false;
        while (i < env->philos_number)
        {
            if (pids[i]) 
            {
                waiting = true;
                waitpid(pids[i], &status, WNOHANG);
                if (WIFEXITED(status) && WEXITSTATUS(status))
                    return (kill_process(env, pids));
                else if (WIFEXITED(status))
                    pids[i] = 0;
            }
        }
    }
}

int main(int ac, char **av)
{
    t_env env;
    pid_t pids[200];

    memset(&env, 0, sizeof(t_env));
    if (get_args(ac, av, &env))
    {
        if (init_forks(&env) && lunch_process(&env, pids))
        {
            wait_process(&env, pids);
        }
    }
    destroy_forks(&env);
}