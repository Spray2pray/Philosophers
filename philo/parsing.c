/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:15:48 by mbamatra          #+#    #+#             */
/*   Updated: 2024/10/27 09:08:46 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					sign;
	long long			result;

	result = 0;
	sign = 1;
	while (*str != '\0' && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign *= -1;
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10
				&& (*str - '0') > LLONG_MAX % 10))
		{
			if (sign == -1)
				return (0);
			else
				return (-1);
		}
		result = result * 10 + (*(str++) - '0');
	}
	return (result * sign);
}

int	parse_input(t_table *table, char **argv)
{
	table->philo_num = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->meals_count = ft_atoi(argv[5]);
	else
		table->meals_count = -1;
	if (table->philo_num < 1 || table->philo_num > 2147483647
		|| table->time_to_die <= 0 || table->time_to_die > 2147483647
		|| table->time_to_eat <= 0 || table->time_to_eat > 2147483647
		|| table->time_to_sleep <= 0 || table->time_to_sleep > 2147483647
		|| (argv[5] && (table->meals_count <= 0
				|| table->meals_count > 2147483647)))
		return (1);
	return (0);
}
