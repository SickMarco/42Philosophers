/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:41:50 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/22 18:25:06 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_ph{
	int	nphilo;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	meals;
	pthread_t	*th;
}				t_ph;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);

#endif