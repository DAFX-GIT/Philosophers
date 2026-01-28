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

int	check_arg_count(t_parse *parsing)
{
	if (parsing->arg_count > 5)
	{
		write(2, "Too many arguments\n", 19);
		freeparse(parsing);
		return (1);
	}
	if (parsing->arg_count < 4)
	{
		write(2, "Not enough arguments\n", 21);
		freeparse(parsing);
		return (1);
	}
	return (0);
}

int	pre_parse(t_parse *parsing, int ac, char **av)
{
	int		i;
	char	*str;

	i = 0;
	if (ac > 2)
		str = ft_strjoinall(av + 1, NULL);
	else
		str = av[1];
	if (!str)
		return (write(2, "Memory error\n", 13) - 12);
	parsing->arg = ft_split(str, ' ');
	if (!parsing->arg)
	{
		free(str);
		return (write(2, "Memory error\n", 13) - 12);
	}
	if (ac > 2)
		free(str);
	while (parsing->arg[i])
		i++;
	parsing->arg_count = i;
	return (0);
}

int	main(int ac, char **av)
{
	t_sim	*sim;
	t_parse	parsing;

	if (ac == 1)
		return (write(2, "Not enough arguments\n", 21) - 20);
	if (pre_parse(&parsing, ac, av))
		return (1);
	if (check_arg_count(&parsing))
		return (1);
	sim = malloc(sizeof(t_sim));
	if (!sim)
		return (write(2, "Memory error\n", 13) - 12);
	memset(sim, 0, sizeof(*sim));
	if (parse(sim, &parsing))
	{
		freeall(sim);
		return (1);
	}
	if (ini_sim(sim))
		return (1);
	usleep(2000);
	if (born2philo_ma(sim))
		write(2, "Thread error\n", 13);
	freeall(sim);
	return (0);
}
