/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:33:01 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/12 19:14:00 by adastugu         ###   ########.fr       */
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

void	print_status(t_philo *p, char *msg)
{
	pthread_mutex_lock(&p->sim->print_lock);
	pthread_mutex_lock(&p->sim->stop_lock);
	if (!p->sim->stop)
	{
		printf("%ld %d %s\n", get_time_ms() - p->sim->start_time, p->id, msg);
	}
	pthread_mutex_unlock(&p->sim->stop_lock);
	pthread_mutex_unlock(&p->sim->print_lock);
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
