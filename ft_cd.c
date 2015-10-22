/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/29 15:41:59 by vroche            #+#    #+#             */
/*   Updated: 2015/10/14 16:41:57 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_part(t_sh1 *sh, char **av)
{
	char	*dest[4];
	char	buf[256];

	if (access(av[1], F_OK) == 0)
	{
		if (access(av[1], X_OK) != 0)
		{
			ft_dprintf(2, "%s: permission denied: %s\n", av[0], av[1]);
			return ;
		}
		chdir(av[1]);
		dest[1] = ft_strdup("PWD");
		dest[2] = getcwd(buf, 256);
		dest[3] = NULL;
		ft_setenv(sh, dest);
		free(dest[1]);
	}
	else
		ft_dprintf(2, "%s: no such file or directory: %s\n", av[0], av[1]);
}

void		ft_cd(t_sh1 *sh, char **av)
{
	if (!av[1])
	{
		if (!(av[1] = ft_env_search(sh->environ, "HOME=")))
		{
			ft_dprintf(2, "cd: No home directory\n");
			return ;
		}
	}
	else if (av[2])
	{
		ft_dprintf(2, "cd: Too many arguments.\n");
		return ;
	}
	ft_cd_part(sh, av);
}
