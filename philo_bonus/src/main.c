/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:12:48 by aait-ihi          #+#    #+#             */
/*   Updated: 2021/11/25 23:14:44 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

_Bool	get_args(int ac, char **av, t_philo *philo)
{
	if (ac < 5)
		return (false);
	philo->philos_number = ft_atoi(av[1]);
	philo->die_time = ft_atoi(av[2]);
	philo->eating_time = ft_atoi(av[3]);
	philo->sleeping_time = ft_atoi(av[4]);
	if (ac > 5)
		philo->nb_meals = ft_atoi(av[5]);
	if (!philo->philos_number || philo->philos_number > 200 || !philo->die_time)
	{
		printf(ERROR_INVALID_ARG);
		return (false);
	}
	return (true);
}

void	kill_process(t_philo *philo, pid_t *pids)
{
	while (philo->id)
	{
		philo->id--;
		kill(pids[philo->id], SIGKILL);
	}
}

_Bool	lunch_process(t_philo *philo, pid_t *pids)
{
	while (philo->id < philo->philos_number)
	{
		philo->id++;
		pids[philo->id - 1] = fork();
		if (pids[philo->id - 1] == 0)
			routine(philo);
		if (pids[philo->id - 1] == -1)
		{
			kill_process(philo, pids);
			return (false);
		}
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_philo	philo;
	pid_t	pids[200];

	memset(&philo, 0, sizeof(t_philo));
	errno = 0;
	if (get_args(ac, av, &philo))
	{
		ft_print(PRINTER_UNLINK, "", 0, 0);
		ft_print(PRINTER_INIT, "", 0, 0);
		init_forks(&philo);
		if (lunch_process(&philo, pids))
		{
			sem_wait(philo.kill_philos);
			kill_process(&philo, pids);
		}
		ft_print(PRINTER_UNLINK, "", 0, 0);
		ft_print(PRINTER_DESTROY, "", 0, 0);
		destroy_forks(&philo);
	}
}
