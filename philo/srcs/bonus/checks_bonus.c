/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:54:30 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/14 16:57:25 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief Signals the parent (once) that this philosopher ate enough.
void	check_done(t_process *p)
{
	if (!p->done && p->sim->musteat > 0 && p->eaten >= p->sim->musteat)
	{
		p->done = 1;
		sem_post(p->sim->philos_done);
	}
}
