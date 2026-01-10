/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:33:01 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/09 17:42:51 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
int	nb_len(long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	while (nb > 0)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}

long get_time_ms(t_state *p)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000L + tv.tv_usec / 1000L) - p->start_time);
}

void print_status(t_state *p, char *msg)
{
	if(!p->sim->stop)
	{
		pthread_mutex_lock(&p->sim->print_lock);
		printf("%ld %d %s\n", get_time_ms(p), p->id, msg);
		pthread_mutex_unlock(&p->sim->print_lock);
	}
}
