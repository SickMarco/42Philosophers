/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:00:31 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/24 16:15:20 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*a_dumb_philo(void *arg)
{
	t_dumb	*d;

	d = (t_dumb *)arg;
	if (d->id % 2 == 0)
		usleep(10000);
	while (1)
	{
		get_fork(&d);
		sleeping(&d);
		print_status(&d, 'T');
	}
	return (0);
}

void	philos_thread(t_ph **ph)
{
	int	i;

	i = -1;
	pthread_mutex_init(&(*ph)->print, NULL);
	while (++i < (*ph)->nphilo)
	{
		if (pthread_create(&(*ph)->th[i], NULL, &a_dumb_philo, &(*ph)->dumb[i]))
			printf("Thread Error\n");
	}
	i = -1;
	while (++i < (*ph)->nphilo)
		pthread_join((*ph)->th[i], NULL);
	i = -1;
	while (++i < (*ph)->nphilo)
		pthread_mutex_destroy(&(*ph)->forks[i]);
	pthread_mutex_destroy(&(*ph)->print);
}