/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:58:12 by mbamatra          #+#    #+#             */
/*   Updated: 2024/10/27 09:06:50 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	time;
	long			ms;

	ms = 0;
	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void	free_all(t_table *table, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
		free(philo[i]);
	free(philo);
	free(table->forks);
	free(table->forks_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->death_mutex);
}

int	print_messege_utils(t_philo *philo, char *str)
{
	if (philo_died(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d %s\n", get_time() - philo->start_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (0);
}

int	print_messege(int flag_num, t_philo *philo)
{
	if (flag_num == 1)
	{
		print_messege_utils(philo, FORK_1);
		print_messege_utils(philo, FORK_2);
		return (print_messege_utils(philo, EATING));
	}
	else if (flag_num == 2)
		return (print_messege_utils(philo, THINKING));
	else if (flag_num == 3)
		return (print_messege_utils(philo, SLEEPING));
	else if (flag_num == 4)
		return (print_messege_utils(philo, DIED));
	return (0);
}

void	*new_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "Malloc failed\n", 14);
		return (NULL);
	}
	return (ptr);
}
