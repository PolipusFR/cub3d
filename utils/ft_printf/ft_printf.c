/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:24:35 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/13 15:26:34 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	pf_putchar(int c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	else
		return (1);
}

int	solver(va_list args, const char format)
{
	int	size_printed;

	size_printed = 0;
	if (format == 'c')
		size_printed = pf_putchar(va_arg(args, int));
	else if (format == 's')
		size_printed = pf_putstr(va_arg(args, char *));
	else if (format == 'p')
		size_printed = pf_putptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		size_printed = pf_itoa(va_arg(args, int));
	else if (format == 'u')
		size_printed = pf_itoa_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		size_printed = pf_puthex(va_arg(args, unsigned int), format);
	else if (format == '%')
		size_printed = pf_putchar('%');
	return (size_printed);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		size_printed;
	int		size_cpy;
	int		i;

	size_printed = 0;
	va_start(args, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			size_cpy = size_printed;
			size_printed += solver(args, format[i + 1]);
			if (size_cpy > size_printed)
				return (-1);
			i++;
		}
		else if (pf_putchar(format[i]) < 0)
			return (-1);
		else
			size_printed++;
		i++;
	}
	return (va_end(args), size_printed);
}
