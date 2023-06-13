/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:01:53 by mle-biha          #+#    #+#             */
/*   Updated: 2023/04/05 13:35:01 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	- Initializes all fields of main_data and philosophers.
*/
void	init_philo(t_main_data *main_data, char **args, int argc)
{
	int	i;

	i = 0;
	main_data->philo_nb = ft_atoi(args[1]);
	main_data->time_to_die = ft_atoi(args[2]);
	main_data->time_to_eat = ft_atoi(args[3]);
	main_data->time_to_sleep = ft_atoi(args[4]);
	assign_nb_of_eat(main_data, args, argc);
	main_data->stop = 0;
	main_data->initial_time = get_time();
	main_data->philosophers = malloc(main_data->philo_nb
			* sizeof(t_philosopher));
	main_data->forks = malloc(main_data->philo_nb * sizeof(pthread_mutex_t));
	pthread_mutex_init(&(main_data->check_stop), NULL);
	while (i < main_data->philo_nb)
	{
		assign_philo_data(main_data, i);
		i++;
	}
}

/*
	- Locks the mutex check_stop.
	- If the stop field is equal to 1, it unlocks the mutex check_stop
	and the function returns 1.
	- Otherwise, it is also unlock but it returns 0.
*/
int	should_stop(t_philosopher *philosopher)
{
	pthread_mutex_lock(&(philosopher->main_data->check_stop));
	if (philosopher->main_data->stop == 1)
	{
		pthread_mutex_unlock(&(philosopher->main_data->check_stop));
		return (1);
	}
	pthread_mutex_unlock(&(philosopher->main_data->check_stop));
	return (0);
}

/*
	- Checks if the program should stop by calling the function 'should_stop'.
	- If it should, then it returns 0, otherwise the program continues.
	- It locks the forks, locks the mutex is_eating,
	assigns the time to the last_meal field and increments the nb_of_eat.
	- Unlocks the is_eating mutex and sleep for time_to_eat ms.
	- Unlocks the forks, then checks if the program should stop or not.
	- Sleeps for time_to_sleep ms. Calls once again the fucntion should_stop.
	- Returns 1 if all went well.
*/
int	live(t_philosopher *philosopher)
{
	if (should_stop(philosopher) == 1)
		return (0);
	pthread_mutex_lock(philosopher->left_fork);
	printf("%ld %d picked up a fork\n", get_time(), philosopher->id);
	pthread_mutex_lock(philosopher->right_fork);
	printf("%ld %d picked up a fork\n", get_time(), philosopher->id);
	printf("%ld %d is eating\n", get_time(), philosopher->id);
	pthread_mutex_lock(&philosopher->is_eating);
	philosopher->last_meal = get_time();
	philosopher->nb_of_eat++;
	pthread_mutex_unlock(&philosopher->is_eating);
	usleep((philosopher->main_data->time_to_eat) * 1000);
	pthread_mutex_unlock(philosopher->right_fork);
	printf("%ld %d put down a fork\n", get_time(), philosopher->id);
	pthread_mutex_unlock(philosopher->left_fork);
	printf("%ld %d put down a fork\n", get_time(), philosopher->id);
	if (should_stop(philosopher) == 1)
		return (0);
	printf("%ld %d is sleeping\n", get_time(), philosopher->id);
	usleep((philosopher->main_data->time_to_sleep) * 1000);
	if (should_stop(philosopher) == 1)
		return (0);
	printf("%ld %d is thinking\n", get_time(), philosopher->id);
	return (1);
}

/*
	- A function called by pthread_create.
	- Checks if the id of the philosopher % 2 is equal to 1, if so, it does a
	usleep of time to eat * 500 (instead of 1000, to have time_to_eat / 2).
	- Loops until the 'live' function returns 0,
	if it does the function returns NULL.
	- If it never returns 0, it loops indefinitely.
*/
void	*life_of_a_philosopher(void *p)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)p;
	if (philosopher->id % 2 == 1)
		usleep(philosopher->main_data->time_to_eat * 500);
	while (1)
		if (live(philosopher) == 0)
			return (NULL);
}
