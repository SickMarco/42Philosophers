/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:46:23 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/22 18:36:21 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_init(t_ph **ph, int ac, char **av)
{
	(void)ac;
	*ph = ft_calloc(sizeof(t_ph), 1);
	(*ph)->nphilo = ft_atoi(av[1]);
	//(*ph)->tt_die = ft_atoi(av[2]);
	//(*ph)->tt_eat = ft_atoi(av[3]);
	//(*ph)->tt_sleep = ft_atoi(av[4]);
	//if (ac == 6)
	//	(*ph)->meals = ft_atoi(av[5]);
		
}

int	main(int ac, char **av)
{
	t_ph		*ph;

	if (ac == 5 || ac == 6)
	{
		philo_init(&ph, ac, av);
		ph->th = malloc(sizeof(pthread_t) * (ph->nphilo + 1));
	}
	else
		printf("\033[0;31mWrong input\n\033[0;37m");
	return (0);
}
