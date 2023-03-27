/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:00:31 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/27 18:58:52 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	alive(t_dumb **d)
{
	pthread_mutex_lock((*d)->death);
	if (*((*d)->status) == 0)
	{
		pthread_mutex_unlock((*d)->death);
		return (0);
	}
	pthread_mutex_unlock((*d)->death);
	if (!(*d)->meals)
		return (1);
	else if ((*d)->meals < (*d)->e_meals)
		return (0);
	return (1);
}

void	death(t_ph **ph)
{
	int	i;

	i = -1;
	while (1)
	{
		pthread_mutex_lock(&(*ph)->death);
		if ((*ph)->status == 0)
			break ;
		if ((long)(*ph)->tt_die < (get_time2(ph) - (*ph)->last[i]))
		{
			pthread_mutex_lock(&(*ph)->print);
			printf("\033[0;31m%ld %d died\n", get_time2(ph), (i + 1));
			(*ph)->status = 0;
			pthread_mutex_unlock(&(*ph)->print);
			break ;
		}
		i++;
		if (i == (*ph)->nphilo)
			i = 0;
		pthread_mutex_unlock(&(*ph)->death);
		usleep(1000);
	}
	pthread_mutex_unlock(&(*ph)->death);
}

void	*a_dumb_philo(void *arg)
{
	t_dumb	*d;

	d = (t_dumb *)arg;
	if (d->id % 2 == 0)
		usleep(10000);
	while (alive(&d))
	{
		get_fork(&d);
		print_status(&d, 'S');
		usleep((*d).tt_sleep * 1000);
		print_status(&d, 'T');
	}
	return (0);
}

void	philos_thread(t_ph **ph)
{
	int	i;

	i = -1;
	while (++i < (*ph)->nphilo)
		if (pthread_create(&(*ph)->th[i], NULL, &a_dumb_philo, &(*ph)->dumb[i]))
			write(STDERR_FILENO, "Thread Error\n", 14);
	death(ph);
	i = -1;
	while (++i < (*ph)->nphilo)
		pthread_join((*ph)->th[i], NULL);
	i = -1;
	while (++i < (*ph)->nphilo)
		pthread_mutex_destroy(&(*ph)->forks[i]);
	pthread_mutex_destroy(&(*ph)->print);
	pthread_mutex_destroy(&(*ph)->death);
}
