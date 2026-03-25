/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_selector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 10:58:30 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 11:16:40 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	is_flags(char *str)
{

	return(ft_strcmp(str, "--simple") == 0 || ft_strcmp(str,
				"--medium") == 0 || ft_strcmp(str, "--complex") == 0
			|| ft_strcmp(str, "--adaptive") == 0 || ft_strcmp(str,
				"--bench") == 0);


	}


int	apply_flag_strategy(int ac, char **av, t_stack **a, t_stack **b, t_stats *ops)
{
	int	i;

	i = 1;
	while (i < ac && av[i])
	{
		if (ft_strcmp(av[i], "--simple") == 0)
			selection_sort(a, b,ops);
		else if (ft_strcmp(av[i], "--medium") == 0)
			chunk_sort(a, b, ops);
		else if (ft_strcmp(av[i], "--complex") == 0)
			radix_sort(a, b, ops);
		i ++;
	}
	return (0);
}
