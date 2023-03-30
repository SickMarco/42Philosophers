/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:46:23 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/30 19:26:50 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
		(*ph)->dumb[i].ts = (*ph)->ts.tv_sec;
		(*ph)->dumb[i].tu = (*ph)->ts.tv_usec;
		(*ph)->dumb[i].print = &(*ph)->print;
		(*ph)->dumb[i].death = &(*ph)->death;
		(*ph)->dumb[i].status = &(*ph)->status;
		(*ph)->dumb[i].meals = 0;
		(*ph)->dumb[i].e_meals = 0;
		(*ph)->dumb[i].last_arr = (*ph)->last;
		(*ph)->dumb[i].left_f = &(*ph)->forks[i];
		(*ph)->dumb[i].right_f = &(*ph)->forks[(i + 1) % (*ph)->nphilo];
		if (ac == 6)
			(*ph)->dumb[i].meals = ft_atoi(av[5]);
	}
}

int	philo_init(t_ph **ph, int ac, char **av)
{
	int	i;

	i = -1;
	if (check_input(av))
		return (1);
	(*ph)->nphilo = ft_atoi(av[1]);
	(*ph)->tt_die = ft_atoi(av[2]);
	gettimeofday(&(*ph)->ts, NULL);
	(*ph)->tse = (*ph)->ts.tv_sec;
	(*ph)->tu = (*ph)->ts.tv_usec;
	(*ph)->last = ft_calloc(sizeof(long int), (*ph)->nphilo);
	(*ph)->th = ft_calloc(sizeof(pthread_t), (*ph)->nphilo);
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
