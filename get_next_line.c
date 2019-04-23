/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:48:17 by gdalard           #+#    #+#             */
/*   Updated: 2019/04/23 21:02:59 by gdalard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static int	process(char **tab, char *tmp, char **line)
{
	char	*buf2;

	if (tmp)
	{
		if (!(*line = ft_strsub(*tab, 0, tmp - *tab)))
			return (-1);
		buf2 = *tab;
		if (!(*tab = ft_strdup(tmp + 1)))
		{
			ft_strdel(&buf2);
			return (-1);
		}
		ft_strdel(&buf2);
		return (1);
	}
	if (!**tab)
		return (0);
	*line = ft_strdup(*tab);
	ft_strdel(tab);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*tab[OPEN_MAX];
	char		buf[BUFF_SIZE + 1];
	int			size;
	char		*tmp;
	char		*buf2;

	size = 0;
	if (fd < 0 || line == NULL || (!tab[fd] && !(tab[fd] = ft_strnew(0))))
		return (-1);
	while (!(tmp = ft_strchr(tab[fd], '\n'))
			&& (size = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[size] = '\0';
		buf2 = tab[fd];
		if (!(tab[fd] = ft_strjoin(tab[fd], buf)))
		{
			ft_strdel(&buf2);
			return (-1);
		}
		ft_strdel(&buf2);
	}
	if (size == -1)
		return (-1);
	return (process(&tab[fd], tmp, line));
}
