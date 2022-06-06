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
	env->forks = malloc(env->philos_number * sizeof(t_fork));
	if (env->forks)
	{
		while (env->nb_init_flocks < env->philos_number)
		{
			env->forks[env->nb_init_flocks].status = 1;
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
	while (true)
	{
		if ((philo->status == DEAD || *philo->simulation_terminated))
			return (false);
		{
			pthread_mutex_lock(&philo->right_fork->lock);
			pthread_mutex_lock(&philo->left_fork->lock);
			if (philo->left_fork->status == 0)
			{
				pthread_mutex_unlock(&philo->right_fork->lock);
				pthread_mutex_unlock(&philo->left_fork->lock);
				continue;
			}
			philo->right_fork->status = 0;
			philo->left_fork->status = 0;
			pthread_mutex_unlock(&philo->left_fork->lock);
			printf(FORK_TAKEN_MSG, get_timestamp(), philo->id);
			printf(FORK_TAKEN_MSG, get_timestamp(), philo->id);
			break ;
		}
	}
	return (true);
}

void	drop_forks(t_philo *philo)
{
	philo->right_fork->status = 1;
	philo->left_fork->status = 1;
	pthread_mutex_unlock(&philo->right_fork->lock);
	printf(FORK_FREED_MSG, get_timestamp(), philo->id);
	printf(FORK_FREED_MSG, get_timestamp(), philo->id);
}
