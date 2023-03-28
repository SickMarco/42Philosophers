/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:04:22 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/28 15:57:14 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(t_dumb **d, char flag)
{
	pthread_mutex_lock((*d)->death);
	pthread_mutex_lock((*d)->print);
	if (*(*d)->status == 0)
	{
		pthread_mutex_unlock((*d)->print);
		pthread_mutex_unlock((*d)->death);
		return ;
	}
	pthread_mutex_unlock((*d)->death);
	if (flag == 'T')
		printf("\033[0;32m%ld %d is thinking\n", get_time((*d)->time_s,
				(*d)->time_u), (*d)->id);
	else if (flag == 'E')
		printf("\033[0;33m%ld %d is eating\n", get_time((*d)->time_s,
				(*d)->time_u), (*d)->id);
	else if (flag == 'F')
		printf("\033[0;36m%ld %d has taken a fork\n", get_time((*d)->time_s,
				(*d)->time_u), (*d)->id);
	else if (flag == 'S')
		printf("\033[0;35m%ld %d is sleeping\n", get_time((*d)->time_s,
				(*d)->time_u), (*d)->id);
	pthread_mutex_unlock((*d)->print);
}

void	eating(t_dumb **d)
{
	print_status(d, 'E');
	pthread_mutex_lock((*d)->death);
	(*d)->last_arr[(*d)->id - 1] = get_time((*d)->time_s,
			(*d)->time_u);
	pthread_mutex_unlock((*d)->death);
	usleep((*d)->tt_eat * 1000);
}

void	get_fork(t_dumb **d)
{
	if ((*d)->id == (*d)->nphilo)
	{
		pthread_mutex_lock((*d)->right_f);
		print_status(d, 'F');
		pthread_mutex_lock((*d)->left_f);
		print_status(d, 'F');
		eating(d);
		pthread_mutex_unlock((*d)->left_f);
		pthread_mutex_unlock((*d)->right_f);
	}
	else
	{
		pthread_mutex_lock((*d)->left_f);
		print_status(d, 'F');
		pthread_mutex_lock((*d)->right_f);
		print_status(d, 'F');
		eating(d);
		pthread_mutex_unlock((*d)->left_f);
		pthread_mutex_unlock((*d)->right_f);
	}
}

int	alive(t_dumb **d)
{
	if ((*d)->meals != 0)
	{
		if (++(*d)->e_meals == (*d)->meals)
		{
			pthread_mutex_lock((*d)->death);
			*((*d)->status) = 0;
			pthread_mutex_unlock((*d)->death);
			return (0);
		}
	}
	return (1);
}

void	death(t_ph **ph)
{
	int	i;

	i = -1;
	while (1)
	{
		if (++i == (*ph)->nphilo)
			i = 0;
		pthread_mutex_lock(&(*ph)->death);
		if (!(*ph)->status)
			break ;
		if ((long)(*ph)->tt_die < (get_time((*ph)->time_s,
					(*ph)->time_u) - (*ph)->last[i]))
		{
			(*ph)->status = 0;
			pthread_mutex_lock(&(*ph)->print);
			printf("\033[0;31m%ld %d died\n", get_time((*ph)->time_s,
					(*ph)->time_u), (i + 1));
			pthread_mutex_unlock(&(*ph)->print);
			break ;
		}
		pthread_mutex_unlock(&(*ph)->death);
		usleep(1000);
	}
	pthread_mutex_unlock(&(*ph)->death);
}
