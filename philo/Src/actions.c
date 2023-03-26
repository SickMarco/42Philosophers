/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:04:22 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/26 22:42:09 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(t_dumb **d, char flag)
{
	static int	blk = 0;

	pthread_mutex_lock((*d)->print);
	if (flag == 'D' && blk == 0)
	{
		printf("\033[0;31m%ld %d died\n", get_time(d), (*d)->id);
		blk = 1;
	}
	if (flag == 'T' && blk == 0)
		printf("\033[0;32m%ld %d is thinking\n", get_time(d), (*d)->id);
	else if (flag == 'E' && blk == 0)
		printf("\033[0;33m%ld %d is eating\n", get_time(d), (*d)->id);
	else if (flag == 'F' && blk == 0)
		printf("\033[0;36m%ld %d has taken a fork\n",
			get_time(d), (*d)->id);
	else if (flag == 'S' && blk == 0)
		printf("\033[0;35m%ld %d is sleeping\n", get_time(d), (*d)->id);
	pthread_mutex_unlock((*d)->print);
}

void	get_fork(t_dumb **d)
{
	if ((*d)->id % 2 == 0 || ((*d)->id % 2 != 0 && (*d)->id == (*d)->nphilo))
	{
		pthread_mutex_lock((*d)->left_f);
		print_status(d, 'F');
		pthread_mutex_lock((*d)->right_f);
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
		print_status(d, 'F');
		pthread_mutex_lock((*d)->left_f);
		print_status(d, 'F');
		print_status(d, 'E');
		(*d)->last_m = get_time(d);
		usleep((*d)->tt_eat * 1000);
		pthread_mutex_unlock((*d)->left_f);
		pthread_mutex_unlock((*d)->right_f);
	}
}

void	sleeping(t_dumb **d)
{
	long int	end;

	print_status(d, 'S');
	end = get_time(d) + (*d)->tt_sleep;
	while (get_time(d) < end)
		usleep(1);
}
