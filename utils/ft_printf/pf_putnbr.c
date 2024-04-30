/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:14:08 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/13 15:26:55 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	pf_putnbr(int nb)
{
	int	size_printed;

	size_printed = 0;
	if (nb == -2147483648)
	{
		size_printed += write (1, "-2", 2);
		if (size_printed < 0)
			return (-1);
		nb = 147483648;
	}
	if (nb < 0)
	{
		size_printed += pf_putchar('-');
		if (size_printed < 0)
			return (-1);
		nb *= -1;
	}
	if (nb >= 10)
	{
		size_printed += pf_putnbr(nb / 10);
		size_printed += pf_putnbr(nb % 10);
	}
	else
		size_printed += pf_putchar(nb + 48);
	return (size_printed);
}
