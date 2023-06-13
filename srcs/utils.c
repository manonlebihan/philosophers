/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:54:29 by mle-biha          #+#    #+#             */
/*   Updated: 2023/04/05 13:36:01 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	- Assign max_nb_of_eat of main_data depending on if the argument was passed
	to the program or not.
*/
void	assign_nb_of_eat(t_main_data *main_data, char **args, int argc)
{
	if (argc == 6)
		main_data->max_nb_of_eat = ft_atoi(args[5]);
	else
		main_data->max_nb_of_eat = -1;
}

/*
	- Initializes each forks.
	- Initializes each philosophers.
	- Creates a thread for each philosopher and calls the function
	'life_of_a_philosopher'.
	- Then calls the function 'pthread_detach' to detach the thread to allow
	the other threads to run, once it is done, it frees all the used ressources.
*/
void	assign_philo_data(t_main_data *main_data, int i)
{
	pthread_mutex_init(&(main_data->forks[i]), NULL);
	main_data->philosophers[i].id = i + 1;
	main_data->philosophers[i].nb_of_eat = 0;
	main_data->philosophers[i].last_meal = 0;
	main_data->philosophers[i].left_fork = &(main_data->forks[i]);
	main_data->philosophers[i].right_fork = &(main_data->forks[(i + 1)
			% main_data->philo_nb]);
	main_data->philosophers[i].main_data = main_data;
	main_data->philosophers[i].last_meal = main_data->initial_time;
	pthread_mutex_init(&(main_data->philosophers[i].is_eating), NULL);
	pthread_create(&(main_data->philosophers[i].life_of_a_philosopher),
		NULL, life_of_a_philosopher, &(main_data->philosophers[i]));
	pthread_detach(main_data->philosophers[i].life_of_a_philosopher);
}

/*
	- Function to get the current time in milliseconds.
*/
long int	get_time(void)
{
	struct timeval	tv;
	long int		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_ms);
}
