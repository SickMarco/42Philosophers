/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:41:50 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/31 12:29:33 by mbozzi           ###   ########.fr       */
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
# include <limits.h>

typedef struct s_dumb{
	int						id;
	int						nphilo;
	int						tt_die;
	int						tt_eat;
	int						tt_sleep;
	int						meals;
	int						e_meals;
	long int				last_m;
	suseconds_t				tu;
	time_t					ts;
	pthread_mutex_t			*left_f;
	pthread_mutex_t			*right_f;
	pthread_mutex_t			*print;
	pthread_mutex_t			*death;
	int						*status;
	long int				*last_arr;
}				t_dumb;

typedef struct s_ph{
	t_dumb					*dumb;
	int						nphilo;
	pthread_t				*th;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print;
	pthread_mutex_t			death;
	struct timeval			ts;
	time_t					tse;
	suseconds_t				tu;
	int						tt_die;
	int						status;
	long int				*last;
}				t_ph;

//			PHILO			//

int			philos_thread(t_ph **ph);
void		*a_dumb_philo(void *arg);
void		death(t_ph **ph);

//			ACTIONS			//

void		status(long int time, int id, pthread_mutex_t *print, char flag);
void		get_fork(t_dumb **d);
void		go_to_sleep(t_dumb **d, int type);

//			UTILS			//

int			check_input(char **av);
long int	get_time(time_t start, suseconds_t ustart);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		free_for_all(t_ph **ph);

#endif