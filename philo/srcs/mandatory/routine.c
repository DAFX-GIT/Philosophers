/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:02:48 by adastugu          #+#    #+#             */
/*   Updated: 2026/10/27 16:33:08 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	to_eat(t_philo *p)
{
	if (p->state != THINKING)
		return ;
	lock_forks(p);
	set_last_meal(p);
	print_status(p, "is eating");
	pthread_mutex_lock(&p->sim->done_lock);
	p->eaten++;
	pthread_mutex_unlock(&p->sim->done_lock);
	p->state = EATING;
}

/// @brief Moves EATING -> SLEEPING -> THINKING once enough time has passed.
/// Called on every loop tick, so each transition happens as soon as it's due.
static int	to_sleep_and_think(t_philo *p)
{
	if (p->state == EATING && get_time_ms() - p->last_meal >= p->sim->t2eat)
	{
		unlock_forks(p);
		p->state = SLEEPING;
		p->last_action = get_time_ms();
		print_status(p, "is sleeping");
		if (psleep(p->sim->t2sleep - WAKE_MARGIN_MS, p))
			return (1);
	}
	if (p->state == SLEEPING
		&& get_time_ms() - p->last_action >= p->sim->t2sleep)
	{
		p->state = THINKING;
		print_status(p, "is thinking");
	}
	return (0);
}

/// @brief Philosopher thread. Eating and the end of sleeping are not
/// slept through but polled by this loop, so the usleep() at the bottom is
/// what keeps it from spinning at 100% CPU. 400 us was the best trade-off
/// between precision and CPU load in testing (e.g. 400 410 200 200).
static void	*life(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (wait_start(p))
		return (NULL);
	psleep(p->sim->start_time - get_time_ms(), p);
	print_status(p, "is thinking");
	if (check_single(p))
		return (NULL);
	psleep(p->sim->start_time - get_time_ms()
		+ start_delay(p->id, p->sim->nbof_philos, p->sim->t2eat), p);
	while (1)
	{
		to_eat(p);
		if (philo_stopped(p))
			break ;
		if (to_sleep_and_think(p))
			break ;
		usleep(400);
	}
	if (p->state == EATING)
		unlock_forks(p);
	return (NULL);
}

/// @brief Picks a start time just ahead and hands it to every philosopher
/// through their own flag. Each one then waits for that time on the clock,
/// so they all begin together, however long thread creation took.
static void	release_philos(t_sim *sim)
{
	int	i;

	sim->start_time = get_time_ms() + START_MARGIN_MS;
	i = 0;
	while (i < sim->nbof_philos)
	{
		pthread_mutex_lock(&sim->philo[i].philo_lock);
		sim->philo[i].last_meal = sim->start_time;
		sim->philo[i].started = 1;
		pthread_mutex_unlock(&sim->philo[i].philo_lock);
		i++;
	}
}

/// @brief Starts one thread per philosopher plus the monitors, then waits
/// for the simulation to end. Returns 1 if a thread could not be created.
int	start_simulation(t_sim *sim)
{
	int	i;

	if (pthread_create(&sim->printer, NULL, &printer, sim))
		return (1);
	i = 0;
	while (i < sim->nbof_philos)
	{
		if (pthread_create(&sim->philothread[i], NULL, &life, &sim->philo[i]))
			return (stop_and_join(sim, i, 0), 1);
		i++;
	}
	release_philos(sim);
	if (pthread_create(&sim->monitor[0], NULL, &death, sim))
		return (stop_and_join(sim, i, 0), 1);
	if (sim->musteat
		&& pthread_create(&sim->monitor[1], NULL, &gluttony, sim))
		return (stop_and_join(sim, i, 1), 1);
	wait_sim_stop(sim);
	stop_and_join(sim, i, 1 + (sim->musteat > 0));
	return (0);
}
