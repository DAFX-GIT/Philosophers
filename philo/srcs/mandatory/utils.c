/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:33:01 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/13 15:29:49 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	else
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	psleep(long time_in_ms, t_philo *p)
{
	long	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time_in_ms)
	{
		if (check_stop(p))
			return (1);
		check_done(p);
		usleep(100);
	}
	return (0);
}
