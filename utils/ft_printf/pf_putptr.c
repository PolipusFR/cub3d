/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:14:25 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/13 15:26:59 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_printed_size(uintptr_t nb)
{
	int	size_printed;

	size_printed = 0;
	while (nb != 0)
	{
		size_printed++;
		nb = nb / 16;
	}
	return (size_printed);
}

void	print_ptr(uintptr_t nb)
{
	if (nb >= 16)
	{
		print_ptr(nb / 16);
		print_ptr(nb % 16);
	}
	else
	{
		if (nb <= 9)
			pf_putchar(nb + '0');
		else
			pf_putchar(nb - 10 + 'a');
	}
}

int	pf_putptr(unsigned long long ptr)
{
	int	size_printed;

	size_printed = 0;
	size_printed += write (1, "0x", 2);
	if (size_printed < 0)
		return (-1);
	if (ptr == 0)
		size_printed += pf_putchar('0');
	else
	{
		print_ptr(ptr);
		size_printed += get_printed_size(ptr);
	}
	return (size_printed);
}
