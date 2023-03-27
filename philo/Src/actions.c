/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:04:22 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/27 19:01:29 by mbozzi           ###   ########.fr       */
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
		printf("\033[0;32m%ld %d is thinking\n", get_time(d), (*d)->id);
	else if (flag == 'E')
		printf("\033[0;33m%ld %d is eating\n", get_time(d), (*d)->id);
	else if (flag == 'F')
		printf("\033[0;36m%ld %d has taken a fork\n",
			get_time(d), (*d)->id);
	else if (flag == 'S')
		printf("\033[0;35m%ld %d is sleeping\n", get_time(d), (*d)->id);
	pthread_mutex_unlock((*d)->print);
}

void	eating(t_dumb **d)
{
	print_status(d, 'E');
	pthread_mutex_lock((*d)->death);
	(*d)->last_arr[(*d)->id - 1] = get_time(d);
	pthread_mutex_unlock((*d)->death);
	usleep((*d)->tt_eat * 1000);
}

void	get_fork(t_dumb **d)
{
	if ((*d)->id % 2 == 0 || ((*d)->id % 2 != 0 && (*d)->id == (*d)->nphilo))
	{
		pthread_mutex_lock((*d)->left_f);
		print_status(d, 'F');
		pthread_mutex_lock((*d)->right_f);
		print_status(d, 'F');
		eating(d);
		pthread_mutex_unlock((*d)->right_f);
		pthread_mutex_unlock((*d)->left_f);
	}
	else
	{
		pthread_mutex_lock((*d)->right_f);
		print_status(d, 'F');
		pthread_mutex_lock((*d)->left_f);
		print_status(d, 'F');
		eating(d);
		pthread_mutex_unlock((*d)->left_f);
		pthread_mutex_unlock((*d)->right_f);
	}
}
