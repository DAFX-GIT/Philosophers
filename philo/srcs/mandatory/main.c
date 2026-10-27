/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:39:32 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/25 12:23:31 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_sim	*sim;
	t_parse	parsing;
	int		status;

	if (ac == 1)
		return (print_error("Not enough arguments\n"));
	if (pre_parse(&parsing, ac, av) || check_arg_count(&parsing))
		return (1);
	sim = malloc(sizeof(t_sim));
	if (!sim)
		return (freeparse(&parsing), print_error("Memory error\n"));
	memset(sim, 0, sizeof(*sim));
	if (parse(sim, &parsing))
		return (freeall(sim), 1);
	if (ini_sim(sim))
		return (1);
	status = start_simulation(sim);
	if (status)
		print_error("Thread error\n");
	destroy_mutexes(sim);
	freeall(sim);
	return (status);
}
