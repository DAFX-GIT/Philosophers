/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:39:32 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/12 19:31:47 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void pre_parse(t_parse *parsing, int ac, char **av)
{
	int i;
	char *str;

	i = 0;
	if (ac > 2)
		str = ft_strjoinall(av + 1);
	else
		str = av[1];
	parsing->arg = ft_split(str, ' ');
	if (ac > 2)
		free(str);
	while (parsing->arg[i])
		i++;
	parsing->arg_count = i;
	if (parsing->arg_count > 5)
	{
		write(2, "Too many arguments\n", 19);
		freeparse(parsing);
		exit (1);
	}
}

int	main(int ac, char **av)
{
	t_sim	*sim;
	t_parse parsing;

	if (ac == 1)
	{
		write(2, "Not enough arguments\n", 21);
		return (1);
	}
	pre_parse(&parsing, ac, av);
	if (parsing.arg_count < 4)
	{
		write(2, "Not enough arguments\n", 21);
		freeparse(&parsing);
		return (1);
	}
	sim = malloc(sizeof(t_sim));
	memset(sim, 0, sizeof(*sim));
	parse(sim, &parsing);
	ini_sim(sim);
	born2philo(sim);
	freeall(sim, &parsing);
	return (0);
}
