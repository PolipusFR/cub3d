/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itoa_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:53:04 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/13 15:26:43 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

char	*pf_reverse(char *str, int len_str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = len_str - 1;
	tmp = 0;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	str[len_str] = '\0';
	return (str);
}

int	pf_print_string(char *string, int size)
{
	string = pf_reverse(string, size);
	return (pf_putstr(string));
}

int	check(void)
{
	if (pf_putstr("-2147483648") == -1)
		return (-1);
	return (11);
}
