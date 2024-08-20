/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_charset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:09:57 by sben-rho          #+#    #+#             */
/*   Updated: 2024/08/20 13:09:59 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_charset(char s, const char *charset)
{
	int	i;

	i = 0;
	if (s == '\0')
		return (1);
	while (charset[i] != '\0')
	{
		if (s == charset[i])
			return (1);
		i++;
	}
	return (0);
}
