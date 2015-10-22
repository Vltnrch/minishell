/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 14:15:26 by vroche            #+#    #+#             */
/*   Updated: 2015/10/22 19:35:35 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exit(char **av)
{
	char	*tmp;

	if (av[1] && !av[2])
	{
		tmp = av[1];
		while (*tmp)
			if (!ft_isdigit(*tmp++))
				return (ft_printf("exit: Expression Syntax.\n"));
	}
	else if (av[1] && av[2])
		return (ft_printf("exit: Expression Syntax.\n"));
	ft_printf("exit\n");
	exit(av[1] ? ft_atoi(av[1]) % 256 : 0);
}


static void	manage_line(t_sh1 *sh)
{
	char	*line;
	char	**av;

	while (!(line = readline("$> ")))
	{
		av = ft_spacesplit(line);
		if (*av == NULL)
			;
		else if (ft_strcmp(av[0], "exit") == 0)
			ft_exit(av);
		else if (ft_strcmp(av[0], "cd") == 0)
			ft_cd(sh, av);
		else if (ft_strcmp(av[0], "unsetenv") == 0)
			ft_unsetenv(sh, av);
		else if (ft_strcmp(av[0], "setenv") == 0)
			ft_setenv(sh, av);
		else if (ft_strcmp(av[0], "env") == 0)
			ft_env(sh, av);
		else
			ft_execve(sh, sh->environ, av);
		free(line);
	}
}

static void	ft_init_shstruct(t_sh1 *sh, char **environ)
{
	char	**tmp;
	char	*dest[4];
	char	buf[256];

	if (!(sh->environ = (char **)malloc((BUFF_ENV) * sizeof(char *))))
		return ;
	tmp = sh->environ;
	while (*environ != NULL)
		*tmp++ = ft_strdup(*environ++);
	*tmp = NULL;
	dest[1] = ft_strdup("PWD");
	dest[2] = getcwd(buf, 256);
	dest[3] = NULL;
	ft_setenv(sh, dest);
	free(dest[1]);
}

int			main(int ac, char **av, char **environ)
{
	t_sh1	sh;

	ac = 0;
	av = 0;
	ft_init_shstruct(&sh, environ);
	manage_line(&sh);
	return (0);
}
