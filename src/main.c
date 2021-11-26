/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:41:06 by aait-ihi          #+#    #+#             */
/*   Updated: 2021/11/25 23:41:43 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

_Bool	get_args(int ac, char **av, t_env *env)
{
	if (ac < 5)
		return (false);
	env->philos_number = ft_atoi(av[1]);
	env->die_time = ft_atoi(av[2]);
	env->eating_time = ft_atoi(av[3]);
	env->sleeping_time = ft_atoi(av[4]);
	if (ac > 5)
		env->nb_meals = ft_atoi(av[5]) * env->philos_number;
	if (!env->philos_number || env->philos_number > 200 || !env->die_time)
	{
		printf(ERROR_INVALID_ARG);
		return (false);
	}
	return (true);
}

void	watch_death(t_env *env)
{
	size_t	i;

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
				return ;
			}
			pthread_mutex_unlock(&env->philos[i].check_death_lock);
			i++;
		}
	}
}

void	create_threads(t_env *env)
{
	size_t	i;

	while (env->nb_init_threads < env->philos_number)
	{
		i = env->nb_init_threads;
		if (pthread_create(&env->thread_ids[i], NULL, routine, &env->philos[i]))
		{
			env->simulation_terminated = true;
			break ;
		}
		env->nb_init_threads++;
	}
	if (env->nb_init_threads == env->philos_number)
		watch_death(env);
	i = 0;
	while (i < env->nb_init_threads)
	{
		pthread_join(env->thread_ids[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_env	env;

	memset(&env, 0, sizeof(t_env));
	if (get_args(ac, av, &env))
	{
		env.thread_ids = malloc(env.philos_number * sizeof(pthread_t));
		if (env.thread_ids && init_forks(&env) && init_philos(&env, env.philos_number, 0))
		{
			create_threads(&env);
		}
	}
	free(env.thread_ids);
	destroy_forks(&env);
	destroy_philos(&env);
}
