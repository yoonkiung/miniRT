/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:44:45 by daechoi           #+#    #+#             */
/*   Updated: 2022/11/15 18:57:00 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	init_select(t_select *select, t_camera *cam)
{
	select->type = CAM;
	select->object = cam;
}

void	which_object(t_select *select, void (*f)(void *object))
{
	if (select->type == CAM)
		(*f)(select->object);
	else if (select->type == SPHERE)
		(*f)(select->object);
	else if (select->type == PLANE)
		(*f)(select->object);
	else if (select->type == CYLINDER)
		(*f)(select->object);
}