/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_L.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiyoon <kiyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:56:18 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/08 13:56:19 by kiyoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_l(char **buffer, t_elements *element)
{
	char	**position;
	char	**rgb;

	if (element->light)
		return (0);
	position = ft_split(buffer[1], ", ");
	rgb = ft_split(buffer[3], ", ");
	if (split_num(buffer) != 4 || split_num(position) != 3 \
		|| split_num(rgb) != 3)
		return (0);
	element->light = ft_malloc(sizeof(t_light));
	element->light->pos.x = ft_atof(position[0]);
	element->light->pos.y = ft_atof(position[1]);
	element->light->pos.z = ft_atof(position[2]);
	element->light->ratio = ft_atof(buffer[2]);
	free_char(position);
	return (1);
}
