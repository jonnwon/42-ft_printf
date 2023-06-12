/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:44:19 by jonchoi           #+#    #+#             */
/*   Updated: 2022/09/26 14:34:45 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_flag
{
	int			flag;
	int			width;
	int			prec;
	int			type;
	int			error;
}				t_flag;

typedef struct s_box
{
	int			margin;
	char		sign;
	char		prefix;
	int			zero;
	long long	value;
	int			value_len;
	char		base[16];
	int			base_len;
}				t_box;

# define PER		1
# define C			2
# define S			4
# define P			8
# define D			16
# define I			32
# define U			64
# define H			128
# define CH			256

# define MINUS	1
# define ZERO	2
# define SPACE	4
# define PLUS	8
# define HASH	16

int			ft_printf(const char *form, ...);
void		ft_bzero(void *s, size_t n);
char		*ft_strchr(const char *s, int c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
size_t		ft_strlen(const char *s);
int			ft_parsing(char **form, t_flag *opt, va_list ap);
long long	ft_arg(t_flag *opt, va_list ap);
int			ft_output(t_flag *opt, long long arg);
int			ft_max(int x, int y);
void		ft_check(t_flag *opt, t_box *box);
int			ft_numlen(unsigned long long n, int len);
void		ft_print_box(t_flag *flag, t_box *box);

#endif
