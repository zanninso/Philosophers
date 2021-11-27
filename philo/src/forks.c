/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:43:38 by aait-ihi          #+#    #+#             */
/*   Updated: 2021/11/26 15:01:18 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

_Bool	init_forks(t_env *env)
{
	size_t	i;

	env->forks = malloc(env->philos_number * sizeof(t_fork));
	if (env->forks)
	{
		while (env->nb_init_flocks < env->philos_number)
		{
			i = (env->nb_init_flocks + env->nb_init_flocks % 2);
			env->forks[env->nb_init_flocks].last_user = i % env->philos_number;
			if (pthread_mutex_init(&env->forks[env->nb_init_flocks].lock, NULL))
				return (false);
			env->nb_init_flocks++;
		}
		return (true);
	}
	return (false);
}

void	destroy_forks(t_env *env)
{
	size_t	i;

	if (env->forks)
	{
		i = 0;
		while (i < env->nb_init_flocks)
		{
			pthread_mutex_destroy(&env->forks[i].lock);
			i++;
		}
		free(env->forks);
	}
}

_Bool	get_forks(t_philo *philo)
{
	_Bool	can_take_forks;

	while (true)
	{
		can_take_forks = philo->right_fork->last_user != philo->id;
		can_take_forks &= philo->left_fork->last_user != philo->id;
		if ((philo->status == DEAD || *philo->simulation_terminated))
			return (false);
		if (can_take_forks)
		{
			pthread_mutex_lock(&philo->right_fork->lock);
			printf(FORK_TAKEN_MSG, get_timestamp(), philo->id);
			pthread_mutex_lock(&philo->left_fork->lock);
			printf(FORK_TAKEN_MSG, get_timestamp(), philo->id);
			break ;
		}
	}
	return (true);
}

void	drop_forks(t_philo *philo)
{
	philo->right_fork->last_user = philo->id;
	philo->left_fork->last_user = philo->id;
	pthread_mutex_unlock(&philo->left_fork->lock);
	pthread_mutex_unlock(&philo->right_fork->lock);
	printf(FORK_FREED_MSG, get_timestamp(), philo->id);
	printf(FORK_FREED_MSG, get_timestamp(), philo->id);
}
