/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:04:22 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/24 16:14:53 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(t_dumb **d, char flag)
{
	pthread_mutex_lock(&(*d)->ph->print);
	if (flag == 'T')
		printf("\033[0;32m%ld %d is thinking\n", get_time(&(*d)->ph), (*d)->id);
	else if (flag == 'E')
		printf("\033[0;33m%ld %d is eating\n", get_time(&(*d)->ph), (*d)->id);
	else if (flag == 'F')
		printf("\033[0;36m%ld %d has taken a fork\n",
			get_time(&(*d)->ph), (*d)->id);
	else if (flag == 'S')
		printf("\033[0;35m%ld %d is sleeping\n", get_time(&(*d)->ph), (*d)->id);
	else if (flag == 'D')
		printf("\033[0;31m%ld %d is died\n", get_time(&(*d)->ph), (*d)->id);
	printf("\033[0;37m");
	pthread_mutex_unlock(&(*d)->ph->print);
}

void	get_fork(t_dumb **d)
{
	pthread_mutex_lock((*d)->left_f);
	print_status(d, 'F');
	pthread_mutex_lock((*d)->right_f);
	print_status(d, 'F');
	print_status(d, 'E');
	usleep((*d)->tt_eat);
	pthread_mutex_unlock((*d)->left_f);
	pthread_mutex_unlock((*d)->right_f);
}

void	sleeping(t_dumb **d)
{
	print_status(d, 'S');
	usleep((*d)->tt_sleep);
}
