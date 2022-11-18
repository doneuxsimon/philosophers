/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:54:00 by sdoneux           #+#    #+#             */
/*   Updated: 2022/11/18 16:26:49 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct s_instr
{
	atomic_bool				active;
	long					philos;
	long					t_die;
	long					t_eat;
	long					t_sleep;
	pthread_mutex_t			*mutex;
	atomic_uint_fast64_t	must_eat;
	atomic_int				philos_finished;
	atomic_uint_fast64_t	start_time;
	pthread_mutex_t			print;
}		t_instr;

typedef struct s_philo
{
	long					place;
	atomic_uint_fast64_t	times_eaten;
	atomic_uint_fast64_t	last_meal;
	pthread_t				philo;
	struct s_instr			*instr;
	struct s_philo			*next;
	struct s_philo			*before;
}	t_philo;

int			ft_isdigit(int c);
long		ft_atoi(const char *str);
uint64_t	get_time(void);
void		my_sleep(uint64_t time);
int			ft_strcmp(const char *s1, char *s2);
void		print_time(t_philo *philo, const char *message);
void		check_death(t_philo *philo);
void		*routine(void *arg);
t_philo		*philo_init(t_philo *philo, t_instr *instr);
t_instr		*init_instr(int argc, char **argv);
int			init_mutex(t_philo *philo, t_instr *instr);
int			create_philos(t_philo *philo, t_instr *instr);
int			join_philos(t_philo *philo, t_instr *instr);
int			start_philo(int argc, char **argv);

#endif