/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:19:14 by aait-ihi          #+#    #+#             */
/*   Updated: 2021/11/25 23:34:27 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>           /* For O_* constants */
# include <sys/stat.h>        /* For mode constants */
# include <semaphore.h>
# include <sys/errno.h>

# define SEM_FORKS "forks"
# define SEM_FORKS_QUEUE "forks_queue"
# define SEM_KILL_PHILOS "kill_philos"
# define SEM_CHECK_DEATH "check_death"
# define SEM_PRINTER "printer"

# define LOCK_PERM 0777

# define ERROR_THREAD_CREATION "error accure during thread creation\n"
# define ERROR_INVALID_ARG "invalide arguments given!\n"

# define TRY_TAKE_FORK_MSG "%15lu %lu is trying to take a fork\n"
# define FORK_TAKEN_MSG "%15lu %lu has taken a fork\n"
# define FORK_FREED_MSG "%15lu %lu has freed a fork\n"
# define EATING_MSG "%15lu %lu is eating\n"
# define SLEEPING_MSG "%15lu %lu is sleeping\n"
# define THINKING_MSG "%15lu %lu is thinking\n"
# define DEAD_MSG "%15lu %lu DEAD\n"

typedef struct timeval	t_time;

typedef struct s_philo
{
	sem_t		*forks;
	sem_t		*forks_queue;
	sem_t		*kill_philos;
	sem_t		*check_death_lock;
	char		cdl_name[25];
	size_t		id;
	size_t		eat_counter;
	size_t		nb_meals;
	size_t		philos_number;
	size_t		sleeping_time;
	size_t		eating_time;
	size_t		die_time;
	size_t		expected_death_time;
	_Bool		status;
}				t_philo;

enum
{
	LIVE,
	DEAD
};

enum
{
	false,
	true
};

enum
{
	PRINTER_INIT,
	PRINTER_DESTROY,
	PRINTER_PRINT,
	PRINTER_UNLINK
};

enum
{
	FORK_TAKEN,
	FORK_FREE
};

void		init_forks(t_philo *philo);
void		destroy_forks(t_philo *philo);
void		get_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

void		routine(t_philo *philo);

void		*ft_memcpy(void *vdest, void *vsrc, size_t size);
long long	ft_atoi(const char *s);
size_t		get_timestamp(void);
void		ft_sleep(size_t time);
void		ft_print(int action, const char *msg, size_t time, size_t id);

#endif
