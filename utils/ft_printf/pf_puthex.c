/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:55:18 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/13 15:26:50 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	pf_print_hex_string(char *hex_string, int size)
{
	while (size--)
	{
		if (write(1, &hex_string[size], 1) == -1)
			return (-1);
	}
	return (1);
}

int	pf_puthex(unsigned int nb, const char format)
{
	char	*hex_digits;
	char	hex_string[9];
	int		i;
	int		j;

	hex_digits = "0123456789abcdef";
	if (nb == 0)
		return (write(1, "0", 1));
	i = 0;
	while (nb > 0)
	{
		hex_string[i] = hex_digits[nb % 16];
		nb /= 16;
		i++;
	}
	if (format == 'X')
	{
		j = -1;
		while (j++ < i)
			hex_string[j] = pf_toupper(hex_string[j]);
	}
	if (pf_print_hex_string(hex_string, i) == -1)
		return (-1);
	return (i);
}
