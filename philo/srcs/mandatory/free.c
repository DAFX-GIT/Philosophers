/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:13:02 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/21 14:26:27 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freeparse(t_parse *parsing)
{
	int	i;

	i = 0;
	if (parsing->arg)
		while (parsing->arg[i])
			free(parsing->arg[i++]);
	if (parsing->arg)
		free(parsing->arg);
}

void	freeall(t_sim *sim)
{
	if (sim->forks)
		free(sim->forks);
	if (sim->philo)
		free(sim->philo);
	if (sim->philothread)
		free(sim->philothread);
	if (sim)
		free(sim);
}

int	join(t_sim *sim, int to_join)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sim->stop_lock);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->stop_lock);
	while (i < to_join)
	{
		pthread_join((sim->philothread[i]), NULL);
		i++;
	}
	pthread_join((sim->monitor[0]), NULL);
	if (sim->musteat)
		pthread_join((sim->monitor[1]), NULL);
	return (0);
}
