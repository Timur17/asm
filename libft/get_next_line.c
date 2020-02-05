/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtorwold <wtorwold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:50:23 by wtorwold          #+#    #+#             */
/*   Updated: 2019/12/02 23:57:31 by wtorwold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_search(char **line, char *temp, int *f)
{
	size_t		start;
	char		*leak;
	int			end;

	end = 0;
	start = 0;
	while (temp[end] != '\0' && temp[end] != '\n')
		end++;
	if (temp[end] == '\n')
	{
		*line = ft_strsub(temp, 0, end);
		start = ft_strlen(temp);
		leak = ft_strsub(temp, end + 1, start - (size_t)end - 1);
		free(temp);
		temp = leak;
		*f = (-3);
		return (temp);
	}
	return (temp);
}

static char			*ft_read(int fd, char **line, char *temp, int *f)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;
	char		*leak;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		leak = ft_strjoin(temp, buf);
		free(temp);
		temp = leak;
		temp = ft_search(line, temp, f);
		if (*f == -3)
			return (temp);
	}
	*f = ret;
	return (temp);
}

int					get_next_line(int fd, char **line)
{
	int				f;
	static char		*temp[110000];

	ERROR(line == NULL || BUFF_SIZE <= 0 || fd < 0
			|| (fd >= 11000) || (read(fd, NULL, 0) < 0));
	if (temp[fd] == NULL)
		temp[fd] = (char *)ft_memalloc(1);
	if ((f = (int)ft_strlen(temp[fd])) > 0)
	{
		temp[fd] = ft_search(line, temp[fd], &f);
		if (f == -3)
			return (1);
	}
	f = 0;
	temp[fd] = ft_read(fd, line, temp[fd], &f);
	if (f == -3)
		return (1);
	if (f == 0 && (int)ft_strlen(temp[fd]) > 0)
	{
		*line = ft_strjoin("", temp[fd]);
		free(temp[fd]);
		temp[fd] = NULL;
		return (1);
	}
	return (f == 0 ? 0 : -1);
}
