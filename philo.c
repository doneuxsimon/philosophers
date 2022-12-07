/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:12:46 by sdoneux           #+#    #+#             */
/*   Updated: 2022/12/07 17:27:00 by sdoneux          ###   ########.fr       */
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
	t_philo	*philo;
	t_instr	*instr;

	instr = init_instr(argc, argv);
	if (!instr)
		return (1);
	philo = malloc(sizeof(t_philo) * instr->philos);
	if (!philo)
	{
		free(instr);
		return (1);
	}
	if (!init_mutex(philo, instr))
		return (1);
	if (!create_philos(philo, instr))
		return (1);
	check_death(philo);
	if (!join_philos(philo, instr))
		return (1);
	free(instr->mutex);
	free(instr);
	free(philo);
	return (0);
}

int	verif_cypher(char **argv)
{
	if (ft_atoi(argv[1]) <= 0)
	{
		write(1, "Need at least one philosopher on the table\n", 43);
		return (1);
	}
	if (ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
	{
		write(1,
			"All args have to be positive and less than the max_int\n", 55);
		return (1);
	}
	if (argv[5] && ft_atoi(argv[5]) <= 0)
	{
		write(1,
			"All args have to be positive and less than the max_int\n", 55);
		return (1);
	}
	return (0);
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
	if (verif_cypher(argv))
		return (1);
	if (start_philo(argc, argv) == 1)
		return (1);
	return (0);
}
