/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_stategy_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:13:48 by brportos          #+#    #+#             */
/*   Updated: 2026/03/27 16:55:43 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	count_strategy_flags(int ac, char **av)
{
	int		i;
	int		j;
	int		count;
	char	**split;

	count = 0;
	i = 1;
	while (i < ac && av[i])
	{
		split = ft_split(av[i], ' ');
		j = 0;
		while (split[j])
		{
			if (ft_strcmp(split[j], "--simple") == 0 || ft_strcmp(split[j],
					"--medium") == 0 || ft_strcmp(split[j], "--complex") == 0
				|| ft_strcmp(split[j], "--adaptive") == 0)
				count++;
			j++;
		}
		free(split);
		i++;
	}
	return (count);
}

char	*find_strategy(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--simple") == 0 || ft_strcmp(argv[i],
				"--medium") == 0 || ft_strcmp(argv[i], "--complex") == 0)
			return (argv[i]);
		i++;
	}
	return (NULL);
}

void	is_bench(int argc, char **argv, t_stats *ops)
{
	int		i;
	char	*strategy;

	i = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--bench") == 0)
		{
			strategy = find_strategy(argc, argv);
			print_bench(strategy, ops);
			return ;
		}
		i++;
	}
}

void	is_strategy(char *str, t_stats *ops)
{
	if (ft_strcmp(str, "--simple") == 0)
		ft_printf(2, "[bench] strategy: Simple / O(n²)\n");
	else if (ft_strcmp(str, "--medium") == 0)
		ft_printf(2, "[bench] strategy: Medium / O(n√n)\n");
	else if (ft_strcmp(str, "--complex") == 0)
		ft_printf(2, "[bench] strategy: Complex / O(nlogn)\n");
	else if (ops->disorder < 0.2)
		ft_printf(2, "[bench] strategy: Simple / O(n²)\n");
	else if (ops->disorder >= 0.2 && ops->disorder < 0.5)
		ft_printf(2, "[bench] strategy: Medium / O(n√n)\n");
	else
		ft_printf(2, "[bench] strategy: Complex / O(nlogn)\n");
}
