/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:12:55 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/30 18:05:17 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_input(char **av)
{
	int	tmp;
	int	i;

	i = 0;
	while (av[++i])
	{
		tmp = ft_atoi(av[i]);
		if (tmp <= 0)
			return (printf("\033[0;31mInvalid input\n"));
	}
	return (0);
}

void	free_for_all(t_ph **ph)
{
	free((*ph)->dumb);
	free((*ph)->th);
	free((*ph)->forks);
	free((*ph)->last);
	free(*ph);
}

long int	get_time(time_t start, suseconds_t ustart)
{
	struct timeval	t1;
	long int		ret;

	gettimeofday(&t1, NULL);
	ret = ((t1.tv_sec - start) * 1000
			+ (t1.tv_usec - ustart) / 1000);
	return (ret);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	char	*str;
	size_t	i;

	i = -1;
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	str = (char *)ptr;
	while (++i < (nmemb * size))
		str[i] = '\0';
	return (ptr);
}
