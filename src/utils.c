/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:07:04 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/07 18:32:51 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	error_r(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

void	sleep_with_check(long long time, t_mediator *med)
{
	long long	i;

	i = now();
	while (!(med->is_death))
	{
		if ((now() - i) >= time)
			break ;
		usleep(50);
	}
}

void	print_action(t_mediator *med, int id, char *string)
{
	pthread_mutex_lock(&(med->mutex_print));
	if (!(med->is_death))
	{
		printf("\e[33m%lli \e[0m", now() - med->start_time);
		printf("\e[36m%i \e[0m", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(med->mutex_print));
}

long	ft_atoi(const char *nptr)
{
	int		result_sign;
	long	result;

	if (!*nptr)
		return (0);
	result_sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr++ == '-')
			result_sign = -1;
	}
	result = 0;
	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
			break ;
		result *= 10;
		result += *nptr - '0';
		nptr++;
	}
	return (result * result_sign);
}
