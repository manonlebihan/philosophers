/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:15:11 by mle-biha          #+#    #+#             */
/*   Updated: 2023/04/05 13:02:40 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/******************* STRUCTS *******************/

typedef struct s_main_data
{
	int						philo_nb;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						max_nb_of_eat;
	int						stop;
	long int				initial_time;					
	struct s_philosopher	*philosophers;
	pthread_mutex_t			*forks;
	pthread_mutex_t			check_stop;
}	t_main_data;

typedef struct s_philosopher
{
	int					id;
	int					nb_of_eat;
	long int			last_meal;
	t_main_data			*main_data;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		is_eating;
	pthread_t			life_of_a_philosopher;
}	t_philosopher;

/******************* PHILO FUNCTIONS *******************/
void		*life_of_a_philosopher(void *p);
void		init_philo(t_main_data *t_main_data, char **args, int nb_of_eat);

/******************* UTILS FUNCTIONS *******************/
long int	get_time(void);
void		assign_philo_data(t_main_data *main_data, int i);
void		assign_nb_of_eat(t_main_data *main_data, char **args, int argc);

/******************* FT_ATOI FUNCTION *******************/
int			ft_atoi(const char *str);

#endif
