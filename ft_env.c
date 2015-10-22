/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/29 16:00:39 by vroche            #+#    #+#             */
/*   Updated: 2015/10/14 16:50:29 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_usage_env(char c)
{
	ft_dprintf(2, "env: illegal option -- %c\n", c);
	ft_putstr_fd("usage: env [-i] [name=value ...] \
[utility [argument ...]]\n", 2);
}

static void	ft_env_part(t_sh1 *sh, char **environ, char **av)
{
	char	**envi;

	envi = (char **)malloc(sizeof(char *) * BUFF_ENV);
	while (*av && **av == '-')
	{
		if (ft_strcmp(*av, "-i"))
			return (ft_usage_env(*(*av + 1)));
		environ = envi;
		av++;
	}
	if (environ == envi)
	{
		while (*av && strchr(*av, '='))
		{
			*envi = *av++;
			envi++;
		}
		*envi = NULL;
	}
	if (*av)
		ft_execve(sh, environ, av);
}

void		ft_env(t_sh1 *sh, char **av)
{
	char	**environ;
	int		i;

	i = 0;
	av++;
	environ = sh->environ;
	if (!*av)
	{
		environ = sh->environ;
		while (*environ)
			ft_printf("%s\n", *environ++);
		return ;
	}
	ft_env_part(sh, environ, av);
}
