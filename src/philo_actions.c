/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:46:16 by aait-ihi          #+#    #+#             */
/*   Updated: 2021/11/25 23:47:15 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

_Bool	init_philos(t_env *env, size_t n, size_t id)
{
	if (!pthread_mutex_init(&env->left_meals_lock, NULL))
		env->philos = malloc(env->philos_number * sizeof(t_philo));
	if (env->philos)
	{
		memset(env->philos, 0, sizeof(t_philo));
		while (env->nb_init_plocks < n)
		{
			id = env->nb_init_plocks;
			if (pthread_mutex_init(&env->philos[id].check_death_lock, NULL))
				return (false);
			env->philos[id].id = id;
			env->philos[id].right_fork = &env->forks[(id + n - !(id % 2)) % n];
			env->philos[id].left_fork = &env->forks[(id + n - (id % 2)) % n];
			env->philos[id].left_meals = &env->nb_meals;
			env->philos[id].left_meals_lock = &env->left_meals_lock;
			env->philos[id].die_time = env->die_time;
			env->philos[id].eating_time = env->eating_time;
			env->philos[id].sleeping_time = env->sleeping_time;
			env->philos[id].nb_meals = env->nb_meals / env->philos_number;
			env->philos[id].simulation_terminated = &env->simulation_terminated;
			env->nb_init_plocks++;
		}
	}
	return (env->philos != NULL);
}

void	destroy_philos(t_env *env)
{
	size_t	i;

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
	pthread_mutex_destroy(&env->left_meals_lock);
}

static inline _Bool	eating(t_philo *philo)
{
	if (get_forks(philo))
	{
		pthread_mutex_lock(&philo->check_death_lock);
		if (philo->status == LIVE && !*philo->simulation_terminated)
		{
			philo->eat_counter++;
			philo->expected_death_time = get_timestamp() + philo->die_time;
			pthread_mutex_unlock(&philo->check_death_lock);
			printf(EATING_MSG, get_timestamp(), philo->id);
			ft_sleep(philo->eating_time);
			drop_forks(philo);
			return (true);
		}
		pthread_mutex_unlock(&philo->check_death_lock);
		drop_forks(philo);
	}
	return (false);
}

void wait_others_end(t_philo *philo)
{
	pthread_mutex_lock(philo->left_meals_lock);
	*philo->left_meals = *philo->left_meals - 1;
	pthread_mutex_unlock(philo->left_meals_lock);	
	while (!*philo->simulation_terminated && *philo->left_meals)
	{
		pthread_mutex_lock(&philo->check_death_lock);
		philo->expected_death_time = get_timestamp() + 10;
		ft_sleep(1);
		pthread_mutex_unlock(&philo->check_death_lock);	
	}
	philo->expected_death_time = get_timestamp() - 1;
}

void	*routine(void *vphilo)
{
	const size_t	id = ((t_philo*)vphilo)->id;
	t_philo			*philo;

	philo = vphilo;
	philo->expected_death_time = get_timestamp() + philo->die_time;
	while (!*philo->simulation_terminated && eating(philo))
	{
		printf(SLEEPING_MSG, get_timestamp(), id);
		ft_sleep(philo->sleeping_time);
		if (philo->nb_meals == philo->eat_counter)
		{
			wait_others_end(philo);
			return (NULL) ;
		}
		printf(THINKING_MSG, get_timestamp(), id);
	}
	if (philo->status == DEAD)
		printf(DEAD_MSG, get_timestamp(), id);
	return (NULL);
}
