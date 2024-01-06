/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:15:36 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/07 18:36:57 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_philosopher *philo)
{
	t_mediator	*med;

	med = philo->mediator;
	pthread_mutex_lock(&(med->forks[philo->left_fork]));
	print_action(med, philo->id, "\e[38;5;69mhas taken a fork\e[0m");
	pthread_mutex_lock(&(med->forks[philo->right_fork]));
	print_action(med, philo->id, "\e[38;5;69mhas taken a fork\e[0m");
	print_action(med, philo->id, "\e[32mis eating\e[0m");
	pthread_mutex_lock(&(philo->mutex_eat));
	philo->last_eat = now();
	sleep_with_check(med->time_to_eat, med);
	(philo->meals)++;
	pthread_mutex_unlock(&(philo->mutex_eat));
	pthread_mutex_unlock(&(med->forks[philo->left_fork]));
	pthread_mutex_unlock(&(med->forks[philo->right_fork]));
}

void	p_sleep(t_philosopher *philo)
{
	print_action(philo->mediator, philo->id, "\e[38;5;149mis sleeping\e[0m");
	sleep_with_check(philo->mediator->time_to_sleep, philo->mediator);
}

void	p_think(t_philosopher	*philo)
{
	print_action(philo->mediator, philo->id, "\e[38;5;200mis thinking\e[0m");
}
