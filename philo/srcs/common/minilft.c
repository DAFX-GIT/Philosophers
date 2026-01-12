/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:29:59 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/12 19:05:11 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	nb_len(long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	while (nb > 0)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoinall(char **av)
{
	char	*res;
	int		i;
	int		j;
	int		len;

	if (!av)
		return (NULL);
	i = 0;
	len = 0;
	while (av[i])
		len += ft_strlen(av[i++]);
	res = malloc(len + i + 1);
	if (!res)
		return (NULL);
	i = 0;
	len = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
			res[len++] = av[i][j++];
		res[len++] = ' ';
		i++;
	}
	res[len] = '\0';
	return (res);
}
