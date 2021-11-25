#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "philo.h"

ft_print(int action, const char *msg, size_t time, size_t id)
{
    static sem_t *lock;

    if (action == PRINTER_PRINT)
    {
        sem_wait(lock);
        printf(msg, time, id);
        sem_post(lock);
    }
    else if (action == PRINTER_INIT)
        lock = sem_open("printer_lock", O_CREAT, S_IRUSR | S_IWUSR , 1);
    else
        sem_close(lock);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

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
	if (((*s == '-' || *s == '+') && ft_isdigit(s[1])))
		m *= (*s++ == '-' ? -1 : 1);
	while (i++ < 19 && ft_isdigit(*s))
		n = (n * 10) + (*s++ - '0');
	return (n * m);
}

void *ft_memcpy(void *vdest, void *vsrc, size_t size)
{
    unsigned char *dest;
    unsigned char *src;
    size_t i;

    i = 0;
    dest = vdest;
    src = vsrc;
    if (dest && src)
        while (i < size)
        {
            dest[i] = src[i];
            i++;    
        }
    return(dest);
}

void ft_sleep(size_t time)
{
    const size_t goal_time = get_timestamp() + time;

    while (goal_time > get_timestamp())
        usleep(100);
}

size_t get_timestamp() 
{
    static size_t start_time;
    t_time  now;

    gettimeofday(&now, NULL);
    if (start_time == 0)
        start_time = (((long long)now.tv_sec)*1000) + (now.tv_usec/1000);
    return ((((long long)now.tv_sec)*1000) + (now.tv_usec/1000) - start_time);
}