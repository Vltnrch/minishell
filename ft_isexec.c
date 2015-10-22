/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 14:32:12 by vroche            #+#    #+#             */
/*   Updated: 2015/10/14 16:49:05 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** fonction to detect if file is Mach-O binary-64 with magic number
** open file, read 4 first bytes, compare and close.
** CA FE BA BE	Java class file, Mach-O Fat Binary
** BE BA FE CA	Java class file, Mach-O Fat Binary (reverse)
** FE ED FA CF	Mach-O binary (64-bit)
** CF FA ED FE	Mach-O binary (reverse byte ordering scheme, 64-bit)
** Thanks wiki !
*/

#include "minishell.h"
#include "stdio.h"

int	ft_isexec(char *str)
{
	int				fd;
	unsigned int	buf;
	int				rtn;
	char			*scr;

	rtn = 0;
	if ((fd = open(str, O_RDONLY)) == -1)
		rtn = -1;
	if (rtn == 0 && read(fd, &buf, sizeof(unsigned int)) \
					!= sizeof(unsigned int))
		rtn = -2;
	if (rtn == 0 && !(buf == 0xCFFAEDFE || buf == 0xFEEDFACF \
					|| buf == 0xCAFEBABE || buf == 0xBEBAFECA))
		rtn = -3;
	scr = (char *)&buf;
	if (rtn == -3 && *scr == '#' && *(scr + 1) == '!')
		rtn = 0;
	close(fd);
	return (rtn);
}
