/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:13:51 by bmuselet          #+#    #+#             */
/*   Updated: 2018/04/11 11:13:56 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec    bump_mapping(t_vec normal, t_vec hit_point, t_ray ray)
{
	double	noisecoefx;
	double	noisecoefy;
	double	noisecoefz;

	noisecoefx = noise(0.05 * hit_point.x, 0.05 * hit_point.y, 0.05 * hit_point.z);
	noisecoefy = noise(0.05 * hit_point.y, 0.05 * hit_point.z, 0.05 * hit_point.x);
	noisecoefz = noise(0.05 * hit_point.z, 0.05 * hit_point.x, 0.05 * hit_point.y);
	normal.x = (1.0f - ray.hit_obj->bump) * normal.x + ray.hit_obj->bump * noisecoefx;
	normal.y = (1.0f - ray.hit_obj->bump) * normal.y + ray.hit_obj->bump * noisecoefy;
	normal.z = (1.0f - ray.hit_obj->bump) * normal.z + ray.hit_obj->bump * noisecoefz;
    return (normal);
}