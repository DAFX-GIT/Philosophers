/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:04:49 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/21 14:30:08 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	else
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	psleep(long time_to_wait)
{
	long	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time_to_wait)
	{
		usleep(500);
	}
	return (0);
}

void	kill_process(t_sim *sim, int to_kill)
{
	int	i;

	i = 0;
	sim->stop = 1;
	while (i < to_kill)
	{
		sem_post(sim->philos_done);
		usleep(8000);
		kill(sim->process[i].pid, SIGKILL);
		i++;
	}
}
