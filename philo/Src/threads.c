/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:00:31 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/23 19:27:48 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*a_dumb_philo(void *arg)
{
	t_dumb	*d;

	d = (t_dumb *)arg;
	pthread_mutex_lock(&d->ph->forks[1]);
	int i = -1;
	while (++i < 4)
	{
		printf("%ld %d is a ktm\n", get_time(&d->ph), d->id);
		sleep(1);
	}
	pthread_mutex_unlock(&d->ph->forks[1]);
	return (0);
}

void	philos_thread(t_ph **ph)
{
	int	i;

	i = -1;
	(*ph)->forks = ft_calloc(sizeof(pthread_mutex_t), ((*ph)->nphilo + 1));
	while (++i < (*ph)->nphilo)
		pthread_mutex_init(&(*ph)->forks[i], NULL);
	i = -1;
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
}