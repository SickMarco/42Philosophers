/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:04:22 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/31 13:11:45 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	status(long int time, int id, pthread_mutex_t *print, char flag)
{
	static int	blk = 0;

	pthread_mutex_lock(print);
	if (flag == 'D' && blk == 0)
	{
		printf("\033[0;31m%ld %d died\n", time, id);
		blk = 1;
	}
	else if (flag == 'T' && blk == 0)
		printf("\033[0;32m%ld %d is thinking\n", time, id);
	else if (flag == 'E' && blk == 0)
		printf("\033[0;33m%ld %d is eating\n", time, (id));
	else if (flag == 'F' && blk == 0)
		printf("\033[0;36m%ld %d has taken a fork\n", time, id);
	else if (flag == 'S' && blk == 0)
		printf("\033[0;35m%ld %d is sleeping\n", time, id);
	pthread_mutex_unlock(print);
}

void	eating(t_dumb **d)
{
	long int	tmp;

	tmp = get_time((*d)->ts, (*d)->tu);
	status(tmp, (*d)->id, (*d)->print, 'E');
	pthread_mutex_lock((*d)->death);
	(*d)->last_arr[(*d)->id - 1] = tmp;
	pthread_mutex_unlock((*d)->death);
	go_to_sleep(d, (*d)->tt_eat);
}

void	get_fork(t_dumb **d)
{
	pthread_mutex_lock((*d)->left_f);
	status(get_time((*d)->ts, (*d)->tu), (*d)->id, (*d)->print, 'F');
	pthread_mutex_lock((*d)->right_f);
	status(get_time((*d)->ts, (*d)->tu), (*d)->id, (*d)->print, 'F');
	eating(d);
	pthread_mutex_unlock((*d)->right_f);
	pthread_mutex_unlock((*d)->left_f);
}

void	go_to_sleep(t_dumb **d, int type)
{
	long int	ftime;

	ftime = get_time((*d)->ts, (*d)->tu);
	while (get_time((*d)->ts, (*d)->tu) - ftime < (long)type)
		usleep(50);
}

void	death(t_ph **ph)
{
	int			i;
	long int	time;

	while (1)
	{
		i = -1;
		time = get_time((*ph)->tse, (*ph)->tu);
		pthread_mutex_lock(&(*ph)->death);
		if ((*ph)->status == 0)
			break ;
		while (++i < (*ph)->nphilo)
		{
			if ((*ph)->tt_die < (time - (*ph)->last[i]))
			{
				(*ph)->status = 0;
				status(time, (i + 1), &(*ph)->print, 'D');
				break ;
			}
		}
		pthread_mutex_unlock(&(*ph)->death);
		usleep(5000);
	}
	pthread_mutex_unlock(&(*ph)->death);
}
