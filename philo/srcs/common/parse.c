/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:27:33 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/14 17:12:21 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(MODE_BONUS)
# include "philo_bonus.h"
#else
# include "philo.h"
#endif

int	check_all_digit(int ac, char **av)
{
	int	j;
	int	i;

	j = 1;
	while (j < ac)
	{
		i = 0;
		while (av[j][i])
		{
			if (!(av[j][i] >= '0' && av[j][i] <= '9'))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

void	get_value(t_sim *sim, int ac, char **av)
{
	sim->nbof_philos = atoi(av[1 - 1]);
	sim->t2die = atoi(av[2 - 1]);
	sim->t2eat = atoi(av[3 - 1]);
	sim->t2sleep = atoi(av[4 - 1]);
	if (ac > 5 - 1)
		sim->musteat = atoi(av[5 - 1]);
}

int	check_len(t_sim *sim, int ac, char **av)
{
	if (nb_len(sim->nbof_philos) != (int)ft_strlen(av[1 - 1]))
		return (0);
	if (nb_len(sim->t2die) != (int)ft_strlen(av[2 - 1]))
		return (0);
	if (nb_len(sim->t2eat) != (int)ft_strlen(av[3 - 1]))
		return (0);
	if (nb_len(sim->t2sleep) != (int)ft_strlen(av[4 - 1]))
		return (0);
	if (ac > 5 - 1)
		if (nb_len(sim->musteat) != (int)ft_strlen(av[5 - 1]))
			return (0);
	return (1);
}

void	parse(t_sim *sim, t_parse *parsing)
{
	int		ac;
	char	**av;

	ac = parsing->arg_count;
	av = parsing->arg;
	if (!check_all_digit(ac, av))
	{
		write(2, "Given arguments are not (positive) digits\n", 42);
		freeall(sim, parsing);
		exit(1);
	}
	get_value(sim, ac, av);
	if (!check_len(sim, ac, av))
	{
		write(2, "Given arguments are not within int range\n", 41);
		freeall(sim, parsing);
		exit(1);
	}
	if (sim->nbof_philos > 200)
	{
		write(2, "Too many philosophers\n", 22);
		freeall(sim, parsing);
		exit(1);
	}
}
