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

int	is_flags(char *str)
{
	return (ft_strcmp(str, "--simple") == 0 || ft_strcmp(str, "--medium") == 0
		|| ft_strcmp(str, "--complex") == 0 || ft_strcmp(str, "--adaptive") == 0
		|| ft_strcmp(str, "--bench") == 0);
}

void	is_split(t_stack **a, char **split, int j)
{
	int	k;

	k = 0;
	while (split[j][k])
	{
		if ((split[j][k] == '-' || split[j][k] == '+'))
			k++;
		if (!ft_isdigit(split[j][k]))
		{
			free_split(split);
			ft_stackclear(a);
			write(2, "Error\n", 6);
			exit(1);
		}
		k++;
	}
}

static void	parse_and_push(t_stack **a, char **split, int *is_error)
{
	int	j;
	int	n;

	j = 0;
	while (split[j])
	{
		if (is_flags(split[j]))
		{
			j++;
			continue ;
		}
		is_split(a, split, j);
		n = ft_atoi(split[j], is_error);
		if (*is_error == 1)
			return (ft_stackclear(a), free_split(split), exit(1));
		ft_stackadd_back(a, ft_stacknew(n));
		j++;
	}
}

void	isdoublequoted(t_stack **a, char **av)
{
	int		i;
	char	**split;
	int		is_error;

	is_error = 0;
	i = 1;
	while (av[i])
	{
		split = ft_split(av[i], ' ');
		parse_and_push(a, split, &is_error);
		free_split(split);
		i++;
	}
}
