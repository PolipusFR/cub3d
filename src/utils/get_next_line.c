/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:48:37 by lsabatie          #+#    #+#             */
/*   Updated: 2024/08/29 04:52:47 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;

	len_s1 = gnl_strlen(s1);
	len_s2 = gnl_strlen_buff(s2);
	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
	{
		return (NULL);
	}
	i = -1;
	j = 0;
	while (++i < len_s1)
		str[i] = s1[i];
	while (j < len_s2)
		str[i++] = s2[j++];
	str[len_s1 + len_s2] = '\0';
	free(s1);
	return (str);
}

int	check_newline(char *buf)
{
	int	i;

	if (!buf)
		return (0);
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char			*ret;
	static char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = fill_string(fd, buf);
	if (!ret)
		return (NULL);
	if (gnl_strlen(ret) == 0)
	{
		free(ret);
		return (NULL);
	}
	buffer_reset(buf);
	return (ret);
}
