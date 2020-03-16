/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:04:13 by jwisozk           #+#    #+#             */
/*   Updated: 2020/03/02 04:57:51 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include "../includes/libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
//# include <SDL2/SDL.h>
# include "../includes/SDL2/SDL2.framework/Headers/SDL.h"

# define TITLE_WINDOW	"R4Y7r4c1N9_C4P031R4_CR3W"
# define DW				601
# define DH				601
# define DS             (DW * DH)
# define EXTENSION		"cfg"
# define VW				1
# define VH				1
# define D				2
# define INF			1000
// # define BACKGROUND		128, 128, 128
# define BACKGROUND		255, 255, 255
# define BACKG			0xFFFFFF
# define BLACK			0x0
# define DARK_GREY			0x505050
# define E				1e-6
# define SPHERE_OBJ		{SPHERE, &ft_sphere_intersect, &ft_sphere_fill}
# define PLANE_OBJ		{PLANE, &ft_plane_intersect, &ft_plane_fill}
# define CYLINDER_OBJ	{CYLINDER,  &ft_cylinder_intersect, &ft_cylinder_fill}
# define CONE_OBJ		{CONE,  &ft_cone_intersect, &ft_cone_fill}
# define ARR_OBJ		{SPHERE_OBJ, CYLINDER_OBJ, PLANE_OBJ, CONE_OBJ}
# define TAN(x)			tan(x * M_PI / 180)
# define COS(x)			cos(x * M_PI / 180)
# define SIN(x)			sin(x * M_PI / 180)
# define CAM_S			"camera"
# define LIGHT_S		"light"
# define SPHERE_S		"sphere"
# define PLANE_S		"plane"
# define CYLINDER_S		"cylinder"
# define CONE_S			"cone"
# define ARR_TYPES		{{CAM_S}, {LIGHT_S}, {SPHERE_S}, {PLANE_S}, {CYLINDER_S}, {CONE_S}}
# define OBJ_TYPES		{CAM_S, LIGHT_S, PLANE_S, SPHERE_S, CYLINDER_S, CONE_S}
# define AMBIENT_S		"ambient"
# define POINT_S		"point"
# define DIRECT_S		"directional"
# define LIGHT_TYPES	{AMBIENT_S, POINT_S, DIRECT_S}
# define TYPE			"type"
# define INTENSITY		"intensity"
# define LOOK_AT		"look_at"
# define POSITION		"position"
# define CENTER			"center"
# define NORMAL			"normal"
# define COLOR			"color"
# define ANGLE			"angle"
# define RADIUS			"radius"
# define SPECULAR		"specular"
# define ROTATION		"rotation"
# define TRANSLATION	"translation"
# define USAGE			"Usage: ./RTv1 <filename>"
# define ERROR  		"Error: "
# define ERROR_1		"Extension of file is incorrect."
# define ERROR_2		"Type # is invalid."
# define ERROR_3		"Curly braces in the file are not valid."
# define ERROR_4		"The length of the 4th rotation parameter should be 3."
# define ERROR_5		"The 4th parameter of rotation is invalid."
# define ERROR_6		"File not found."
# define ERROR_7		"File doesn' contain a camera."
# define ERROR_8		"File doesn't contain parameter of camera: look_at\""
# define ERROR_9		"File doesn't contain parameter of camera: position\""
# define ERROR_10_1		"Parameters of camera: \"position\" and \"look_at\""
# define ERROR_10_2		" are equal. Impossible to determine camera direction."
# define ERROR_10		ERROR_10_1 ERROR_10_2
# define ERROR_11		"Param \"type\" of light is invalid."
# define ERROR_12		"Param \"position\" of light is invalid."
# define ERROR_13		"Param \"intensity\" of light is invalid."
# define ERROR_14		"Param \"center\" of sphere is invalid."
# define ERROR_15		"Param \"radius\" of sphere is invalid."
# define ERROR_16		"Param \"color\" of sphere is invalid."
# define ERROR_17		"Param \"center\" of cylinder is invalid."
# define ERROR_18		"Param \"normal\" of cylinder is invalid."
# define ERROR_19		"Param \"radius\" of cylinder is invalid."
# define ERROR_20		"Param \"color\" of cylinder is invalid."
# define ERROR_21		"Param \"center\" of cone is invalid."
# define ERROR_22		"Param \"normal\" of cone is invalid."
# define ERROR_23		"Param \"angle\" of cone is invalid."
# define ERROR_24		"Param \"color\" of cone is invalid."
# define ERROR_25		"Param \"point\" of plane is invalid."
# define ERROR_26		"Param \"normal\" of plane is invalid."
# define ERROR_27		"Param \"color\" of plane is invalid."
# define ERROR_28		"Function close() failed."
# define ERROR_29		"Memory was not allocated."
# define ERROR_30		"Function mlx_init() return NULL."
# define ERROR_31		"Function mlx_new_window() return NULL."
# define ERROR_32		"Function mlx_new_image() return NULL."
# define ERROR_33		"Function get_next_line() return -1."
# define ERROR_34		"Function ft_new_lst() return NULL."
# define ERROR_35		"Function mlx_xpm_file_to_image() return NULL."
# define SHADOW_ON		1
# define SHADOW_OFF		0
# define START_RECUR	0
# define MAX_DEPTH		4
# define RAYS_IN_ROW	4
# define ALL_RAYS		25
# define RAYS_STEP		0.2
# define RENDERS_NUM	2

typedef struct			s_vec3
{
	double				x;
	double				y;
	double				z;
}						t_vec3;

typedef struct			s_ang3
{
	int					x;
	int					y;
	int					z;
}						t_ang3;

typedef struct			s_ray
{
	t_vec3				origin;
	t_vec3				direct;
	double				t_min;
	double				t_max;
}						t_ray;

typedef enum			e_type
{
	CAMERA,
	LIGHT,
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	COUNT
}						t_type;

typedef enum			e_type_light
{
	AMBIENT,
	POINT,
	DIRECTIONAL
}						t_type_light;

typedef struct			s_obj
{
	t_type				type;
	t_vec3				center;
	t_vec3				normal;
	double				radius;
	double				angle;
	int					color;
	int					specular;
	t_vec3				translation;
	t_ang3				rotation;
	double 				t;
	char				tneg;
	char				hollow;
	double				tpt;
	double				tptp;
	double				refl;
	int					sliced;
	t_vec3				slice_up;
	t_vec3				slice_down;
	double				len_up;
	double				len_down;
	struct s_obj		*neg;
	struct s_obj		*next;
}						t_obj;

typedef struct			s_arr_type
{
	char				*type;
}						t_arr_type;

typedef struct			s_lst
{
	char				*type;
	void				*data;
	struct s_lst		*next;
}						t_lst;

typedef struct			s_light
{
	t_type_light		type;
	t_vec3				pos;
	double				intensity;
	struct s_light		*next;
}						t_light;

typedef struct			s_cam
{
	t_vec3				forward;
	t_vec3				left;
	t_vec3				up;
	t_vec3				pos;
	t_vec3				look_at;
}						t_cam;

typedef struct          s_sdl
{
	SDL_Window          *win;
	SDL_Renderer        *ren;
	SDL_Texture	        *tex;
	SDL_Event           e;
	int                 pixels[DS];
	int                 pitch;
}                       t_sdl;

typedef struct			s_pixel
{
	t_vec3				point;
	t_vec3				normal;
	int					color;
	int					specular;
	t_type				type;
	t_vec3				po;
	t_vec3				center;
}						t_pixel;

typedef struct			s_flags
{
	char	anti_aliasing;
	char	cartoon;
}						t_flags;


typedef struct			s_data
{
	t_sdl				sdl;
	t_cam				*cam;
	t_light				*l;
	t_obj				*obj_all;
	t_obj				*obj;
	t_ray				ray;
	t_pixel				p;
	t_flags				f;
	void				(*r[RENDERS_NUM])(struct s_data *);
}						t_data;

char					*ft_msg(char *str);
t_vec3					ft_create_vec3(double x, double y, double z);
t_ang3					ft_create_ang3(int x, int y, int z);
t_ray					ft_create_ray(t_vec3 cam, t_vec3 dir, double t_min,
						double t_max);
t_vec3					ft_cross_product(t_vec3 a, t_vec3 b);
t_vec3					ft_multiply(double k, t_vec3 v);
t_vec3					ft_subtract(t_vec3 v1, t_vec3 v2);
t_vec3					ft_add(t_vec3 v1, t_vec3 v2);
t_vec3					ft_normalize_vec3(t_vec3 v);
double					ft_lenv(t_vec3 v);
double					ft_dot(t_vec3 v1, t_vec3 v2);
double					ft_max(double x, double y);
double					ft_min(double x, double y);
int						ft_rgb(int r, int g, int b);
int						ft_multiply_color(double k, int color, int specular);
void					ft_camera_create(t_data *data, t_lst *lst);
void					ft_light_create(t_data *data, t_lst *lst);
void					ft_obj_create(t_data *data, t_lst *lst);
t_vec3					ft_translate(t_vec3 o, t_vec3 t);
t_vec3					ft_rotate(t_vec3 v, t_ang3 a);
void					ft_get_scene(int fd, t_data *data);
int						*ft_rotation_order(int *arr, int array[3], char *str);
double					*ft_new_arr_d(char *a, char *b, char *c);
int						*ft_new_arr_i(char *a, char *b, char *c, char *str);
void					ft_pixels_get(t_data *data);
void					ft_camera_look_at(t_data *data);
void					ft_camera_ray(t_data *data, int x, int y);
void					ft_camera_multiray(t_data *data, int x, int y, double ax, double ay);
t_obj					*ft_obj_intersect(t_obj *obj, t_ray *ray, int shadow);
void					ft_pixel_fill(t_obj *obj, t_pixel *p, t_ray *ray);
//double					ft_lighting(t_data *data);
double	ft_lighting(t_data *data, t_pixel *p);
t_lst					*ft_new_lst(char *type, void *data);
void					ft_add_lst(t_lst **head, t_lst *new);
void					ft_check_argv(char *str);
void					ft_open_file(char *name, int *fd);
void					ft_close_file(const int fd);
int						ft_compare_vec3(t_vec3 a, t_vec3 b);
int						ft_check_substr(char *str, int num);
void    				ft_sdl2_main(t_sdl   *sdl);
void    				ft_sdl2_key_quit(SDL_Event e, int *running);
int 				    ft_isvalid(char *str, char *arr[], int max);
int					    ft_isvalid_light(char *str);
int					    ft_isvalid_obj(char *str);

double	ft_neg_calc(t_ray *ray, t_obj *obj, t_obj **ret, double p[2]);
t_ray	ft_refract(t_ray ray, double t, t_vec3 normal, double tpt);
int		ft_trace_ray(t_data *data, t_ray ray, int i);
void	print_v(t_vec3 v);
int		ft_rgb_add(int a, int b);
t_ray	ft_reflect(t_ray ray, double t, t_vec3 norm);
int		refl_colour(t_ray ray, t_pixel p, t_obj *o, t_data *data);
void	ft_antialiasing(t_data *data);
int		ft_cartoon(double lighting, t_pixel *p);

typedef struct			s_dot
{
	t_ray	ray;
	t_obj	o;
	t_vec3	norm;
	double	kr;	
	double	l;
}						t_dot;

/*
**	tree structure with links to left, right and up (parent) nodes
*/

typedef struct			s_tree
{
	t_dot			dot;
	int				left_col;
	int				right_col;
	int				colour;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*parent;
}						t_tree;

t_tree	*ft_tree_new(t_dot dot);
double	koef_refr(double nt, t_vec3 norm, t_ray rfr, t_ray ray);
t_tree  *ft_trace_refracted(t_ray ray, t_data *data, t_tree *node, int *i);
int		ft_traverse_tree(t_tree *node, int i, t_data *data);
int     ft_transparent_colour(t_ray ray, t_obj *o, t_data *data);
void	slice(t_ray *ray, t_obj *obj, double p[2]);
void	slice_sphere(t_ray *ray, t_obj *obj, double p[2]);

#endif
