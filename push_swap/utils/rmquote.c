/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 09:00:35 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 16:03:56 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	is_split(char **split, int j)
{
	int	k;

	k = 0;
	while (split[j][k])
	{
		if ((split[j][k] == '-' || split[j][k] == '+'))
			k++;
		if (!ft_isdigit(split[j][k]))
			return (write(2, "error\n", 6), free(split), exit(1));
		k++;
	}
}
void	isdoublequoted(t_stack **a, char **av)
{
	int		i;
	int		j;
	int		n;
	char	**split;

	i = 1;
	while (av[i])
	{
		split = ft_split(av[i], ' ');
		j = 0;
		while (split[j])
		{
			if (is_flags(split[j]))
			{
				j++;
				continue ;
			}
			is_split(split, j);
			n = ft_atoi(split[j]);
			ft_stackadd_back(a, ft_stacknew(n));
			j++;
		}
		free(split);
		i++;
	}
}
