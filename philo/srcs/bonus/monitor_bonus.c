/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:07:19 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/21 14:29:05 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_process *p, char *msg)
{
	sem_wait(p->sim->print_lock);
	pthread_mutex_lock(&p->last_meal_lock);
	if (!p->sim_stop)
	{
		printf("%ld %d %s\n", get_time_ms() - p->sim->start_time, p->philo_id
			+ 1, msg);
	}
	sem_post(p->sim->print_lock);
	pthread_mutex_unlock(&p->last_meal_lock);
}

void	*death(void *arg)
{
	t_process	*p;

	p = (t_process *)arg;
	while (!p->sim_stop)
	{
		sem_wait(p->sim->print_lock);
		pthread_mutex_lock(&p->last_meal_lock);
		if (get_time_ms() - p->last_meal >= p->sim->t2die)
		{
			pthread_mutex_unlock(&p->last_meal_lock);
			p->sim_stop = 1;
			printf("%ld %d %s\n", get_time_ms() - p->sim->start_time,
				p->philo_id + 1, "died");
			return (sem_post(p->sim->stop_sim), NULL);
		}
		sem_post(p->sim->print_lock);
		pthread_mutex_unlock(&p->last_meal_lock);
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
		sem_wait(sim->philos_done);
		i++;
	}
	if (sim->stop)
		return (NULL);
	sem_wait(sim->print_lock);
	sem_post(sim->stop_sim);
	printf("%ld %s\n", get_time_ms() - sim->start_time,
		"All philosophers have eaten their fill");
	return (NULL);
}
