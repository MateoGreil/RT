/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 12:48:33 by bmuselet          #+#    #+#             */
/*   Updated: 2018/04/11 12:07:59 by mgreil           ###   ########.fr       */
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
# define KEY_TAB 48
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
# define KEY_FN 279

# define INVALID_FILE_DESCRIPTION 0
# define INVALID_FILE 1
# define INVALID_ARG 2

# define ON 1
# define OFF 0

# define FOV 2

# define ERROR -1
# define SPH 0 //sphere
# define PLA 1 //plan
# define CYL 2 //cylindre
# define CON 3 //cone
# define PAR 4 //par
# define LIG 5 //light
# define LIA 6 //ambient_light
# define LID 7 //directional_light

# define ROT_SPEED 10
# define MOVE_SPEED 10

# define INFINITE 1000000000
# define ZERO 0.0000001

# define TRUE 1
# define FALSE 0

# define NB_MIRRORING 0
# define NB_THREADS 8
# define NB_SAMPLES 1
# define NB_TEXTURES 5

# define BLACK (t_color){0, 0, 0}
# define WHITE (t_color){255, 255, 255}

# define N_AIR 1.000293

typedef struct		s_obj
{
	char			id;
	char			type;
	t_vec			pos;
	t_vec			dir;
	double			rad;
	t_color			color;
	t_vec			rot;
	t_vec			trans;
	int				num_texture;
	int				perturbation;
	double			bump;
	char			refl;
	char			refr;
	double			n_refr;
}					t_obj;

typedef struct		s_ray
{
	t_vec			pos;
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
	int				antialiasing;
	int				cel_shading;
	int				sepia;
	int				bnw;
	int				reverse;
	int				fog;
	int				stereo;
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
	void			*mlx;
	void			*win;
	void			*wait_win;
	t_img			img;
	t_img			wait_img;
	int				y_start;
	int				y_end;
	xmlDocPtr		doc;
	t_cam			cam;
	t_list			*objs;
	t_list			*lights;
	t_img			*texture;
}					t_env;

void				ft_delstr(void *content, size_t content_size);

t_img				new_image(void *mlx, int img_size_x, int img_size_y);
void				del_image(void *mlx, t_img *img);
void				put_pixel_to_image(t_img *img, int x, int y, t_color color);

void				set_cam_coordinates(t_env *e);
void				cam_to_world_matrix(t_env *e);
void				world_to_cam_matrix(t_env *e);
double				hammersley(int j);
t_vec				ray_dir_cal(t_env *e, double i, double j, int s);

void				x_rotation(t_cam *cam, double a);
void				y_rotation(t_cam *cam, double a);
void				z_rotation(t_cam *cam, double a);

int					check_inter_objects(t_env *e, t_ray *ray);
t_color				search_color(void *e, int x, int y, int s);
t_color				max_color(t_color color);
t_color				specular_light(t_ray ray, t_ray *light_ray,
					t_color light_color);
t_color				calc_specular(t_ray ray, t_ray *light_ray,
					t_color light_color, t_color spec);

double				cone_inter(t_env *e, t_ray *ray, t_vec temp);
double				plan_inter(t_env *e, t_ray *ray);
double				cylindre_inter(t_env *e, t_ray *ray, t_vec temp);
double				sphere_inter(t_env *e, t_ray *ray, t_vec temp);
void				draw(t_env *e, int loading);


void				ray_refl(t_env *e, t_ray *ray, int nb_rebond);
void				ray_refr(t_env *e, t_ray *ray, int nb_rebond);

int					key_hook(int keycode, t_env *e);
int					button_exit(int keycode, t_env *e);
t_color				light_calc(t_env *e, t_ray ray);
t_color				directional_light(t_env *e, t_ray ray, t_ray *light_ray);
t_color				ambient_color(t_env *e, t_ray ray);
void				transformations(t_obj *obj);
t_vec				ft_rotation_x(t_vec ex_pos, double angle);
t_vec				ft_rotation_y(t_vec ex_pos, double angle);
t_vec				ft_rotation_z(t_vec ex_pos, double angle);
t_vec				get_normal(t_vec hit_point, t_ray ray);
void				screenshot(t_env *e);
void				sampling_color(t_env *e, t_vec compteur);
t_color				screenshotearch_color(void *e, int x, int y, int s);
void				blend_color(t_env *e, t_color *color,
					t_vec compteur, int n);

double				equation_second(t_vec a, double *b);
double				parab_inter(t_env *e, t_ray *ray, t_vec temp);

void				multi_thread(t_env *e);
double				cel_shading(t_env *e, double d);
t_color				cel_shading_shape(t_env *e, t_ray ray, t_color color);
void				antialiasing(t_env *e, t_vec compteur,
					t_color *color, int i);

void				stereoscopy(t_env *e);
void				save_scene(t_env *e);
void				print_keys(void);

void				init_loading(t_env *e);
int					mouse_hook(int button, int x, int y, t_env *e);
void				change_object(t_env *e, int keycode);
void				change_object_color(t_color *color);
int					change_filter(int keycode, t_env *e);
t_color				filter_color(t_env *e, t_color color, t_ray ray);
int					key_filter(int keycode, t_env *e);
int					calc_shadow(t_env *e, t_ray light_ray);

t_color				tex_or_not(t_env *e, t_color color, t_ray ray);
t_color				damier_color(t_vec hit_point, t_color color);
void 				marble_texture(t_vec hit_point, t_color *color);
void				grain_texture(t_vec hit_point, t_color *color);
t_color 			perlin_color(t_vec hit_point);

double				noise(double x, double y, double z);
double				lerp(double t, double a, double b);
double				fade(double t);
double				grad(int hash, double x, double y, double z);

int					load_texture_img(t_env *e);
t_color				print_texture(t_env *e, t_obj *obj, t_vec hit_pos);
t_vec				bump_mapping(t_vec normal, t_vec hit_point, t_ray ray);

// PARTIE PARSING XML //
xmlNodePtr			get_node(xmlNodePtr node, char *name);
void				parse_file(t_env *e, char *docname);
void				xml_get_cam(xmlNodePtr cam, t_env *e);
void				xml_get_objs(xmlNodePtr objs, t_env *e);
void				xml_get_lights(xmlNodePtr lights, t_env *e);
t_color				xml_get_color(xmlNodePtr cur, t_env *e);
char				xml_get_type(xmlNodePtr cur, t_env *e);
t_vec				xml_get_vec(xmlNodePtr cur, t_env *e);

void	save_scene(t_env *e);
void	xml_set_vec(xmlNodePtr cur, t_vec vec);
void	xml_set_type(xmlNodePtr cur, int type);
void	xml_set_color(xmlNodePtr cur, t_color color);

void	printf_obj(t_obj obj);

#endif
