/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:31:04 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/13 15:26:41 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	pf_itoa_unsigned(unsigned int nb)
{
	char	string[12];
	int		i;

	if (nb == 0)
		return (write(1, "0", 1));
	i = 0;
	while (nb > 0 && i < 11)
	{
		string[i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	if (pf_print_string(string, i) == -1)
		return (-1);
	return (i);
}
