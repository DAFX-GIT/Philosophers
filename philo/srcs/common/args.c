/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
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

/// @brief Writes msg to stderr and returns 1,
/// so callers can write `return (print_error("..."));`.
int	print_error(char *msg)
{
	ssize_t	ret;

	ret = write(2, msg, ft_strlen(msg));
	(void)ret;
	return (1);
}

void	freeparse(t_parse *parsing)
{
	int	i;

	if (!parsing->arg)
		return ;
	i = 0;
	while (parsing->arg[i])
		free(parsing->arg[i++]);
	free(parsing->arg);
}

int	check_arg_count(t_parse *parsing)
{
	if (parsing->arg_count > 5)
	{
		freeparse(parsing);
		return (print_error("Too many arguments\n"));
	}
	if (parsing->arg_count < 4)
	{
		freeparse(parsing);
		return (print_error("Not enough arguments\n"));
	}
	return (0);
}

/// @brief Accepts both `./philo 5 800 200 200` and `./philo "5 800 200 200"`
/// by joining every argument into one string and splitting it on spaces.
int	pre_parse(t_parse *parsing, int ac, char **av)
{
	int		i;
	char	*str;

	if (ac > 2)
		str = ft_strjoinall(av + 1, NULL);
	else
		str = av[1];
	if (!str)
		return (print_error("Memory error\n"));
	parsing->arg = ft_split(str, ' ');
	if (ac > 2)
		free(str);
	if (!parsing->arg)
		return (print_error("Memory error\n"));
	i = 0;
	while (parsing->arg[i])
		i++;
	parsing->arg_count = i;
	return (0);
}
