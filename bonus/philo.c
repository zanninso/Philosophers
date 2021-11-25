/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:15:13 by aait-ihi          #+#    #+#             */
/*   Updated: 2021/11/25 23:19:00 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	exit_routine(int status, const char *msg,
	size_t time, t_philo *philo)
{
	ft_print(PRINTER_PRINT, msg, time, philo->id);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_FORKS_QUEUE);
	sem_unlink(SEM_KILL_PHILOS);
	sem_unlink(SEM_CHECK_DEATH);
	ft_print(PRINTER_UNLINK, "", (size_t)0, (size_t)0);
	sem_post(philo->kill_philos);
	sem_close(philo->check_death_lock);
	exit(status);
}

static void	*watch_death(void *vphilo)
{
	t_philo	*philo;

	philo = vphilo;
	while (true)
	{
		usleep(100);
		sem_wait(philo->check_death_lock);
		if (get_timestamp() > philo->expected_death_time)
			exit_routine(DEAD, DEAD_MSG, get_timestamp(), philo);
		sem_post(philo->check_death_lock);
	}
	return (NULL);
}

static inline void	eating(t_philo *philo)
{
	size_t	current_time;

	get_forks(philo);
	sem_wait(philo->check_death_lock);
	philo->eat_counter++;
	current_time = get_timestamp();
	philo->expected_death_time = current_time + philo->die_time;
	sem_post(philo->check_death_lock);
	ft_print(PRINTER_PRINT, EATING_MSG, current_time, philo->id);
	ft_sleep(philo->eating_time);
	drop_forks(philo);
}

void	routine(t_philo *philo)
{
	const size_t	id = philo->id;
	pthread_t		tid;

	sem_unlink(SEM_CHECK_DEATH);
	philo->check_death_lock = sem_open(SEM_CHECK_DEATH, O_CREAT, LOCK_PERM, 1);
	if (pthread_create(&tid, NULL, watch_death, philo))
		exit_routine(DEAD, ERROR_THREAD_CREATION, 0, philo);
	pthread_detach(tid);
	philo->expected_death_time = get_timestamp() + philo->die_time;
	while (true)
	{
		eating(philo);
		ft_print(PRINTER_PRINT, SLEEPING_MSG, get_timestamp(), id);
		ft_sleep(philo->sleeping_time);
		if (philo->eat_counter == philo->nb_meals)
			exit_routine(LIVE, "", 0, philo);
		ft_print(PRINTER_PRINT, THINKING_MSG, get_timestamp(), id);
	}
}
