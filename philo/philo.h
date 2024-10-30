/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:44:11 by mbamatra          #+#    #+#             */
/*   Updated: 2024/10/27 09:09:25 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"
# define FORK_1 "has taken a fork"
# define FORK_2 "has taken a fork"

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef struct s_table {
	int				*forks;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	long			philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_count;
	bool			dead;
}	t_table;

typedef struct s_philo {
	long			meals_count;
	pthread_t		thread_id;
	int				id;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	long			last_meal_time;
	int				left_fork;
	int				right_fork;
	t_table			*table;
}	t_philo;

int		ft_atoi(const char *str);
int		parse_input(t_table *table, char **argv);
void	data_init(t_table *table);
void	*new_malloc(size_t size);
int		philo_died(t_philo *philo);
t_philo	**init_philo(t_table *table);
int		ft_usleep(long time, t_philo *philo);
t_philo	*initialize_forks(void *fork);
int		forks_available(t_philo *philo);
int		print_messege_utils(t_philo *philo, char *str);
int		print_messege(int flag_num, t_philo *philo);
void	free_all(t_table *table, t_philo **philo);
int		get_time(void);

#endif