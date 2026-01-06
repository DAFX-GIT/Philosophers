/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:39:32 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/06 14:57:19 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo philo;

	memset(&philo, 0, sizeof(philo));
	if (ac < 4)
	{
		write(2, "Not enough arguments\n", 21);
		return (1);
	}
	parse(&philo, ac, av);
	born2philo(&philo);
}