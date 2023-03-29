/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:00:31 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/29 14:47:25 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	pthread_mutex_lock((*d)->death);
	if (*((*d)->status) == 0 && (*d)->e_meals >= (*d)->meals)
	{
		pthread_mutex_unlock((*d)->death);
		return (0);
	}
	pthread_mutex_unlock((*d)->death);
	return (1);
}

void	*a_dumb_philo(void *arg)
{
	t_dumb	*d;

	d = (t_dumb *)arg;
	if (d->id % 2 == 0)
		usleep(5000);
	while (1)
	{
		get_fork(&d);
		status(get_time(d->ts, d->tu), d->id, d->print, 'S');
		usleep((*d).tt_sleep * 1000);
		status(get_time(d->ts, d->tu), d->id, d->print, 'T');
		if (!alive(&d))
			break ;
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
