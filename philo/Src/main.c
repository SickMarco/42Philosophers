/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:46:23 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/27 19:05:54 by mbozzi           ###   ########.fr       */
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

void	philo_struct_init(t_ph **ph, int ac, char **av)
{
	int				i;

	i = -1;
	while (++i < (*ph)->nphilo)
	{
		(*ph)->dumb[i].id = i + 1;
		(*ph)->dumb[i].nphilo = (*ph)->nphilo;
		(*ph)->dumb[i].tt_die = ft_atoi(av[2]);
		(*ph)->dumb[i].tt_eat = ft_atoi(av[3]);
		(*ph)->dumb[i].tt_sleep = ft_atoi(av[4]);
		(*ph)->dumb[i].time_start = (*ph)->ts.tv_sec;
		(*ph)->dumb[i].time_ustart = (*ph)->ts.tv_usec;
		(*ph)->dumb[i].print = &(*ph)->print;
		(*ph)->dumb[i].e_meals = 1;
		(*ph)->dumb[i].death = &(*ph)->death;
		(*ph)->dumb[i].status = &(*ph)->status;
		(*ph)->dumb[i].last_arr = (*ph)->last;
		(*ph)->dumb[i].meals = 0;
		if (ac == 6)
			(*ph)->dumb[i].meals = ft_atoi(av[5]);
		philo_fork_set(ph, i);
	}
}

int	philo_init(t_ph **ph, int ac, char **av)
{
	int	i;

	i = -1;
	(*ph)->nphilo = ft_atoi(av[1]);
	(*ph)->tt_die = ft_atoi(av[2]);
	if ((*ph)->nphilo == 1)
		return (printf("\033[0;31m%d 1 died\n", (*ph)->tt_die));
	gettimeofday(&(*ph)->ts, NULL);
	(*ph)->time_start = (*ph)->ts.tv_sec;
	(*ph)->time_ustart = (*ph)->ts.tv_usec;
	(*ph)->last = ft_calloc(sizeof(long int), ((*ph)->nphilo));
	(*ph)->th = ft_calloc(sizeof(pthread_t), ((*ph)->nphilo));
	(*ph)->forks = ft_calloc(sizeof(pthread_mutex_t), ((*ph)->nphilo));
	(*ph)->dumb = ft_calloc(sizeof(t_dumb), (*ph)->nphilo);
	(*ph)->status = 1;
	pthread_mutex_init(&(*ph)->print, NULL);
	pthread_mutex_init(&(*ph)->death, NULL);
	while (++i < (*ph)->nphilo)
		pthread_mutex_init(&(*ph)->forks[i], NULL);
	philo_struct_init(ph, ac, av);
	return (0);
}

int	main(int ac, char **av)
{
	t_ph		*ph;

	if (ac == 5 || ac == 6)
	{
		ph = ft_calloc(sizeof(t_ph), 1);
		if (philo_init(&ph, ac, av))
			return (0);
		philos_thread(&ph);
		free_for_all(&ph);
	}
	else
		write(STDERR_FILENO, "\033[0;31mInsert valid arguments\n", 31);
	return (0);
}
