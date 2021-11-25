/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:24:47 by aait-ihi          #+#    #+#             */
/*   Updated: 2021/11/25 23:35:34 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *s)
{
	long long	n;
	int			m;
	int			i;

	if (!s)
		return (0);
	n = 0;
	i = 0;
	m = 1;
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if ((*s == '-' || *s == '+') && (s[1] >= '0' && s[1] <= '9'))
		if (*s++ == '-' )
			m = -1;
	while (i++ < 19 && ft_isdigit(*s))
		n = (n * 10) + (*s++ - '0');
	return (n * m);
}

void	*ft_memcpy(void *vdest, void *vsrc, size_t size)
{
	unsigned char	*dest;
	unsigned char	*src;
	size_t			i;

	i = 0;
	dest = vdest;
	src = vsrc;
	if (dest && src)
	{
		while (i < size)
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (dest);
}

void	ft_sleep(size_t time)
{
	const size_t	goal_time = get_timestamp() + time;

	while (goal_time > get_timestamp())
		usleep(10);
}

size_t	get_timestamp(void)
{
	static size_t	start_time;
	t_time			now;

	gettimeofday(&now, NULL);
	if (start_time == 0)
		start_time = (((long)now.tv_sec) * 1000) + (now.tv_usec / 1000);
	return ((((long)now.tv_sec) * 1000) + (now.tv_usec / 1000) - start_time);
}
