/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiyoon <kiyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:21:08 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/22 15:21:08 by kiyoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double	minf(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

double	maxf(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
