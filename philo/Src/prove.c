#include "../philo.h"

// PASS AND RETURN ARG IN THREAD

void	philo_init(t_ph **ph, char **av)
{
	(*ph)->nphilo = ft_atoi(av[1]);
	//(*ph)->tt_die = ft_atoi(av[2]);
	//(*ph)->tt_eat = ft_atoi(av[3]);
	//(*ph)->tt_sleep = ft_atoi(av[4]);
}

void	*add_one(void *arg)
{
	int *res = malloc(sizeof(int)); // allocazione di memoria per il risultato
	*res = *(int *)arg; // cast dell'argomento a intero
	(*res)++;
	return ((void *)res); // restituzione del risultato
}

int	main(int ac, char **av)
{
	t_ph		*ph;
	pthread_t	*th;
	int i = -1;
	int *res;

	(void)ac;
	ph = ft_calloc(sizeof(t_ph), 1);
	philo_init(&ph, av);
	th = malloc(sizeof(pthread_t) * (ph->nphilo + 1));
	while (++i < ph->nphilo)
	{
		pthread_create(&th[i], NULL, &add_one, &i);
		pthread_join(th[i], (void **)&res);
		printf("%d\n", *res);
		free(res);
	}
	return (0);
}