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
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/// @brief Sleeps in short steps: one long usleep() can overshoot by
/// several ms under load, which is enough to miss a meal deadline.
void	psleep(long time_in_ms)
{
	long	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time_in_ms)
		usleep(500);
}

/// @brief Builds "<time> <id> <msg>" and sends it with a single write().
/// printf() would buffer the line inside this process, and a philosopher
/// killed with SIGKILL loses its buffer when stdout is a pipe or a file.
void	print_status(t_process *p, char *msg)
{
	char	line[64];
	int		len;
	ssize_t	ret;

	sem_wait(p->sim->print_lock);
	len = put_nbr(line, get_time_ms() - p->sim->start_time);
	line[len++] = ' ';
	len += put_nbr(line + len, p->id + 1);
	line[len++] = ' ';
	while (*msg && len < 62)
		line[len++] = *msg++;
	line[len++] = '\n';
	ret = write(1, line, len);
	(void)ret;
	sem_post(p->sim->print_lock);
}
