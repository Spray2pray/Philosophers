/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:25:23 by mbamatra          #+#    #+#             */
/*   Updated: 2024/10/27 09:09:02 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(long time, t_philo *philo)
{
	long	start;
	long	end;

	start = get_time();
	end = start + time;
	while (get_time() < end)
	{
		if (philo_died(philo))
			return (1);
		usleep(250);
	}
	return (0);
}

int	philo_died(t_philo *philo)
{
	if (philo->meals_count != -1 && philo->meals_count == 0)
		return (1);
	pthread_mutex_lock(&philo->table->death_mutex);
	if (philo->table->dead == true)
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (1);
	}
	if (get_time() - philo->last_meal_time >= philo->time_to_die)
	{
		philo->table->dead = true;
		pthread_mutex_unlock(&philo->table->death_mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ld %d %s\n", get_time() - philo->start_time,
			philo->id + 1, DIED);
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (0);
}

void	*routine_helper(t_philo *philo)
{
	if (print_messege(1, philo)
		|| ft_usleep(philo->time_to_eat, philo))
		return (NULL);
	philo->last_meal_time = get_time();
	pthread_mutex_lock(&philo->table->forks_mutex[philo->left_fork]);
	philo->table->forks[philo->left_fork] = philo->id;
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->left_fork]);
	pthread_mutex_lock(&philo->table->forks_mutex[philo->right_fork]);
	philo->table->forks[philo->right_fork] = philo->id;
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->right_fork]);
	if (print_messege(3, philo) || ft_usleep(philo->time_to_sleep, philo)
		|| print_messege(2, philo))
		return (NULL);
	philo->meals_count--;
	return (philo);
}

void	*routine(void *t)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = initialize_forks(t);
	while (philo_died(philo) == 0)
	{
		if ((philo->meals_count == -1 || philo->meals_count != 0))
		{
			if (forks_available(philo) == 2)
			{
				i = 1;
				if (routine_helper(philo) == NULL)
					return (NULL);
			}
			else if (i == 0 && i++)
				ft_usleep(philo->time_to_eat - 2, philo);
			else if (i == 1 && i++)
				ft_usleep(4, philo);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	**philo;
	int		i;

	i = -1;
	if (argc < 5 || argc > 6)
		return (write(2, "Wrong number of arguments\n", 27));
	if (parse_input(&table, argv) == 1)
	{
		write(2, "Invalid arguments\n", 18);
		return (1);
	}
	data_init(&table);
	philo = init_philo(&table);
	while (++i < table.philo_num)
		pthread_create(&philo[i]->thread_id, NULL, routine, (void *)philo[i]);
	i = -1;
	while (++i < table.philo_num)
		pthread_join(philo[i]->thread_id, NULL);
	free_all(&table, philo);
}
