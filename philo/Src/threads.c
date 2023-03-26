/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:00:31 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/26 23:05:49 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	alive(t_dumb **d)
{
	if ((*d)->tt_die < (get_time(d) - (*d)->last_m))
	{
		print_status(d, 'D');
		return (0);
	}
	else if (!(*d)->meals)
		return (1);
	else if ((*d)->meals < (*d)->e_meals)
		return (0);
	return (1);
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
		sleeping(&d);
		if (++d->e_meals > d->meals)
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
	i = -1;
	while (++i < (*ph)->nphilo)
		pthread_join((*ph)->th[i], NULL);
	i = -1;
	while (++i < (*ph)->nphilo)
		pthread_mutex_destroy(&(*ph)->forks[i]);
	pthread_mutex_destroy(&(*ph)->print);
}
