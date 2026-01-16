/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:50:37 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/16 16:54:41 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	while (!sim->stop)
	{
		sim->i = 0;
		while (sim->i < sim->nbof_philos)
		{
			pthread_mutex_lock(&sim->print_lock);
			pthread_mutex_lock(&sim->stop_lock);
			if (get_time_ms() - sim->philo[sim->i].last_meal >= sim->t2die)
			{
				sim->stop = 1;
				printf("%ld %d %s\n", get_time_ms() - sim->start_time,
					sim->philo[sim->i].id + 1, "has died");
				return (pthread_mutex_unlock(&sim->print_lock),
					pthread_mutex_unlock(&sim->stop_lock), NULL);
			}
			pthread_mutex_unlock(&sim->print_lock);
			pthread_mutex_unlock(&sim->stop_lock);
			sim->i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*glutony(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	i = 0;
	while (i < sim->nbof_philos)
	{
		if (check_stop(&sim->philo[0]))
			return (NULL);
		if (sim->philo[i].done == 0)
		{
			usleep(1000);
			continue ;
		}
		i++;
	}
	pthread_mutex_lock(&sim->print_lock);
	pthread_mutex_lock(&sim->stop_lock);
	sim->stop = 1;
	printf("%ld %s\n", get_time_ms() - sim->start_time,
		"All philosophers have eaten their fill");
	pthread_mutex_unlock(&sim->print_lock);
	pthread_mutex_unlock(&sim->stop_lock);
	return (NULL);
}

void	wait_sim_stop(t_sim *sim)
{
	while (1)
	{
		pthread_mutex_lock(&sim->stop_lock);
		if (sim->stop == 1)
		{
			pthread_mutex_unlock(&sim->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&sim->stop_lock);
		usleep(1000);
	}
}

void	print_status(t_philo *p, char *msg)
{
	pthread_mutex_lock(&p->sim->print_lock);
	pthread_mutex_lock(&p->sim->stop_lock);
	if (!p->sim->stop)
	{
		printf("%ld %d %s\n", get_time_ms() - p->sim->start_time, p->id + 1, msg);
	}
	pthread_mutex_unlock(&p->sim->stop_lock);
	pthread_mutex_unlock(&p->sim->print_lock);
}
