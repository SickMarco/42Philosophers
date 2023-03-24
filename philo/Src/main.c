/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:46:23 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/24 16:14:06 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_fork_set(t_ph **ph, int i)
{
	if ((*ph)->dumb[i].id == 1)
	{
		(*ph)->dumb[i].left_f = &(*ph)->forks[(*ph)->nphilo - 1];
		(*ph)->dumb[i].right_f = &(*ph)->forks[0];
	}
	else if ((*ph)->dumb[i].id == (*ph)->nphilo + 1)
	{
		(*ph)->dumb[i].left_f = &(*ph)->forks[(*ph)->nphilo - 1];
		(*ph)->dumb[i].right_f = &(*ph)->forks[(*ph)->nphilo];
	}
	else
	{
		(*ph)->dumb[i].left_f = &(*ph)->forks[(*ph)->dumb[i].id - 2];
		(*ph)->dumb[i].right_f = &(*ph)->forks[(*ph)->dumb[i].id - 1];
	}
}

void	philo_struct_init(t_ph **ph)
{
	int	i;

	i = -1;
	(*ph)->dumb = ft_calloc(sizeof(t_dumb), ((*ph)->nphilo + 1));
	while (++i < (*ph)->nphilo)
	{
		(*ph)->dumb[i].ph = (*ph);
		(*ph)->dumb[i].id = i + 1;
		(*ph)->dumb[i].nphilo = (*ph)->nphilo;
		(*ph)->dumb[i].tt_die = (*ph)->tt_die;
		(*ph)->dumb[i].tt_die = (*ph)->tt_die;
		(*ph)->dumb[i].tt_eat = (*ph)->tt_eat;
		(*ph)->dumb[i].tt_sleep = (*ph)->tt_sleep;
		(*ph)->dumb[i].tt_die = (*ph)->tt_die;
		(*ph)->dumb[i].time_start = (*ph)->time_start;
		(*ph)->dumb[i].time_ustart = (*ph)->time_ustart;
		if ((*ph)->meals)
			(*ph)->dumb[i].meals = (*ph)->meals;
		philo_fork_set(ph, i);
	}
}

void	philo_init(t_ph **ph, int ac, char **av)
{
	struct timeval	ts;
	int				i;

	(void)ac;
	*ph = ft_calloc(sizeof(t_ph), 1);
	(*ph)->nphilo = ft_atoi(av[1]);
	gettimeofday(&ts, NULL);
	(*ph)->time_start = ts.tv_sec;
	(*ph)->time_ustart = ts.tv_usec;
	(*ph)->tt_eat = ft_atoi(av[2]) * 1000;
	(*ph)->tt_sleep = ft_atoi(av[3]) * 1000;
/*	(*ph)->tt_die = ft_atoi(av[2]);
	if (ac == 6)
		(*ph)->meals = ft_atoi(av[5]);
	else
		(*ph)->meals = 0; */
	i = -1;
	(*ph)->forks = ft_calloc(sizeof(pthread_mutex_t), ((*ph)->nphilo));
	while (++i < (*ph)->nphilo)
		pthread_mutex_init(&(*ph)->forks[i], NULL);
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
