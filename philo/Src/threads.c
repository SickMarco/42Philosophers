/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:00:31 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/31 13:10:30 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	alive(t_dumb **d)
{
	int	ret;

	pthread_mutex_lock((*d)->death);
	ret = 1;
	if ((*d)->meals && ++(*d)->e_meals == (*d)->meals)
	{
		*((*d)->status) = 0;
		ret = 0;
	}
	else if (!(*d)->meals && *((*d)->status) == 0)
		ret = 0;
	pthread_mutex_unlock((*d)->death);
	return (ret);
}

void	*a_dumb_philo(void *arg)
{
	t_dumb	*d;

	d = (t_dumb *)arg;
	if (d->nphilo == 1)
		status(get_time(d->ts, d->tu), d->id, d->print, 'F');
	else
	{
		if (d->id % 2 == 0)
			usleep(10000);
		while (1)
		{
			get_fork(&d);
			status(get_time(d->ts, d->tu), d->id, d->print, 'S');
			go_to_sleep(&d, d->tt_sleep);
			status(get_time(d->ts, d->tu), d->id, d->print, 'T');
			if (!alive(&d))
				break ;
		}
	}
	return (EXIT_SUCCESS);
}

int	philos_thread(t_ph **ph)
{
	int	i;

	i = -1;
	while (++i < (*ph)->nphilo)
		if (pthread_create(&(*ph)->th[i], NULL, &a_dumb_philo, &(*ph)->dumb[i]))
			return (write(STDERR_FILENO, "Thread Error\n", 14));
	death(ph);
	i = -1;
	while (++i < (*ph)->nphilo)
		pthread_join((*ph)->th[i], NULL);
	i = -1;
	while (++i < (*ph)->nphilo)
		pthread_mutex_destroy(&(*ph)->forks[i]);
	pthread_mutex_destroy(&(*ph)->print);
	pthread_mutex_destroy(&(*ph)->death);
	return (0);
}
