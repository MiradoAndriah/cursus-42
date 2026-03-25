/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 09:00:35 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 11:23:12 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	isdoublequoted(t_stack **a, char **av)
{
	int		i;
	int		j;
	int		n;
	char	**split;

	split = ft_split(av[1], ' ');
	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (j == 0 && (split[i][j] == '-' || split[i][j] == '+'))
				j++;
			if (!ft_isdigit(split[i][j]))
			{
				write(2, "error\n", 6);
				exit(1);
			}
			j++;
		}
		n = ft_atoi(split[i]);
		ft_stackadd_back(a, ft_stacknew(n));
		i++;
	}
}

void	isunquoted(t_stack **a, int ac, char **av)
{
	int	n;
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		if (is_flags(av[i]))
			{
                i++;
                continue;
            }
		j = 0;
		while (av[i][j])
		{
			if (j == 0 && (av[i][j] == '-' || av[i][j] == '+'))
				j++;
			if (!ft_isdigit(av[i][j]))
			{
				write(2, "error\n", 6);
				exit(1);
			}
			j++;
		}
		n = ft_atoi(av[i]);
		ft_stackadd_back(a, ft_stacknew(n));
		i++;
	}
}
