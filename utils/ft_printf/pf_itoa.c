/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:09:37 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/13 15:26:45 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	pf_itoa(int nb)
{
	char	string[12];
	int		i;

	if (nb < 0)
		return (pf_negative_itoa(nb));
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

int	pf_negative_itoa(int nb)
{
	char	string[12];
	int		i;

	i = 0;
	if (nb == INT_MIN)
		return (check());
	nb *= -1;
	while (nb > 0 && i < 11)
	{
		string[i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	string[i] = '-';
	i++;
	if (pf_print_string(string, i) == -1)
		return (-1);
	return (i);
}
