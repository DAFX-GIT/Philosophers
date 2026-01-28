/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:29:59 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/26 17:57:05 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(MODE_BONUS)
# include "philo_bonus.h"
#else
# include "philo.h"
#endif

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

char	*ft_strjoinall(char **av, char	*res)
{
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

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		len;
	int		sign;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		sign = 1;
		nb = -nb;
	}
	len = nb_len(nb) + sign;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- > sign)
	{
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}