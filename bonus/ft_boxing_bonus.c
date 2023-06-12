/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_boxing_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 04:18:51 by jonchoi           #+#    #+#             */
/*   Updated: 2022/09/26 16:49:33 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	boxing_char(t_flag *opt, t_box *box)
{
	box->value_len = 1;
	if (opt->type & PER)
		box->value = '%';
	if (opt->flag & ZERO && !(opt->flag & MINUS))
		box->zero = opt->width - box->value_len;
}

static void	boxing_p(t_flag *f, t_box *b)
{
	b->prefix = 'x';
	ft_memcpy(b->base, "0123456789abcdef", (b->base_len = 16));
	b->value_len = ft_numlen((unsigned long long)b->value, b->base_len);
	if (f->prec != -1)
		b->zero = f->prec - b->value_len;
	else if (f->flag & ZERO)
		b->zero = f->width - b->value_len - (b->prefix > 0) * 2;
}

static void	boxing_num(t_flag *opt, t_box *box)
{
	int	tmp;

	if (opt->type & P)
	{
		boxing_p(opt, box);
		return ;
	}
	ft_check(opt, box);
	box->value_len = ft_numlen((unsigned long long)box->value, box->base_len);
	if (box->value == 0)
		box->prefix = 0;
	if (opt->prec == 0 && box->value == 0)
		box->value_len = 0;
	if (opt->prec != -1)
		box->zero = opt->prec - box->value_len;
	else if (opt->flag & ZERO)
	{
		tmp = (box->sign > 0) + (box->prefix > 0) * 2;
		box->zero = opt->width - box->value_len - tmp;
	}
}

static void	boxing_str(t_flag *opt, t_box *box)
{
	box->value_len = 6;
	if (box->value)
		box->value_len = ft_strlen((char *)box->value);
	if (opt->prec != -1 && (opt->prec < box->value_len))
		box->value_len = opt->prec;
	if (opt->flag & ZERO)
		box->zero = opt->width - box->value_len;
}

int	ft_output(t_flag *opt, long long arg)
{
	int		len;
	t_box	box;

	ft_bzero(&box, sizeof(t_box));
	box.value = arg;
	if (opt->type & (PER | C))
		boxing_char(opt, &box);
	else if (opt->type & (D | I | U | H | CH | P))
		boxing_num(opt, &box);
	else if (opt->type & S)
		boxing_str(opt, &box);
	len = box.value_len + ft_max(box.zero, 0);
	len += (box.sign > 0) + (box.prefix > 0) * 2;
	box.margin = ft_max(opt->width - len, 0);
	ft_print_box(opt, &box);
	return (len + box.margin);
}
