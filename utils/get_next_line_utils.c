/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:48:30 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/13 15:26:01 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

char	*fill_string(int fd, char *buf)
{
	int		size_read;
	char	*ret;

	size_read = 1;
	ret = NULL;
	while (size_read > 0)
	{
		ret = gnl_strjoin(ret, buf);
		if (!ret)
			return (NULL);
		if (check_newline(buf))
			break ;
		size_read = read(fd, buf, BUFFER_SIZE);
		if (size_read == -1)
		{
			buf[0] = 0;
			free(ret);
			return (NULL);
		}
		buf[size_read] = 0;
	}
	return (ret);
}

int	gnl_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	gnl_strlen_buff(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

void	buffer_reset(char *buf)
{
	int	i;
	int	j;

	if (!check_newline(buf))
		return ;
	i = 0;
	j = 0;
	while (buf[i] != '\n')
		i++;
	i++;
	while (buf[i])
		buf[j++] = buf[i++];
	buf [j] = 0;
}
