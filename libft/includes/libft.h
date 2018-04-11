/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:17:21 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/11 12:11:35 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <math.h>

# define BUFF_SIZE 32

typedef struct	s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

typedef	struct	s_vec
{
	double	x;
	double	y;
	double	z;
	double	h;
}				t_vec;

typedef	struct	s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			ft_dswap(double *a, double *b);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_nbrlen(int nbr);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle,
				size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
double			ft_atof(const char *str);
int				ft_atoi_base(char *str, int base);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtjoin(char const *s1, char const *s2, char const *s3);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdelone_fill(t_list **b_lst, t_list **prev, t_list **alst,
				void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstaddback(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstsort(t_list **b_list, int (*f)(t_list *e_one,
				t_list *e_two));
void			ft_lstsortrev(t_list **b_list, int (*f)(t_list *e_one,
				t_list *e_two));
void			ft_lstrev(t_list **b_list);
void			ft_putlst(t_list *b_list);

int				ft_isnum(int c);
int				ft_isupper(int c);
int				ft_islower(int c);
int				ft_isgraph(int c);
int				ft_ishex(int c);
int				ft_isblank(int c);
int				ft_iscntrl(int c);
int				ft_isspace(int c);
int				ft_ispunct(int c);
void			ft_puterr(char const *s);
void			ft_putnbrendl(int n);
void			ft_putnbrendl_fd(int n, int fd);
void			ft_putnstr(char const *s, size_t n);
int				ft_intlen(int n);
int				ft_strtablen(char **tab);
int				ft_countwords(char const *s, char c);
int				ft_factorial(int nb);
double			ft_pow(double x, double y);
int				ft_is_prime(int nb);
void			ft_putinttab(int **tab, size_t y, size_t x);
void			ft_puttab(char **tab);
size_t			ft_lstcount(t_list *lst);
size_t			ft_sqrtroundup(size_t n);
int				ft_power(int nbr, int power);

int				get_next_line(const int fd, char **line);
int				read_to_lst(const char *path_file, t_list **b_list);

double			ft_deg2rad(double degrees);
double			ft_clamp(double value, double min, double max);

t_vec			vector_cross(t_vec v1, t_vec v2);
t_vec			vector_product(t_vec v1, t_vec v2);
t_vec			vector_normalize(t_vec v);
t_vec			vector_double_substraction(t_vec v1, double i);
t_vec			vector_substraction(t_vec v1, t_vec v2);
t_vec			vector_int_product(t_vec v1, int i);
t_vec			vector_assign_values(double x, double y, double z);
t_vec			vector_addition(t_vec v1, t_vec v2);
t_vec			vector_double_division(t_vec v1, double i);
t_vec			vector_double_product(t_vec v1, double i);
double			vector_dot_product(t_vec v1, t_vec v2);
double			vector_length(t_vec v1);
double			length_between_vectors(t_vec v1, t_vec v2);

t_color			color_double_product(t_color v1, double i);
t_color			color_product(t_color v1, t_color v2);
t_color			color_addition(t_color v1, t_color v2);
t_color			color_division(t_color v1, double i);
t_color			color_average(t_color v1, t_color v2);
t_color			color_balanced(t_color v1, t_color v2, double a, double b);
void			ft_int2rgb(t_color *color, int i);

#endif
