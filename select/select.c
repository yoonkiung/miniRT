/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:44:45 by daechoi           #+#    #+#             */
/*   Updated: 2022/11/15 20:09:53 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_select	*init_select(t_camera *cam)
{
	t_select *select;

	select = ft_malloc(sizeof(t_select));
	select->type = CAM;
	select->cam = cam;
	return (select);
}