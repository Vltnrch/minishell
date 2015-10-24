/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/29 15:40:51 by vroche            #+#    #+#             */
/*   Updated: 2015/10/24 13:15:03 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_execve_local(char **av, char **tmp2)
{
	*tmp2 = av[0];
	if (access(*tmp2, F_OK))
	{
		ft_dprintf(2, "%s: command not found\n", av[0]);
		return (0);
	}
	return (1);
}

static int	ft_execve_final(char *tmp2, char **av, char **env)
{
	pid_t	i;
	int		stat;

	if (access(tmp2, X_OK))
	{
		ft_dprintf(2, "%s: Permission denied.\n", av[0]);
		return (0);
	}
	if (ft_isexec(tmp2) < 0)
	{
		ft_dprintf(2, "%s: is not a Mach-O binary or script.\n", av[0]);
		return (0);
	}
	i = fork();
	if (i == 0)
	{
		if ((stat = execve(tmp2, av, env)) == -1)
			ft_perror_exit("execve failed");
	}
	else
		waitpid(i, &stat, WCONTINUED);
	return (1);
}

int			ft_execve(t_sh1 *sh, char **env, char **av)
{
	char	**tmp;
	char	*tmp2;
	char	*tmp3;

	if ((*av[0] == '.' || *av[0] == '/') && !ft_execve_local(av, &tmp2))
		return (-1);
	else if (!(*av[0] == '.' || *av[0] == '/'))
	{
		if (!(tmp3 = ft_env_search(sh->environ, "PATH=")))
			return (ft_dprintf(2, "%s: command not found\n", av[0]));
		tmp = ft_strsplit(tmp3, ':');
		tmp3 = ft_strjoin("/", av[0]);
		while (*tmp)
		{
			tmp2 = ft_strjoin(*tmp, tmp3);
			free(*tmp);
			if (access(tmp2, F_OK) == 0)
				break ;
			free(tmp2);
			tmp++;
		}
		if (!*tmp)
			return (ft_dprintf(2, "%s: command not found\n", av[0]));
	}
	return (ft_execve_final(tmp2, av, env));
}
