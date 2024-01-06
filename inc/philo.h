/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:40:52 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/07 17:55:10 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philosopher
{
	int					id;
	int					left_fork;
	int					right_fork;
	long long			last_eat;
	int					meals;
	pthread_mutex_t		mutex_eat;
	struct s_mediator	*mediator;
	pthread_t			thread;
}	t_philosopher;

typedef struct s_mediator
{
	int				philo_couter;
	int				time_to_death;
	int				time_to_eat;
	int				time_to_sleep;

	int				notepme;

	int				is_death;

	long long		start_time;

	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*forks;

	t_philosopher	*philos;

}	t_mediator;

//       --=[ init.c ]=--       //
int			check_input_init(int ac, char **av, t_mediator *med);
int			init_philo_forks(t_mediator *med);

//    --=[ symulation.c ]=--    //
void		*philo_rutine(void *data);
int			start_symulation(t_mediator *med);
void		stop_symulation(t_mediator *med);
void		death_checker(t_mediator *r);

//       --=[ utils.c ]=--       //
long long	now(void);
int			error_r(char *msg);
void		sleep_with_check(long long time, t_mediator *med);
void		print_action(t_mediator *med, int id, char *string);
long		ft_atoi(const char *nptr);

//    --=[ philo_action.c ]=--    //
void		p_eat(t_philosopher	*philo);
void		p_sleep(t_philosopher	*philo);
void		p_think(t_philosopher	*philo);

#endif