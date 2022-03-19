/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:37:52 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/19 18:13:42 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (ft_putstr("The program need 4 or 5 arguments to work\n"), 1);
	while (++i < ac)
	{
		if (!is_arg_digit(av[i]))
			return (ft_putstr("Arguments must be numbers\n"), 1);
	}
	return (0);
}
