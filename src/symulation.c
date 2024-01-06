/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:32 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/07 18:39:08 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_rutine(void *data)
{
	t_philosopher	*philo;
	t_mediator		*med;

	philo = (t_philosopher *)data;
	med = philo->mediator;
	if (philo->id % 2 == 0)
		usleep(med->time_to_eat * 500);
	while (med->is_death == 0 && med->philo_couter > 1)
	{
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
	}
	return (NULL);
}

int	start_symulation(t_mediator *med)
{
	int	i;

	i = 0;
	med->start_time = now();
	while (i < med->philo_couter)
	{
		if (pthread_create(&med->philos[i].thread, NULL,
				philo_rutine, &(med->philos[i])))
			return (0);
		pthread_mutex_lock(&(med->philos[i].mutex_eat));
		med->philos[i].last_eat = now();
		pthread_mutex_unlock(&(med->philos[i].mutex_eat));
		i++;
	}
	return (1);
}

void	stop_symulation(t_mediator *med)
{
	int	i;

	i = 0;
	while (i < med->philo_couter)
	{
		pthread_join(med->philos[i].thread, NULL);
		i++;
	}
	i = -1;
	while (++i < med->philo_couter)
	{
		pthread_mutex_destroy(&(med->philos[i].mutex_eat));
	}
	pthread_mutex_destroy(&(med->mutex_print));
	free(med->forks);
	free(med->philos);
}

void	death_checker(t_mediator *med)
{
	int				i;
	t_philosopher	*philos;
	int				min_meals;

	philos = med->philos;
	min_meals = 0;
	while (!(med->is_death))
	{
		i = -1;
		while (++i < med->philo_couter && !(med->is_death))
		{
			pthread_mutex_lock(&(philos[i].mutex_eat));
			if (now() - philos[i].last_eat > med->time_to_death)
			{
				print_action(med, i, "\e[31mdied\e[0m");
				med->is_death = 1;
			}
			if (philos[i].meals < min_meals || i == 0)
				min_meals = philos[i].meals;
			pthread_mutex_unlock(&(philos[i].mutex_eat));
		}
		if (med->notepme != 0 && min_meals >= med->notepme)
			med->is_death = 1;
		usleep(100);
	}
}
