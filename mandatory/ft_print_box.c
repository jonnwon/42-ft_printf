/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:07:23 by jonchoi           #+#    #+#             */
/*   Updated: 2022/09/23 05:20:49 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar_n(char chr, int n)
{
	while (n > 0)
	{
		write(1, &chr, 1);
		n--;
	}
}

static void	ft_putstr_len(char *str, int len)
{
	if (str == 0)
		write(1, "(null)", len);
	else
		write(1, str, len);
}

static void	ft_putnbr_base(unsigned long long n, char *base, int base_len)
{
	if (n > (unsigned long long)base_len - 1)
		ft_putnbr_base(n / base_len, base, base_len);
	ft_putchar_n(base[n % base_len], 1);
}

void	ft_print_box(t_flag *flag, t_box *box)
{
	if (!(flag->flag & MINUS))
		ft_putchar_n(' ', box->margin);
	if (box->sign)
		ft_putchar_n(box->sign, 1);
	if (box->prefix)
	{
		ft_putchar_n('0', 1);
		ft_putchar_n(box->prefix, 1);
	}
	if (box->zero)
		ft_putchar_n('0', box->zero);
	if (flag->type & (PER | C))
		ft_putchar_n((char)box->value, 1);
	else if (flag->type & S)
		ft_putstr_len((char *)box->value, box->value_len);
	else if (box->value_len)
		ft_putnbr_base(box->value, box->base, box->base_len);
	if (flag->flag & MINUS)
		ft_putchar_n(' ', box->margin);
}
