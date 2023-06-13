/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:59:03 by mle-biha          #+#    #+#             */
/*   Updated: 2023/04/05 13:28:38 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	- Frees all the ressources.
	- Destroys the mutexes forks and philosophers for each philosopher.
	- Destroys the mutex check_stop and frees philosophers and forks.
*/
void	free_all(t_main_data *main_data)
{
	int	i;

	i = 0;
	while (i < main_data->philo_nb)
	{
		pthread_mutex_destroy(&(main_data->forks[i]));
		pthread_mutex_destroy(&(main_data->philosophers[i].is_eating));
		i++;
	}
	pthread_mutex_destroy(&(main_data->check_stop));
	free(main_data->philosophers);
	free(main_data->forks);
}

/*
	- Checks when was the last meal of the philosopher.
	- If the philosopher is dead, it prints a massage, 
	then and it returns 0.
*/
int	calculate_time(t_philosopher *p)
{
	long int	current_time;

	current_time = get_time();
	if (p->last_meal != 0)
	{
		if ((current_time - p->last_meal) > p->main_data->time_to_die)
		{
			printf("%ld %d died\n", get_time(), p->id);
			return (0);
		}
	}
	return (1);
}

/*
	- Checks if all the philosopher have eaten at least max_nb_of_eat.
	- If the max_nb_of_eat is equal to -1 then the field wasn't passed
	as an arguments.
	- Loops as long as i is inferior to philo_nb.
	- In the loop, it checks is the nb_of_eat of the philosopher is inferior
	of the max_nb_of_eat, if so, it returns 0.
	- If all was good, it returns 1.
*/
int	have_eaten_enough(t_main_data *main_data)
{
	int	i;

	i = 0;
	if (main_data->max_nb_of_eat == -1)
		return (0);
	while (i < main_data->philo_nb)
	{
		if (main_data->philosophers[i].nb_of_eat < main_data->max_nb_of_eat)
			return (0);
		i++;
	}
	return (1);
}

/*
	- Loops as long as i is inferior as philo_nb.
	- Locks the mutex is_eating.
	- Checks if the philosopher starved or if he has eaten enough.
	- If so, it locks the check_stop mutex, then assign 1 to the stop field.
	- Then unlocks check_stop and is_eating and returns NULL.
	- If not, it unlocks the is_eating mutex.
	- If it goes out of the second loop, it sleeps during 100 ms.
*/
void	alive_and_kicking(t_main_data	*main_data)
{
	int			i;

	while (1)
	{
		i = 0;
		while (i < main_data->philo_nb)
		{
			pthread_mutex_lock(&(main_data->philosophers[i].is_eating));
			if (calculate_time(&(main_data->philosophers[i])) == 0
				|| have_eaten_enough(main_data) == 1)
			{
				pthread_mutex_lock(&(main_data->check_stop));
				main_data->stop = 1;
				pthread_mutex_unlock(&(main_data->check_stop));
				pthread_mutex_unlock(&(main_data->philosophers[i].is_eating));
				return ;
			}
			pthread_mutex_unlock(&(main_data->philosophers[i].is_eating));
			i++;
		}
		usleep(100);
	}
}

/*
	- Checks if there is the right amount of arguments.
	- If it's the case, it calls the function 'init_philo', then the
	'alive_and_kicking' function and then the 'free_all' function.
*/
int	main(int argc, char *argv[])
{
	t_main_data	main_data;

	if (argc < 5 || argc > 6)
	{
		printf("Error: progam should have 4 or 5 args.\n");
		return (1);
	}
	init_philo(&main_data, argv, argc);
	alive_and_kicking(&main_data);
	free_all(&main_data);
	return (0);
}
