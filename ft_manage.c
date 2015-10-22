/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/29 15:27:56 by vroche            #+#    #+#             */
/*   Updated: 2015/10/14 16:31:48 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_search(char **env, char *search)
{
	char	**tmp;
	int		len;

	len = ft_strlen(search);
	tmp = env;
	while (*tmp && ft_strncmp(*tmp, search, len))
		tmp++;
	if (*tmp)
		return (*tmp + len);
	return (NULL);
}

void	ft_perror_exit(const char *str)
{
	ft_dprintf(2, "Error: %s\n", str);
	exit(EXIT_FAILURE);
}
