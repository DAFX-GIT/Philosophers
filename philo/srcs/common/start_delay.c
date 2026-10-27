/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_delay.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:27:33 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/26 17:37:47 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(MODE_BONUS)
# include "philo_bonus.h"
#else
# include "philo.h"
#endif

/// @brief Staggers the first meal so neighbours don't all reach for the
/// same forks at t=0. With an even count, odd ids simply wait one meal.
/// With an odd count, one philosopher is half a meal out of step and eats
/// alone between the two groups instead of in a third slot: ids 0, 2 and 1
/// start half a meal apart, the rest alternate like the even case. The role
/// moves one seat at a time, so the longest gap between meals is
/// 2.5 * t2eat instead of 3 * t2eat (500 ms vs 600 ms at 5 510 200 200).
long	start_delay(int id, int nbof_philos, long t2eat)
{
	if (nbof_philos % 2 == 0)
		return ((id % 2) * t2eat);
	if (id == 0)
		return (0);
	if (id == 1)
		return (t2eat * 3 / 2);
	if (id == 2)
		return (t2eat / 2);
	if (id % 2 != 0)
		return (t2eat * 2);
	return (t2eat);
}
