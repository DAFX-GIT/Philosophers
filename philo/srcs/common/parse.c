/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
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

int	check_musteat(t_parse *parsing)
{
	if (parsing->arg_count == 5 && parsing->arg[4][0] == '0')
	{
		write(2, "0 All philosophers have eaten their fill\n", 41);
		freeparse(parsing);
		return (1);
	}
	return (0);
}

int	check_all_digit(int ac, char **av)
{
	int	j;
	int	i;

	j = 0;
	while (j < ac)
	{
		i = 0;
		while (av[j][i])
		{
			if (!(av[j][i] >= '0' && av[j][i] <= '9'))
			{
				write(2, "Given arguments are not (positive) digits\n", 42);
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}

void	get_value(t_sim *sim, int ac, char **av)
{
	sim->nbof_philos = ft_atoi(av[1 - 1]);
	sim->t2die = ft_atoi(av[2 - 1]);
	sim->t2eat = ft_atoi(av[3 - 1]);
	sim->t2sleep = ft_atoi(av[4 - 1]);
	if (ac > 5 - 1)
		sim->musteat = ft_atoi(av[5 - 1]);
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

int	parse(t_sim *sim, t_parse *parsing)
{
	int		ac;
	char	**av;

	ac = parsing->arg_count;
	av = parsing->arg;
	if (!check_all_digit(ac, av))
	{
		freeparse(parsing);
		return (1);
	}
	get_value(sim, ac, av);
	if (!check_len(sim, ac, av))
	{
		write(2, "Given arguments are not within int range\n", 41);
		freeparse(parsing);
		return (1);
	}
	if (check_musteat(parsing))
		return (1);
	freeparse(parsing);
	if (sim->nbof_philos == 0)
		return (write(2, "No philosophers\n", 16) - 15);
	return (0);
}

/* if (sim->nbof_philos > 200)
		return (write(2, "Too many philosophers\n", 22) - 21); */