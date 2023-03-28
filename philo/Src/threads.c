/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:00:31 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/28 15:37:35 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*a_dumb_philo(void *arg)
{
	t_dumb	*d;

	d = (t_dumb *)arg;
	if (d->id % 2 == 0)
		usleep(10000);
	while (*(d->status) != 0)
	{
		get_fork(&d);
		print_status(&d, 'S');
		usleep((*d).tt_sleep * 1000);
		print_status(&d, 'T');
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
