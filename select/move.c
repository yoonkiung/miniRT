/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:57:31 by daechoi           #+#    #+#             */
/*   Updated: 2022/11/15 19:52:38 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	move_x(t_select *select, int flag)
{
	if (select->type == CAM && flag == INCREASE)
		select->cam->pos.x++;
	else if (select->type == SPHERE && flag == INCREASE)
		select->sp->pos.x++;
	else if (select->type == PLANE && flag == INCREASE)
		select->pl->pos.x++;
	else if (select->type == CYLINDER && flag == INCREASE)
		select->cy->pos.x++;
	if (select->type == CAM && flag == DECREASE)
		select->cam->pos.x--;
	else if (select->type == SPHERE && flag == DECREASE)
		select->sp->pos.x--;
	else if (select->type == PLANE && flag == DECREASE)
		select->pl->pos.x--;
	else if (select->type == CYLINDER && flag == DECREASE)
		select->cy->pos.x--;
}

void	move_y(t_select *select, int flag)
{
	if (select->type == CAM && flag == INCREASE)
		select->cam->pos.y++;
	else if (select->type == SPHERE && flag == INCREASE)
		select->sp->pos.y++;
	else if (select->type == PLANE && flag == INCREASE)
		select->pl->pos.y++;
	else if (select->type == CYLINDER && flag == INCREASE)
		select->cy->pos.y++;
	if (select->type == CAM && flag == DECREASE)
		select->cam->pos.y--;
	else if (select->type == SPHERE && flag == DECREASE)
		select->sp->pos.y--;
	else if (select->type == PLANE && flag == DECREASE)
		select->pl->pos.y--;
	else if (select->type == CYLINDER && flag == DECREASE)
		select->cy->pos.y--;
}

void	move_z(t_select *select, int flag)
{
	if (select->type == CAM && flag == INCREASE)
		select->cam->pos.z++;
	else if (select->type == SPHERE && flag == INCREASE)
		select->sp->pos.z++;
	else if (select->type == PLANE && flag == INCREASE)
		select->pl->pos.z++;
	else if (select->type == CYLINDER && flag == INCREASE)
		select->cy->pos.z++;
	if (select->type == CAM && flag == DECREASE)
		select->cam->pos.z--;
	else if (select->type == SPHERE && flag == DECREASE)
		select->sp->pos.z--;
	else if (select->type == PLANE && flag == DECREASE)
		select->pl->pos.z--;
	else if (select->type == CYLINDER && flag == DECREASE)
		select->cy->pos.z--;
}