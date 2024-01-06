/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:39:35 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/07 17:33:47 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_mediator	mediator;

	if (!check_input_init(ac, av, &mediator))
		return (error_r("Invalid input."));
	if (!init_philo_forks(&mediator))
	{
		free(mediator.forks);
		free(mediator.philos);
		return (error_r("Failed to create symulation"));
	}
	start_symulation(&mediator);
	death_checker(&mediator);
	stop_symulation(&mediator);
	return (0);
}
