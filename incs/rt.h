/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 12:48:33 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/01 12:33:11 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RT_H

# define RT_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include <stdio.h> //<- A SUPPRIMER

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define KEY_PRESS 2
# define MOUSE_PRESS 4
# define MOUSE_MOVE 6
# define EXIT_PRESS 17
# define EXIT_PRESS_MASK (1L << 17)
# define KEY_PRESS_MASK (1L << 6)
# define MOUSE_PRESS_MASK (1L << 2)
# define MOUSE_MOVE_MASK (1L << 6)

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_SPACE 49
# define KEY_ECHAP 53
# define KEYPAD_RIGHT 124
# define KEYPAD_LEFT 123
# define KEYPAD_UP 126
# define KEYPAD_DOWN 125

# define INVALID_FILE_DESCRIPTION 0
# define INVALID_FILE 1
# define INVALID_ARG 2

# define FOV 2

# define ERROR -1
# define SPH 0
# define PLA 1
# define CYL 2
# define CON 3
# define LIG 4

# define ROT_SPEED 0.1
# define MOVE_SPEED 10

# define MAX 1000000000

# define NB_THREADS 8


typedef struct		s_obj
{
	char			type;
	t_vec			pos;
	t_vec			dir;
	double			rad;
	t_color			color;
	t_vec			rot;
	t_vec			trans;
}					t_obj;

typedef struct		s_ray
{
	t_vec 			pos;
	t_vec			dir;
	double			length;
	t_vec			normal;
	t_obj			*hit_obj;
	t_vec			hit_pos;
	t_vec			hit_dir;
}					t_ray;

typedef struct		s_img
{
	void			*img;
	char			*data;
	int				size_x;
	int				size_y;
	int				bpp;
	int				size_line;
	int				endian;
}						t_img;

typedef struct		s_cam
{
	t_vec			pos;
	t_vec			dir;
	t_vec			forward;
	t_vec			left;
	t_vec			up;
}						t_cam;

typedef struct	s_env
{
	void			*mlx;
	void			*win;
	t_img			img;
	int				y_start;
	int				y_end;
	t_cam			cam;
	t_list			*objs;
	t_list			*lights;
}							t_env;

void	ft_delstr(void *content, size_t content_size);

t_img	new_image(void *mlx, int img_size_x, int img_size_y);
void	del_image(void *mlx, t_img *img);
void	put_pixel_to_image(t_img *img, int x, int y, t_color color);

char	get_type(char *str_obj);
t_vec	get_vec(char *str_obj, int *i_str);
t_color	get_color(char *str_obj, int *i_str);
void	get_objs_and_cam(t_env *e, char *path_file);
void	draw(t_env *e);
int		check_inter_objects(t_env *e, t_ray *ray);

int		cone_inter(t_env *e, t_ray *ray);
int		plan_inter(t_env *e, t_ray *ray);
int		cylindre_inter(t_env *e, t_ray *ray);
int		sphere_inter(t_env *e, t_ray *ray);

int		key_hook(int keycode, t_env *e);
int		button_exit(int keycode, t_env *e);
t_color light_calc(t_env *e, t_ray ray);
void	transformations(t_obj *obj);
t_vec	get_normal(t_env *e, t_vec hit_point, t_ray ray);

#endif
