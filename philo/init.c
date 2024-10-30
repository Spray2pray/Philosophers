/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 00:49:04 by mbamatra          #+#    #+#             */
/*   Updated: 2024/10/27 09:05:59 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_available(t_philo *philo)
{
	int	fork_counter;

	fork_counter = 0;
	pthread_mutex_lock(&philo->table->forks_mutex[philo->left_fork]);
	if (philo->table->forks[philo->left_fork] != philo->id)
		fork_counter++;
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->left_fork]);
	pthread_mutex_lock(&philo->table->forks_mutex[philo->right_fork]);
	if (philo->table->forks[philo->right_fork] != philo->id)
		fork_counter++;
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->right_fork]);
	return (fork_counter);
}

t_philo	*initialize_forks(void *fork)
{
	t_philo	*philo;

	philo = (t_philo *)fork;
	philo->start_time = get_time();
	philo->last_meal_time = philo->start_time;
	if (philo->id == 0)
	{
		philo->left_fork = philo->table->philo_num - 1;
		philo->right_fork = philo->id;
	}
	else
	{
		philo->left_fork = philo->id - 1;
		philo->right_fork = philo->id;
	}
	if (philo->table->philo_num == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(philo->time_to_die, philo);
		printf("%ld 1 has died\n", get_time() - philo->start_time);
		philo->table->dead = true;
	}
	return (philo);
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	table->dead = false;
	table->forks = new_malloc(sizeof(int) * table->philo_num);
	table->forks_mutex = new_malloc(sizeof(pthread_mutex_t) * table->philo_num);
	while (++i < table->philo_num)
	{
		if (i == 0 || i == table->philo_num - 1)
			table->forks[i] = table->philo_num - 1;
		else if (i % 2 == 0)
			table->forks[i] = i + 1;
		else
			table->forks[i] = i;
		pthread_mutex_init(&table->forks_mutex[i], NULL);
	}
}

t_philo	**init_philo(t_table *table)
{
	t_philo	**philo;
	int		i;

	i = -1;
	philo = new_malloc(sizeof(t_philo *) * table->philo_num);
	while (++i < table->philo_num)
	{
		philo[i] = new_malloc(sizeof(t_philo));
		philo[i]->id = i;
		philo[i]->time_to_die = table->time_to_die;
		philo[i]->time_to_eat = table->time_to_eat;
		philo[i]->time_to_sleep = table->time_to_sleep;
		philo[i]->meals_count = table->meals_count;
		philo[i]->table = table;
	}
	return (philo);
}
