/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:47:47 by sdoneux           #+#    #+#             */
/*   Updated: 2022/11/20 20:27:22 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_init(t_philo *philo, t_instr *instr)
{
	int	i;

	i = instr->philos - 1;
	philo[i].next = &philo[0];
	while (i >= 0)
	{
		philo[i].place = i;
		philo[i].instr = instr;
		philo[i].last_meal = get_time();
		philo[i].times_eaten = 0;
		if (i < instr->philos - 1)
			philo[i].next = &philo[i + 1];
		i--;
	}
	return (philo);
}

t_instr	*init_instr(int argc, char **argv)
{
	t_instr	*instr;

	instr = malloc(sizeof(t_instr));
	if (!instr)
		return (NULL);
	instr->active = 1;
	instr->philos = ft_atoi(argv[1]);
	instr->t_die = ft_atoi(argv[2]);
	instr->t_eat = ft_atoi(argv[3]);
	instr->t_sleep = ft_atoi(argv[4]);
	instr->must_eat = -1;
	if (argc == 6)
		instr->must_eat = ft_atoi(argv[5]);
	instr->philos_finished = 0;
	instr->start_time = get_time();
	if (instr->must_eat == 0)
		instr->active = 0;
	return (instr);
}

int	error_mutex(t_philo *philo)
{
	free(philo);
	perror("Failed to init mutex");
	return (0);
}

int	init_mutex(t_philo *philo, t_instr *instr)
{
	int	i;

	i = 0;
	instr->mutex = malloc(sizeof(pthread_mutex_t) * instr->philos);
	if (!instr->mutex)
		return (0);
	while (i < instr->philos)
	{
		if (pthread_mutex_init(&(instr)->mutex[i], NULL) != 0)
			return (error_mutex(philo));
		i++;
	}
	i = 0;
	while (i < instr->philos)
	{
		if (pthread_mutex_init(&philo[i].mutex_eat, NULL) != 0)
			return (error_mutex(philo));
		i++;
	}
	if (pthread_mutex_init(&(instr->print), NULL) != 0)
		return (error_mutex(philo));
	philo_init(philo, instr);
	return (1);
}
