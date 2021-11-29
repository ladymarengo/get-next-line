/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_new.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:31:04 by nsamoilo          #+#    #+#             */
/*   Updated: 2021/11/26 20:26:01 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	save_buffer(char **saved, char *buffer)
{
	char	*temp;

	if (!(*saved) || ft_strlen(*saved) == 0)
	{
		*saved = ft_strdup(buffer);
		if (!(*saved))
			return (-1);
	}
	else
	{
		temp = ft_strjoin(*saved, buffer);
		if (!temp)
			return (-1);
		free(*saved);
		*saved = temp;
	}
	return (1);
}

int	create_line(char **saved, char **line, int state)
{
	char	*temp;

	if ((!(*saved) || ft_strlen(*saved) == 0) && state == 0)
		return (2);
	if (find_newline(*saved) == -1)
	{
		if (state == 1)
			return (0);
		*line = ft_strdup(*saved);
		ft_strdel(saved);
		if (!line)
			return (-1);
		return (1);
	}
	*line = ft_strsub(*saved, 0, find_newline(*saved));
	temp = ft_strsub(*saved, find_newline(*saved) + 1, ft_strlen(*saved));
	free(*saved);
	*saved = temp;
	if (!line || !saved)
	{
		if (!line)
			free(*saved);
		return (-1);
	}
	return (1);
}

int	read_fd(const int fd, char **saved)
{
	char	*buffer;
	int		bytes;
	int		result;

	buffer = ft_strnew(BUFF_SIZE + 1);
	bytes = read(fd, buffer, BUFF_SIZE);
	if (bytes == -1)
	{
		free(buffer);
		return (-1);
	}
	buffer[bytes] = '\0';
	result = save_buffer(saved, buffer);
	free(buffer);
	if (result == -1)
		return (-1);
	else if (bytes == 0)
		return (0);
	else
		return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*saved[MAX_FD];
	int			state;
	int			created;

	created = 0;
	if (BUFF_SIZE <= 0 || fd < 0 || line == NULL)
		return (-1);
	while (created == 0)
	{
		state = read_fd(fd, &(saved[fd]));
		if (state == -1)
			return (-1);
		created = create_line(&(saved[fd]), line, state);
		if (created == 2)
		{
			free(saved[fd]);
			saved[fd] = NULL;
			return (0);
		}
		else if (created == -1 || created == 1)
			return (created);
	}
	return (1);
}
