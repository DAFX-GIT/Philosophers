/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:27:33 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/26 17:37:47 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_all(char *buf, int len)
{
	ssize_t	ret;

	while (len > 0)
	{
		ret = write(1, buf, len);
		if (ret <= 0)
			return ;
		buf += ret;
		len -= ret;
	}
}

/// @brief Appends "<time> [<id>] <msg>\n" to the log buffer (id <= 0: none).
/// Caller holds print_lock and has called wait_log_space().
void	log_line(t_sim *sim, long time, int id, char *msg)
{
	char	*dst;

	dst = sim->log + sim->log_len;
	dst += put_nbr(dst, time);
	*dst++ = ' ';
	if (id > 0)
	{
		dst += put_nbr(dst, id);
		*dst++ = ' ';
	}
	while (*msg)
		*dst++ = *msg++;
	*dst++ = '\n';
	sim->log_len = dst - sim->log;
}

/// @brief Only blocks if the printer is so far behind that the buffer is
/// full. print_lock is released while waiting so the printer can drain it.
void	wait_log_space(t_sim *sim)
{
	while (sim->log_len > LOG_SIZE - LOG_LINE_MAX)
	{
		pthread_mutex_unlock(&sim->print_lock);
		usleep(500);
		pthread_mutex_lock(&sim->print_lock);
	}
}

/// @brief Printer thread. Every ms it swaps the filled buffer for an empty
/// one under print_lock (a pointer swap), then write()s it without the lock.
/// A slow terminal only ever blocks this thread, never a philosopher.
/// Lines and `stop` are both set under print_lock, so the swap that first
/// sees `stop` also contains the last line ("died"): write it and exit.
void	*printer(void *arg)
{
	t_sim	*sim;
	char	*full;
	int		len;
	int		done;

	sim = (t_sim *)arg;
	done = 0;
	while (!done)
	{
		usleep(1000);
		pthread_mutex_lock(&sim->print_lock);
		full = sim->log;
		sim->log = sim->log_out;
		sim->log_out = full;
		len = sim->log_len;
		sim->log_len = 0;
		done = sim->stop;
		pthread_mutex_unlock(&sim->print_lock);
		write_all(full, len);
	}
	return (NULL);
}
