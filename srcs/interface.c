/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 11:41:23 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/14 11:41:24 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void init_loading(t_env *e)
{
  int x;
  int y;

  x = 1;
  while (x <= 400)
  {
    y = 1;
    while (y <= 100)
    {
      put_pixel_to_image(&e->wait_img, x, y, WHITE);
      y++;
    }
    x++;
  }
  mlx_put_image_to_window(e->mlx, e->wait_win, e->wait_img.img, 0, 0);
  mlx_string_put(e->mlx, e->wait_win, 100, 40, 0x000000, "RT is loading ...");
}
/*
void update_loading(t_env *e, int i)
{
  int x;
  int y;

  printf("d\n");
  x = 60;
  while (x < (60 + (i * (280 / NB_THREADS))))
  {
    y = 40;
    while (y < 60)
    {
      mlx_pixel_put(e->mlx, e->wait_win, x, y, 0x000000);
      y++;
    }
    x++;
  }
  mlx_put_image_to_window(e->mlx, e->wait_win, e->wait_img.img, 0, 0);
  mlx_string_put(e->mlx, e->wait_win, 100, 15, 0x000000, "RT is loading ...");
}
*/
