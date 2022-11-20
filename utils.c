/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:48:49 by sdoneux           #+#    #+#             */
/*   Updated: 2022/11/16 17:22:34 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

static long	ft_isspace(const char *str, long i)
{
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	return (i);
}

static long	ft_issneg(const char *str, long *i, long isneg)
{
	if (str[*i] != '\0' && str[*i] == '-')
	{
		isneg = 1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	return (isneg);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	nbr;
	int		isneg;

	i = 0;
	nbr = 0;
	isneg = 0;
	i = ft_isspace(str, i);
	isneg = ft_issneg(str, &i, isneg);
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (-2147483648);
		nbr = (nbr * 10) + (str[i++] - '0');
		if (isneg == 1 && nbr > 2147483648)
			return (-2147483648);
		if (isneg == 0 && nbr > 2147483647)
			return (-2147483648);
	}
	if (isneg == 1)
		return (-nbr);
	return (nbr);
}
