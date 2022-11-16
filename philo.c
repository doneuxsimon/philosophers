/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:12:46 by sdoneux           #+#    #+#             */
/*   Updated: 2022/11/14 17:53:11 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_philo *philo, t_instr *instr)
{
	int	i;

	i = 0;
	while (i < instr->philos)
	{
		if (pthread_create(&philo[i].philo, NULL, routine, philo + i) != 0)
		{
			free(philo);
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_philos(t_philo *philo, t_instr *instr)
{
	int	i;

	i = 0;
	while (i < instr->philos)
	{
		if (pthread_join(philo[i].philo, NULL) != 0)
		{
			free(philo);
			return (0);
		}
		i++;
	}
	return (1);
}

int	start_philo(int argc, char **argv)
{
	long	i;
	long	j;
	t_philo	*philo;
	t_instr	*instr;

	j = 0;
	i = 1;
	instr = init_instr(argc, argv);
	philo = malloc(sizeof(t_philo) * instr->philos);
	if (!philo)
	{
		free(instr);
		return (0);
	}
	if (!init_mutex(philo, instr))
		return (0);
	if (!create_philos(philo, instr))
		return (0);
	check_death(philo);
	if (!join_philos(philo, instr))
		return (0);
	free(philo);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc < 5)
	{
		write(1, "Too few arguments\n", 18);
		return (1);
	}
	if (argc > 6)
	{
		write(1, "Too much arguments\n", 19);
		return (1);
	}
	if (ft_atoi(argv[1]) <= 0)
	{
		write(1, "Need at least one philosopher on the table\n", 43);
		return (1);
	}
	start_philo(argc, argv);
	return (0);
}
