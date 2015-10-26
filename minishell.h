/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 14:15:37 by vroche            #+#    #+#             */
/*   Updated: 2015/10/26 14:37:15 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define BUFF_ENV 1024

typedef struct	s_sh1
{
	char		**environ;
}				t_sh1;

void			ft_cd(t_sh1 *sh, char **av);

void			ft_env(t_sh1 *sh, char **av);

int				ft_execve(t_sh1 *sh, char **env, char **av);

int				ft_isexec(char *str);

char			*ft_env_search(char **env, char *search);
void			ft_perror_exit(const char *str);

void			ft_setenv(t_sh1 *sh, char **av);
void			ft_unsetenv(t_sh1 *sh, char **av);

char			**ft_spacesplit(const char *s);

#endif
