/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:50:37 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/21 14:28:54 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Checks one philosopher. The cheap check only takes their own
/// meal_lock. If they look starved, it re-checks while holding print_lock,
/// so they can't print "is eating" between the check and the "died" line.
static int	has_starved(t_sim *sim, int i)
{
	t_philo	*p;
	int		starved;

	p = &sim->philo[i];
	pthread_mutex_lock(&p->meal_lock);
	starved = get_time_ms() - p->last_meal >= sim->t2die;
	pthread_mutex_unlock(&p->meal_lock);
	if (!starved)
		return (0);
	pthread_mutex_lock(&sim->print_lock);
	pthread_mutex_lock(&p->meal_lock);
	starved = !p->stop && get_time_ms() - p->last_meal >= sim->t2die;
	pthread_mutex_unlock(&p->meal_lock);
	if (starved)
	{
		printf("%ld %d died\n", get_time_ms() - sim->start_time, p->id + 1);
		stop_all(sim);
	}
	pthread_mutex_unlock(&sim->print_lock);
	return (starved);
}

/// @brief Monitor thread: stops the simulation as soon as one philosopher
/// has gone t2die ms without eating.
void	*death(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	while (!check_stop(sim))
	{
		i = 0;
		while (i < sim->nbof_philos)
			if (has_starved(sim, i++))
				return (NULL);
		usleep(400);
	}
	return (NULL);
}

/// @brief Monitor thread (only with the optional 5th argument): stops the
/// simulation once every philosopher has eaten at least musteat times.
void	*glutony(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	i = 0;
	while (i < sim->nbof_philos)
	{
		if (check_stop(sim))
			return (NULL);
		if (!check_done(&sim->philo[i]))
		{
			usleep(3500);
			continue ;
		}
		i++;
	}
	pthread_mutex_lock(&sim->print_lock);
	if (!check_stop(sim))
	{
		printf("%ld All philosophers have eaten their fill\n",
			get_time_ms() - sim->start_time);
		stop_all(sim);
	}
	pthread_mutex_unlock(&sim->print_lock);
	return (NULL);
}

void	wait_sim_stop(t_sim *sim)
{
	while (!check_stop(sim))
		usleep(1000);
}

/// @brief Thread-safe log line. Nothing is printed once the simulation
/// has stopped, so no message can appear after "died".
void	print_status(t_philo *p, char *msg)
{
	pthread_mutex_lock(&p->sim->print_lock);
	if (!p->stop)
		printf("%ld %d %s\n", get_time_ms() - p->sim->start_time, p->id + 1,
			msg);
	pthread_mutex_unlock(&p->sim->print_lock);
}
