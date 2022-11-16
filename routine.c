/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:49:27 by sdoneux           #+#    #+#             */
/*   Updated: 2022/11/14 17:55:05 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philo *philo)
{
	int	i;

	while (philo->instr->active == 1)
	{
		i = 0;
		while (i < philo->instr->active)
		{
			if (philo->times_eaten == philo->instr->must_eat)
			{
				philo->instr->active = 0;
				printf("fini\n");
				break ;
			}
			if (get_time() > (philo + i)->last_meal + philo->instr->t_die)
			{
				philo->instr->active = 0;
				print_time(philo + i, "died");
				break ;
			}
		}
	}
}

bool	main_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	print_time(philo, "has taken a fork");
	if (philo->instr->philos < 2)
	{
		my_sleep(philo->instr->t_die + 100);
		return (true);
	}
	pthread_mutex_lock(&philo->next->mutex);
	print_time(philo, "has taken a fork");
	philo->last_meal = get_time();
	my_sleep(philo->instr->t_eat);
	print_time(philo, "is eating");
	philo->times_eaten += 1;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->next->mutex);
	philo->instr->philos_finished += philo->times_eaten
		== philo->instr->must_eat;
	if (philo->instr->active == 0)
		return (true);
	print_time(philo, "is sleeping");
	my_sleep(philo->instr->t_sleep);
	print_time(philo, "is thinking");
	return (!philo->instr->active);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->place % 2 == 0)
		my_sleep(50);
	while (1)
	{
		if (main_routine(philo))
			break ;
	}
	return (philo);
}
