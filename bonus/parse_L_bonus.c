/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_L_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:33:33 by kiyoon            #+#    #+#             */
/*   Updated: 2022/12/07 17:42:24 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

t_light	*find_cur(t_elements *element)
{
	t_light	*cur;

	cur = element->light;
	while (cur != NULL)
		cur = cur->next;
	cur = ft_malloc(sizeof(t_light));
	return (cur);
}

int	parse_l_bonus(char **buffer, t_elements *element)
{
	char	**position;
	char	**rgb;
	t_light	*cur;

	if (split_num(buffer) != 4)
		return (0);
	position = ft_split(buffer[1], ", ");
	rgb = ft_split(buffer[3], ", ");
	if (split_num(rgb) != 3 || split_num(position) != 3)
		return (0);
	cur = find_cur(element);
	cur->pos.x = ft_atof(position[0]);
	cur->pos.y = ft_atof(position[1]);
	cur->pos.z = ft_atof(position[2]);
	cur->ratio = ft_atof(buffer[2]);
	cur->red = ft_atoi(rgb[0]);
	cur->green = ft_atoi(rgb[1]);
	cur->blue = ft_atoi(rgb[2]);
	cur->next = NULL;
	element->light = cur;
	free_char(position);
	free_char(rgb);
	return (1);
}
