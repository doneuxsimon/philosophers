/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:50:06 by sdoneux           #+#    #+#             */
/*   Updated: 2022/11/16 16:51:47 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	my_sleep(uint64_t time)
{
	uint64_t	i;

	i = get_time();
	while (1)
	{
		if (get_time() - i >= time)
			break ;
		usleep(100);
	}
}

void	print_time(t_philo *philo, const char *message)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->instr->print);
	time = get_time() - philo->instr->start_time;
	if (philo->instr->active == 1 || !ft_strcmp(message, "died"))
	{
		if (!ft_strcmp(message, "has taken a fork"))
			printf("\033[32m%llu %ld %s\n\033[0m", time,
				philo->place + 1, message);
		else if (!ft_strcmp(message, "is sleeping"))
			printf("\033[30m%llu %ld %s\n\033[0m", time,
				philo->place + 1, message);
		else if (!ft_strcmp(message, "is thinking"))
			printf("\033[35m%llu %ld %s\n\033[0m", time,
				philo->place + 1, message);
		else if (!ft_strcmp(message, "is eating"))
			printf("\033[36m%llu %ld %s\n\033[0m", time,
				philo->place + 1, message);
		if (!ft_strcmp(message, "died"))
			printf("\033[31m%llu %ld %s\n\033[0m", time,
				philo->place + 1, message);
	}
	pthread_mutex_unlock(&philo->instr->print);
}
