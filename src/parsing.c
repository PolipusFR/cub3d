#include "../includes/cub3D.h"
#include <stdio.h>


/*
		typedef struct s_parse
		{
			char			**map; MAP (attention au `orientation` a replace  par 0
			double			player[2]; Coord de pop
			unsigned long	color_f; Color Floor
			unsigned long	color_c; Color Sol
			char			orientation; Orientation
			char			*n; Texture
			char			*s; Texture
			char			*e; Texture
			char			*w; Texture
		}				t_parse;
 */

/*
 *
 * NO | SO | WE | EA | F | C

 NO | SO | WE | EA --> Chemin vers les texture
 	Couleur xxx,xxx,xxx | RGB

	Tout est obligatoire, a faire dans l'odre de lecture en vrai
	Une ligne une info. a part si elle est vide

 	Faire un RM char jusqu'a une un des char en string en param

Get la ligne, chopper l'indentifiant, call la fonction approprier, si identifiant non reconnue toz
 	 Si ligne vide, beh osef

	Pour les couleur :
		rm jusqu'a '0123456789', Tout ce qui est apres la string est return pour etude,
		Atoi de mes 3 merde
		Si un des 3 nombre est au dessus de 255, toz
		Check FDF pour l'hexa couleur

	Pour la map :
 		On vois sa plus tard akhy | 0,1,N,W,E,S

	Pour orrientation, si on essaye de l'assigner or qu'il est deja assigner sa degage

	Pour les coord rien de complexe, c'est coller a l'orientation

"NO", "SO", "WE", "EA", "F", "C"- All identifiant
01NWES.0123456789 --> RECHERCHE d'identifiant jusqua'a un de ces char

			"NO", "SO", "WE", "EA", "F", "C"	"NSWEFC"

 */

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

void	init_struct(t_parse *game)
{
	game->map = NULL;
	game->player[0] = -1;
	game->player[1] = -1;
	game->color_c = 0;
	game->color_f = 0;
	game->orientation = '\0';
	game->n = NULL;
	game->s = NULL;
	game->e = NULL;
	game->w = NULL;
}

char	*is_full_game(t_parse *game)
{
	if (game->color_f == 0 || game->color_c == 0)
		return ("Missing colors");
	if (!game->w || !game->s || !game->e || !game->n)
		return ("Missing Texture");
	if (game->orientation == '\0' || (game->player[0] == -1 && game->player[1] == -1))
		return ("Missing Spawn point");
	return (NULL);
}

void	print_struct(t_parse *game)
{
	printf(BRED"~~~~~~Game~~~~~~"RESET"\n");
	if (game->n != NULL)
		printf(BMAG"Texture :"RESET"\t"BYEL"N:'%s'\n", game->n);
	else
		printf(BMAG"Texture :"RESET"\t"BRED"N:'%s'\n", game->n);
	if (game->s != NULL)
		printf("\t\t"BYEL"S:'%s'\n"RESET, game->s);
	else
		printf("\t\t"BRED"S:'%s'\n"RESET, game->s);
	if (game->w != NULL)
		printf("\t\t"BYEL"W:'%s'\n"RESET, game->w);
	else
		printf("\t\t"BRED"W:'%s'\n"RESET, game->w);
	if (game->e != NULL)
		printf("\t\t"BYEL"E:'%s'\n\n"RESET, game->e);
	else
		printf("\t\t"BRED"E:'%s'\n\n"RESET, game->e);

	printf(BMAG"Orientation :"RESET"\t"BYEL"'%c'\n\n"RESET, game->orientation);
	printf(BMAG"Color :"RESET"\t\t"BYEL"Floor :'%lu'\n"RESET, game->color_f);
	printf("\t\t"BYEL"Sky :'%lu'\n\n"RESET, game->color_c);
	printf(BMAG"Spawn :"RESET"\t\t"BYEL"'%.2lf' | '%.2lf'\n"RESET, game->player[0], game->player[1]);
}

int	check_file(char *path)
{
	if (!path || path[0] == '\0')
		return (1);
	if (ft_strlen(path) <= 4)
		return (1);
	if (ft_strnstr(path, ".cub", ft_strlen(path)) == NULL)
		return (1);
	return (0);
}

char	*get_id(char *line)
{
	int	i;
	int	save;

	i = 0;
	while (is_charset(line[i], "\f\t\n\r\v ") == 1 && line[i] != '\0')
		i++;
	save = i;
	while (is_charset(line[i], "\f\t\n\r\v ") == 0 && line[i] != '\0')
		i++;
	return (ft_substr(line, save, i - save));
}

int	texture_case(char *line, char *id, t_parse *game)
{
	char	*newline;
	int		i;

	newline = remove_whitespace(line, ".0123456789");
	i = 2;

	if (newline[i] != '.' || newline[i + 1] != '/')
		return (1);
	if (ft_strcmp(id, "NO") == 0)
	{
		game->n = ft_substr(newline, 2, ft_strlen(line) - 4);
		return (0);
	}
	if (ft_strcmp(id, "SO") == 0)
	{
		game->s = ft_substr(newline, 2, ft_strlen(line) - 4);
		return (0);
	}
	if (ft_strcmp(id, "WE") == 0)
	{
		game->w = ft_substr(newline, 2, ft_strlen(line) - 4);
		return (0);
	}
	if (ft_strcmp(id, "EA") == 0)
	{
		game->e = ft_substr(newline, 2, ft_strlen(line) - 4);
		return (0);
	}
	return (0);
}

char	*apply_case(char *line, char *id, t_parse *game)
{
	if (ft_strcmp(id, "NO") == 0 || ft_strcmp(id, "SO") == 0)
		texture_case(line, id, game);
	else if (ft_strcmp(id, "WE") == 0 || ft_strcmp(id, "EA") == 0)
		texture_case(line, id, game);
	else if (ft_strcmp(id, "F") == 0)
		printf(BGRN"Value declared is F"RESET);
	else if (ft_strcmp(id, "C") == 0)
		printf(BGRN"Value declared is C"RESET);
	else
		return ("Invalid identifier\n");
	return (NULL);
}

char	*get_value(t_parse *game, int fd)
{
	char	*line;
	char	*id;
	char	*status;

	line = get_next_line(fd);
	while (line != NULL && line[0] == '\n')
		line = get_next_line(fd);
	while (line != NULL)
	{
		id = get_id(line);
		status = apply_case(line, id, game);
		free(id);
		if (status != NULL && is_full_game(game) != NULL)
			return (status);
		else if (status != NULL && is_full_game(game) == NULL)
			printf("Apply map parsing");
		line = get_next_line(fd);
		while (line != NULL && line[0] == '\n')
			line = get_next_line(fd);
	}
	return (NULL);
}

char	*parsing(char *path)
{
	int		fd;
	t_parse	game;
	char	*status;

	init_struct(&game);
	if (check_file(path) == 1)
		return ("--> Invalid File, need a .cub file.");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return ("Invalid file or permission.");
	status = get_value(&game, fd);
	if (status != NULL)
		return (status);
	close(fd);
	print_struct(&game);
	return (NULL);
}