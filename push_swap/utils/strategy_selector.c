/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_selector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 10:58:30 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 16:17:39 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	is_flags(char *str)
{
	return (ft_strcmp(str, "--simple") == 0 || ft_strcmp(str, "--medium") == 0
		|| ft_strcmp(str, "--complex") == 0 || ft_strcmp(str, "--adaptive") == 0
		|| ft_strcmp(str, "--bench") == 0);
}

int	apply_flag_strategy(int ac, char **av, t_stack **a, t_stack **b,
		t_stats *ops)
{
	int		i;
	char	**split;
	int		j;

	i = 1;
	while (i < ac && av[i])
	{
		split = ft_split(av[i], ' ');
		j = 0;
		while (split[j])
		{
			if (ft_strcmp(split[j], "--simple") == 0)
				selection_sort(a, b, ops);
			else if (ft_strcmp(split[j], "--medium") == 0)
				chunk_sort(a, b, ops);
			else if (ft_strcmp(split[j], "--complex") == 0)
				radix_sort(a, b, ops);
			j++;
		}
		free(split);
		i++;
	}
	return (0);
}
