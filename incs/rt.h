/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 12:48:33 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/20 11:32:40 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RT_H

# define RT_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>

# include <libxml/parser.h>

# include <stdio.h> //<- A SUPPRIMER

# define WIN_WIDTH 1000
# define WIN_HEIGHT 800

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
# define KEY_F 3
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_W 13
# define KEY_R 15
# define KEY_T 17
# define KEY_I 34
# define KEY_L 37
# define KEY_J 38
# define KEY_K 40
# define KEY_N 45
# define KEY_M 46
# define KEY_SPACE 49
# define KEY_DEL 51
# define KEY_ECHAP 53
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_PUP 116
# define KEY_PDOWN 121
# define KEY_ECHAP 53
# define KEYPAD_RIGHT 124
# define KEYPAD_LEFT 123
# define KEYPAD_UP 126
# define KEYPAD_DOWN 125
# define KEY_LCTRL 256

# define INVALID_FILE_DESCRIPTION 0
# define INVALID_FILE 1
# define INVALID_ARG 2

# define ON 1
# define OFF 0

# define FOV 2

# define ERROR -1
# define SPH 0
# define PLA 1
# define CYL 2
# define CON 3
# define PAR 4
# define LIG 5
# define LIA 6
# define LID 7

# define ROT_SPEED 10
# define MOVE_SPEED 10

# define INFINITE 1000000000
# define ZERO 0.0000001


# define TRUE 1
# define FALSE 0

# define NB_MIRRORING 0
# define NB_THREADS 8
# define NB_SAMPLES 1
# define NB_TEXTURES 2

# define BLACK (t_color){0, 0, 0}
# define WHITE (t_color){255, 255, 255}

typedef struct		s_obj
{
	int				id;
	char			type;
	t_vec			pos;
	t_vec			dir;
	double			rad;
	t_color			color;
	t_vec			rot;
	t_vec			trans;
	char			mirror;
	int				num_texture;
}					t_obj;

typedef struct		s_ray
{
	t_vec 			pos;
	t_vec			dir;
	double			length;
	double			disc;
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
}					t_img;

typedef struct		s_cam
{
	double			dist;
	double			focal;
	double			lens_rad;
	double			zoom;
	int				num_samples;
	int 			antialiasing;
	int				cel_shading;
	int				sepia;
	int				bnw;
	int				reverse;
	int				fog;
	t_vec			pos;
	t_vec			dir;
	t_vec			right;
	t_vec			up;
	t_vec			forward;
	int				selection;
	t_obj			*select_obj;
	t_obj			*prev_ray_obj;
	t_point			samp;
	double			cam_to_world[3][3];
}					t_cam;

typedef struct		s_env
{
	void				*mlx;
	void				*win;
	void				*wait_win;
	t_img			img;
	t_img			wait_img;
	int				y_start;
	int				y_end;
	xmlDocPtr		doc;
	t_cam			cam;
	t_list			*objs;
	t_list			*lights;
	t_img			*texture;
	t_img			*bump;
}					t_env;

void				ft_delstr(void *content, size_t content_size);

t_img				new_image(void *mlx, int img_size_x, int img_size_y);
void				del_image(void *mlx, t_img *img);
void				put_pixel_to_image(t_img *img, int x, int y, t_color color);

void				set_cam_coordinates(t_env *e);
void				cam_to_world_matrix(t_env *e);
void				world_to_cam_matrix(t_env *e);
t_vec				ray_dir_cal(t_env *e, double i, double j, int s);

void				x_rotation(t_cam *cam, double a);
void				y_rotation(t_cam *cam, double a);
void				z_rotation(t_cam *cam, double a);

char				get_type(char *str_obj);
t_vec				get_vec(char *str_obj, int *i_str);
t_color				get_color(char *str_obj, int *i_str);
int					get_nbr(char *str_obj, int *i_str);
void				get_objs_and_cam(t_env *e, char *path_file);
int					check_inter_objects(t_env *e, t_ray *ray);

double				cone_inter(t_env *e, t_ray *ray, t_vec temp);
double				plan_inter(t_env *e, t_ray *ray);
double				cylindre_inter(t_env *e, t_ray *ray, t_vec temp);
double				sphere_inter(t_env *e, t_ray *ray, t_vec temp);
void				draw(t_env *e, int loading);
void				ray_mirror(t_env *e, t_ray *ray, int nb_rebond);
int					key_hook(int keycode, t_env *e);
int					button_exit(int keycode, t_env *e);
t_color 			light_calc(t_env *e, t_ray ray);
t_color				directional_light(t_env *e, t_ray ray, t_ray *light_ray);
void				transformations(t_obj *obj);
t_vec				ft_rotation_x(t_vec ex_pos, double angle);
t_vec				ft_rotation_y(t_vec ex_pos, double angle);
t_vec				ft_rotation_z(t_vec ex_pos, double angle);
t_vec				get_normal(t_vec hit_point, t_ray ray);
void				screenshot(t_env *e);
void    		sampling_color(t_env *e, t_vec compteur);
t_color			search_color(void *e, int x, int y, int s);


// PARTIE BENJAMIN //
double		equation_second(t_vec a, double *b);
double		parab_inter(t_env *e, t_ray *ray, t_vec temp);

void				multi_thread(t_env *e);
double				cel_shading(t_env *e, double d);
t_color				cel_shading_shape(t_env *e, t_ray ray, t_color color);
void    antialiasing(t_env *e, t_vec compteur, t_color *color, int i);

void 				init_loading(t_env *e);
int					mouse_hook(int button, int x, int y, t_env *e);
void 				change_object(t_env *e, int keycode);
void 				change_object_color(t_color *color);
int					change_filter(int keycode, t_env *e);
t_color 			filter_color(t_env *e, t_color color, t_ray ray);
int					key_filter(int keycode, t_env *e);

t_color				damier_color(t_vec hit_point);
void 				marble_texture(t_vec hit_point, t_color *color);
void				wood_texture(t_vec hit_point, t_color *color);
t_color 				perlin_color(t_vec hit_point);
void				blend_color(t_env *e, t_color *color, t_vec compteur, int n);

double				noise(double x, double y, double z);
double				fade(double t);
double				lerp(double t, double a, double b);
double				grad(int hash, double x, double y, double z);

int					load_texture_img(t_env *e);
int					load_texture_bump(t_env *e);
t_color  		print_texture(t_env *e, t_obj *obj, t_vec hit_pos);
t_vec    	bump_mapping(t_env *e, t_vec normal, t_vec hit_pos);

// PARTIE PARSING XML //
xmlNodePtr	get_node(xmlNodePtr node, char *name);
void			get_node_for_env(t_env *e, xmlNodePtr root);
void			parse_file(t_env *e, char *docname);

#endif
