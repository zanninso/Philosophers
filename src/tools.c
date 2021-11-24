#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
