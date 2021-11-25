/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:50:32 by aait-ihi          #+#    #+#             */
/*   Updated: 2021/11/25 23:53:27 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

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

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				status;
	size_t			last_user;
}				t_fork;

typedef struct s_philo
{
	size_t			*left_meals;
	t_fork			*left_fork;
	t_fork			*right_fork;
	_Bool			*simulation_terminated;
	pthread_mutex_t	check_death_lock;
	size_t			id;
	size_t			eat_counter;
	size_t			expected_death_time;
	size_t			sleeping_time;
	size_t			eating_time;
	size_t			die_time;
	size_t			nb_meals;
	int				status;
}				t_philo;

typedef struct s_env
{
	t_philo		*philos;
	t_fork		*forks;
	pthread_t	*thread_ids;
	size_t		philos_number;
	size_t		should_eat_counter;
	size_t		sleeping_time;
	size_t		thinking_time;
	size_t		eating_time;
	size_t		die_time;
	size_t		nb_init_flocks;
	size_t		nb_init_plocks;
	size_t		nb_init_threads;
	size_t		nb_meals;
	size_t		*left_meals;
	_Bool		simulation_terminated;
}				t_env;

enum
{
	LIVE,
	DEAD
};

enum
{
	RIGHT,
	LEFT,
};

enum
{
	false,
	true
};

enum
{
	FORK_TAKEN,
	FORK_FREE
};

_Bool		init_forks(t_env *env);
void		destroy_forks(t_env *env);
void		set_fork_ids(size_t philo_id, t_env *env);
_Bool		get_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

void		*ft_memcpy(void *vdest, void *vsrc, size_t size);
long long	ft_atoi(const char *s);

_Bool		init_philos(t_env *env);
void		destroy_philos(t_env *env);
void		*routine(void *venv);

size_t		get_timestamp(void);
void		ft_sleep(size_t time);

#endif
