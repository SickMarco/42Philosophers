/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:41:50 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/24 16:14:30 by mbozzi           ###   ########.fr       */
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

typedef struct s_ph	t_ph;

typedef struct s_dumb{
	t_ph					*ph;
	int						id;
	int						nphilo;
	int						tt_die;
	int						tt_eat;
	int						tt_sleep;
	int						meals;
	long int				last_m;
	suseconds_t				time_ustart;
	time_t					time_start;
	pthread_mutex_t			*left_f;
	pthread_mutex_t			*right_f;
}				t_dumb;

typedef struct s_ph{
	t_dumb					*dumb;
	int						nphilo;
	int						tt_die;
	int						tt_eat;
	int						tt_sleep;
	int						meals;
	suseconds_t				time_ustart;
	time_t					time_start;
	pthread_t				*th;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print;
}				t_ph;

//			PHILO			//

void		philos_thread(t_ph **ph);
void		*a_dumb_philo(void *arg);

//			ACTIONS			//

long int	get_time(t_ph **ph);
void		print_status(t_dumb **d, char flag);
void		get_fork(t_dumb **d);
void		sleeping(t_dumb **d);

//			UTILS			//

int			ft_atoi(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		free_for_all(t_ph **ph);

#endif