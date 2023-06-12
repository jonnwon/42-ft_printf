/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:42:33 by jonchoi           #+#    #+#             */
/*   Updated: 2022/09/30 02:52:02 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	parse_char(char **form, char *charset, int loop)
{
	int		res;
	char	*ptr;

	res = 0;
	ptr = ft_strchr(charset, **form);
	while (**form && ptr)
	{
		res = res | 1 << (ptr - charset);
		(*form)++;
		if (!loop)
			break ;
		ptr = ft_strchr(charset, **form);
	}
	return (res);
}

static int	parse_num(char **form, va_list ap)
{
	int	res;

	res = 0;
	if (**form == '*')
	{
		++(*form);
		return (va_arg(ap, int));
	}
	while ((**form >= '0') && (**form <= '9'))
	{
		res = res * 10 + **form - '0';
		++(*form);
	}
	return (res);
}

static int	ft_check_error(t_flag *opt, char **form, char *ptr)
{
	int	tag;

	tag = 0;
	if ((opt->flag & HASH) && (opt->flag & SPACE))
		tag = -1;
	if ((opt->flag & HASH) && (opt->flag & PLUS))
		tag = -1;
	if ((opt->flag & SPACE) && (opt->flag & PLUS))
		tag = -1;
	if ((opt->flag & HASH) && (opt->type & (PER | C | S | P | D | I | U)))
		tag = -1;
	if ((opt->flag & SPACE) && (opt->type & (PER | U | H | CH | P | C)))
		tag = -1;
	if ((opt->flag & PLUS) && (opt->type & (PER | U | H | CH | P | C | S)))
		tag = -1;
	if (!(opt->type))
		tag = -1;
	if (tag == -1)
	{
		opt->error = 1;
		*form = ptr;
	}
	return (tag);
}

int	ft_parsing(char **form, t_flag *opt, va_list ap)
{
	char	*ptr;

	ptr = ++(*form);
	opt->flag = parse_char(&ptr, "-0 +#", 1);
	opt->width = parse_num(&ptr, ap);
	if (opt->width < 0)
	{
		opt->width *= -1;
		opt->flag = opt->flag | MINUS;
	}
	opt->prec = -1;
	if (parse_char(&ptr, ".", 0))
	{
		opt->prec = parse_num(&ptr, ap);
		if (opt->prec < 0)
			opt->prec = -1;
	}
	opt->type = parse_char(&ptr, "%cspdiuxX", 0);
	if (ft_check_error(opt, form, ptr) == -1)
		return (1);
	if (opt->type)
		*form = ptr;
	return (opt->type);
}

long long	ft_arg(t_flag *opt, va_list ap)
{
	if (opt->type & PER)
		return (0);
	else if (opt->type & S)
		return ((long long)va_arg(ap, char *));
	else if (opt->type & P)
		return ((long long)va_arg(ap, void *));
	else if (opt->type & (C | D | I))
		return (va_arg(ap, int));
	else if (opt->type & (U | H | CH))
		return (va_arg(ap, unsigned int));
	return (0);
}
