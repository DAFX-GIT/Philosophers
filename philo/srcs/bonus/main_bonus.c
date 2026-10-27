/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 19:35:16 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/16 13:50:30 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_sim	*sim;
	t_parse	parsing;

	if (ac == 1)
		return (print_error("Not enough arguments\n"));
	if (pre_parse(&parsing, ac, av) || check_arg_count(&parsing))
		return (1);
	sim = malloc(sizeof(t_sim));
	if (!sim)
		return (freeparse(&parsing), print_error("Memory error\n"));
	memset(sim, 0, sizeof(*sim));
	if (parse(sim, &parsing))
		return (free(sim), 1);
	ini_sim(sim);
	start_simulation(sim);
	freeall_exit(sim, 0);
	return (0);
}
