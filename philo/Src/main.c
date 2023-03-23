/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:46:23 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/23 19:09:31 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_struct_init(t_ph **ph)
{
	int	i;

	i = -1;
	(*ph)->dumb = ft_calloc(sizeof(t_dumb), ((*ph)->nphilo + 1));
	while (++i < (*ph)->nphilo)
	{
		(*ph)->dumb[i].ph = (*ph);
		(*ph)->dumb[i].id = i + 1;
		(*ph)->dumb[i].tt_die = (*ph)->tt_die;
		(*ph)->dumb[i].tt_eat = (*ph)->tt_eat;
		(*ph)->dumb[i].tt_sleep = (*ph)->tt_sleep;
		(*ph)->dumb[i].tt_die = (*ph)->tt_die;
		(*ph)->dumb[i].time_start = (*ph)->time_start;
		(*ph)->dumb[i].time_ustart = (*ph)->time_ustart;
		if ((*ph)->meals)
			(*ph)->dumb[i].meals = (*ph)->meals;
	}
}

void	philo_init(t_ph **ph, int ac, char **av)
{
	struct timeval	ts;

	(void)ac;
	*ph = ft_calloc(sizeof(t_ph), 1);
	(*ph)->nphilo = ft_atoi(av[1]);
	gettimeofday(&ts, NULL);
 	(*ph)->time_start = ts.tv_sec;
	(*ph)->time_ustart = ts.tv_usec;
/*	(*ph)->tt_die = ft_atoi(av[2]);
	(*ph)->tt_eat = ft_atoi(av[3]);
	(*ph)->tt_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*ph)->meals = ft_atoi(av[5]);
	else
		(*ph)->meals = 0; */
	philo_struct_init(ph);
}

int	main(int ac, char **av)
{
	t_ph		*ph;

	philo_init(&ph, ac, av);
	ph->th = malloc(sizeof(pthread_t) * (ph->nphilo + 1));
	philos_thread(&ph);
	free_for_all(&ph);
	return (0);
}
