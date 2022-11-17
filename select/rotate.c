/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:10:43 by daechoi           #+#    #+#             */
/*   Updated: 2022/11/17 16:44:54 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	rotate_x(t_select *select, int flag)
{
	if (select->type == CAM && flag == INCREASE)
		select->cam->norm.x += 0.1;
	else if (select->type == PLANE && flag == INCREASE)
		select->pl->norm.x += 0.1;
	else if (select->type == CYLINDER && flag == INCREASE)
		select->cy->norm.x += 0.1;
	if (select->type == CAM && flag == DECREASE)
		select->cam->norm.x -= 0.1;
	else if (select->type == PLANE && flag == DECREASE)
		select->pl->norm.x -= 0.1;
	else if (select->type == CYLINDER && flag == DECREASE)
		select->cy->norm.x -= 0.1;
}

void	rotate_y(t_select *select, int flag)
{
	if (select->type == CAM && flag == INCREASE)
		select->cam->norm.y += 0.1;
	else if (select->type == PLANE && flag == INCREASE)
		select->pl->norm.y += 0.1;
	else if (select->type == CYLINDER && flag == INCREASE)
		select->cy->norm.y += 0.1;
	if (select->type == CAM && flag == DECREASE)
		select->cam->norm.y -= 0.1;
	else if (select->type == PLANE && flag == DECREASE)
		select->pl->norm.y -= 0.1;
	else if (select->type == CYLINDER && flag == DECREASE)
		select->cy->norm.y -= 0.1;
}

void	rotate_z(t_select *select, int flag)
{
	if (select->type == CAM && flag == INCREASE)
		select->cam->norm.z += 0.1;
	else if (select->type == PLANE && flag == INCREASE)
		select->pl->norm.z += 0.1;
	else if (select->type == CYLINDER && flag == INCREASE)
		select->cy->norm.z += 0.1;
	if (select->type == CAM && flag == DECREASE)
		select->cam->norm.z -= 0.1;
	else if (select->type == PLANE && flag == DECREASE)
		select->pl->norm.z -= 0.1;
	else if (select->type == CYLINDER && flag == DECREASE)
		select->cy->norm.z -= 0.1;
}