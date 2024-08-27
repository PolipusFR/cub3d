/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:51:02 by lsabatie          #+#    #+#             */
/*   Updated: 2024/08/27 10:54:34 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_texture	create_texture(char *path, void *mlx)
{
	t_texture	text;

	text.img = mlx_xpm_file_to_image(mlx, path, &text.width, &text.height);
	if (!text.img)
		return (text);
	text.addr = mlx_get_data_addr(text.img, &text.bits_per_pixel,
			&text.sizeline, &text.endian);
	return (text);
}

void	clear_textures(void *mlx, t_texture *text)
{
	if (text[0].img)
		mlx_destroy_image(mlx, text[0].img);
	if (text[1].img)
		mlx_destroy_image(mlx, text[1].img);
	if (text[2].img)
		mlx_destroy_image(mlx, text[2].img);
	if (text[3].img)
		mlx_destroy_image(mlx, text[3].img);
	free(text);
}

t_texture	*get_textures(void *mlx, t_parse *parse)
{
	t_texture	*textures;

	textures = malloc(sizeof(t_texture) * 4);
	if (!textures)
		return (NULL);
	textures[0] = create_texture(parse->n, mlx);
	textures[1] = create_texture(parse->s, mlx);
	textures[2] = create_texture(parse->e, mlx);
	textures[3] = create_texture(parse->w, mlx);
	if (!textures[0].img || !textures[1].img
		|| !textures[2].img || !textures[3].img)
	{
		printf(BRED"Error\n\t"BMAG"Texture error, check it\n"RESET);
		clear_textures(mlx, textures);
		return (NULL);
	}
	return (textures);
}
