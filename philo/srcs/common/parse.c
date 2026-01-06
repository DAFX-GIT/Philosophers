/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:27:33 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/05 18:02:00 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
void	get_value(t_philo *philo, int ac, char **av)
{
	philo->nbof_philos = atoi(av[1]);
	philo->t2die = atoi(av[2]);
	philo->t2eat = atoi(av[3]);
	philo->t2sleep = atoi(av[4]);
	if (ac > 5)
		philo->musteat = atoi(av[5]);
}

int	check_len(t_philo *philo, int ac, char **av)
{
	if (nb_len(philo->nbof_philos) != (int)ft_strlen(av[1]))
		return (0);
	if (nb_len(philo->t2die) != (int)ft_strlen(av[2]))
		return (0);
	if (nb_len(philo->t2eat) != (int)ft_strlen(av[3]))
		return (0);
	if (nb_len(philo->t2sleep) != (int)ft_strlen(av[4]))
		return (0);
	if (ac > 5)
		if (nb_len(philo->musteat) != (int)ft_strlen(av[5]))
			return (0);
	return (1);
}

void	parse(t_philo *philo, int ac, char **av)
{
	if (!check_all_digit(ac, av))
		exit(((int)write(2, "Given arguments are not digits\n", 31) - 30));
	get_value(philo, ac, av);
	if (!check_len(philo, ac, av))
		exit(((int)write(2, "Given arguments are not within int range\n", 41)
				- 40));
}
