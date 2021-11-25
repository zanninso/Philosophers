/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:15:24 by aait-ihi          #+#    #+#             */
/*   Updated: 2021/11/25 23:16:57 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_philo *philo)
{
	const size_t	n = philo->philos_number;

	sem_unlink(SEM_FORKS);
	philo->forks = sem_open(SEM_FORKS, O_CREAT, LOCK_PERM, n);
	sem_unlink(SEM_FORKS_QUEUE);
	philo->forks_queue = sem_open(SEM_FORKS_QUEUE, O_CREAT, LOCK_PERM, n / 2);
	sem_unlink(SEM_KILL_PHILOS);
	philo->kill_philos = sem_open(SEM_KILL_PHILOS, O_CREAT, LOCK_PERM, 0);
}

void	destroy_forks(t_philo *philo)
{
	sem_unlink(SEM_FORKS);
	sem_close(philo->forks);
	sem_unlink(SEM_FORKS_QUEUE);
	sem_close(philo->forks_queue);
	sem_unlink(SEM_KILL_PHILOS);
	sem_close(philo->kill_philos);
}

void	get_forks(t_philo *philo)
{
	sem_wait(philo->forks_queue);
	sem_wait(philo->forks);
	ft_print(PRINTER_PRINT, FORK_TAKEN_MSG, get_timestamp(), philo->id);
	sem_wait(philo->forks);
	ft_print(PRINTER_PRINT, FORK_TAKEN_MSG, get_timestamp(), philo->id);
	sem_post(philo->forks_queue);
}

void	drop_forks(t_philo *philo)
{
	ft_print(PRINTER_PRINT, FORK_FREED_MSG, get_timestamp(), philo->id);
	ft_print(PRINTER_PRINT, FORK_FREED_MSG, get_timestamp(), philo->id);
	sem_post(philo->forks);
	sem_post(philo->forks);
}
