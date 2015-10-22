/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/29 15:34:55 by vroche            #+#    #+#             */
/*   Updated: 2015/10/14 18:24:11 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_setenv_put(t_sh1 *sh, char **av)
{
	char	**tmp;
	char	*tmp2;
	int		i;

	tmp = sh->environ;
	tmp2 = ft_strjoin(av[1], "=");
	while (*tmp && ft_strncmp(*tmp, tmp2, ft_strlen(tmp2)) != 0)
		tmp++;
	i = 1;
	if (*tmp)
		free(*tmp);
	else
		i = 0;
	*tmp = tmp2;
	if (av[2])
	{
		*tmp = ft_strjoin(*tmp, av[2]);
		free(tmp2);
	}
	if (i == 0)
		*(++tmp) = NULL;
}

void		ft_setenv(t_sh1 *sh, char **av)
{
	if (!av[1])
	{
		free(av[0]);
		ft_env(sh, av);
	}
	else if (av[3] != NULL)
		ft_dprintf(2, "setenv: Too many arguments.\n");
	else
		ft_setenv_put(sh, av);
}

static void	ft_unsetenv_rm(t_sh1 *sh, char **av)
{
	char	**tmp;
	char	**tmp2;
	char	*tmp3;
	int		i;

	while (*av)
	{
		tmp = sh->environ;
		tmp3 = ft_strjoin(*av, "=");
		i = ft_strlen(tmp3);
		while (*tmp != NULL && ft_strncmp(*tmp, tmp3, i) != 0)
			tmp++;
		if (*tmp != NULL)
		{
			free(*tmp);
			tmp2 = tmp;
			tmp++;
			while ((*tmp2++ = *tmp++) != NULL)
				;
		}
		free(tmp3);
		av++;
	}
}

void		ft_unsetenv(t_sh1 *sh, char **av)
{
	av++;
	if (*av)
		ft_unsetenv_rm(sh, av);
	else
		ft_dprintf(2, "unsetenv: Too few arguments.\n");
}
