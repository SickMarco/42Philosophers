/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:04:22 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/26 19:57:54 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(t_dumb **d, char flag)
{

	pthread_mutex_lock((*d)->print);
	if (flag == 'T' && (*d)->stop == 0)
		printf("\033[0;32m%ld %d is thinking\n", get_time(d), (*d)->id);
	else if (flag == 'E' && (*d)->stop == 0)
		printf("\033[0;33m%ld %d is eating\n", get_time(d), (*d)->id);
	else if (flag == 'F' && (*d)->stop == 0)
		printf("\033[0;36m%ld %d has taken a fork\n",
			get_time(d), (*d)->id);
	else if (flag == 'S' && (*d)->stop == 0)
		printf("\033[0;35m%ld %d is sleeping\n", get_time(d), (*d)->id);
	pthread_mutex_unlock((*d)->print);
}

void	get_fork(t_dumb **d)
{
	if ((*d)->id % 2 == 0)
	{
		pthread_mutex_lock((*d)->left_f);
		pthread_mutex_lock((*d)->right_f);
		print_status(d, 'F');
		print_status(d, 'F');
		print_status(d, 'E');
		(*d)->last_m = get_time(d);
		usleep((*d)->tt_eat * 1000);
		pthread_mutex_unlock((*d)->right_f);
		pthread_mutex_unlock((*d)->left_f);
	}
	else
	{
		pthread_mutex_lock((*d)->right_f);
		pthread_mutex_lock((*d)->left_f);
		print_status(d, 'F');
		print_status(d, 'F');
		print_status(d, 'E');
		(*d)->last_m = get_time(d);
		usleep((*d)->tt_eat * 1000);
		pthread_mutex_unlock((*d)->left_f);
		pthread_mutex_unlock((*d)->right_f);
	}
}

long int	get_time2(t_dumb *d)
{
	struct timeval	t1;
	long int		ret;

	gettimeofday(&t1, NULL);
	ret = ((t1.tv_sec - d->time_start) * 1000
			+ (t1.tv_usec - d->time_ustart) / 1000);
	return (ret);
}

void	death(t_ph **ph)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(*ph)->det);
	while (1)
	{
		if ((*ph)->dumb[i].tt_die < (get_time2(&(*ph)->dumb[i]) - (*ph)->dumb[i].last_m))
		{
			printf("\033[0;31m%ld %d died\n", get_time2(&(*ph)->dumb[i]), (*ph)->dumb[i].id);
			i = -1;
			while (++i < (*ph)->nphilo)
				(*ph)->dumb[i].stop = 1;
			break ;
		}
		usleep(1000);
		i++;
		if (i == (*ph)->dumb[i].nphilo - 1)
			i = 0;
	}
	pthread_mutex_unlock(&(*ph)->det);
	return ;
}

void	sleeping(t_dumb **d)
{
	long int	i;
	long int	end;

	i = -1;

	print_status(d, 'S');
	end = get_time(d) + (*d)->tt_sleep;
	while (get_time(d) < end)
		usleep(1);
}
