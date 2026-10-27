/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nbr.c                                          :+:      :+:    :+:   */
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

/// @brief Writes the digits of n (n >= 0) at dst, returns how many.
int	put_nbr(char *dst, long n)
{
	int	len;
	int	i;

	len = nb_len(n);
	i = len;
	while (i-- > 0)
	{
		dst[i] = n % 10 + '0';
		n /= 10;
	}
	return (len);
}
