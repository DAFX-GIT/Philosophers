/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:13:02 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/15 15:13:17 by adastugu         ###   ########.fr       */
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
