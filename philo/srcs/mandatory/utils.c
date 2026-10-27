/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:33:01 by adastugu          #+#    #+#             */
/*   Updated: 2026/02/26 12:45:51 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/// @brief Sleeps in short steps instead of one long usleep(), so the
/// philosopher notices quickly when the simulation stops.
/// Returns 1 if the simulation stopped during the sleep.
int	psleep(long time_in_ms, t_philo *p)
{
	long	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time_in_ms)
	{
		if (philo_stopped(p))
			return (1);
		usleep(600);
	}
	return (0);
}
