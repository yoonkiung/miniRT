/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_A.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiyoon <kiyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:01:53 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/07 18:01:54 by kiyoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	parse_a(char **buffer, t_elements *element)
{
	char	**rgb;

	if (element->amb)
		return (0);
	if (split_num(buffer) != 3)
		return (0);
	rgb = ft_split(buffer[2], ", ");
	if (split_num(rgb) != 3)
		return (0);
	element->amb = ft_malloc(sizeof(t_ambient));
	element->amb->ratio = ft_atof(buffer[1]);
	element->amb->red = ft_atoi(rgb[0]);
	element->amb->green = ft_atoi(rgb[1]);
	element->amb->blue = ft_atoi(rgb[2]);
	free_char(rgb);
	return (1);
}
