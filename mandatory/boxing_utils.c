/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boxing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:59:52 by jonchoi           #+#    #+#             */
/*   Updated: 2022/09/23 03:00:52 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

void	ft_check(t_flag *opt, t_box *box)
{
	if (opt->type & (D | I))
	{
		if (opt->flag & SPACE)
			box->sign = ' ';
		else if (opt->flag & PLUS)
			box->sign = '+';
		if (box->value < 0)
		{
			box->sign = '-';
			box->value *= -1;
		}
	}
	if (opt->flag & HASH && opt->type & H)
		box->prefix = 'x';
	else if (opt->flag & HASH && opt->type & CH)
		box->prefix = 'X';
	if (opt->type & (D | I | U))
		ft_memcpy(box->base, "0123456789", (box->base_len = 10));
	else if (opt->type & (H | P))
		ft_memcpy(box->base, "0123456789abcdef", (box->base_len = 16));
	else if (opt->type & CH)
		ft_memcpy(box->base, "0123456789ABCDEF", (box->base_len = 16));
}

int	ft_numlen(unsigned long long n, int len)
{
	int	i;

	i = 1;
	n /= len;
	while (n > 0)
	{
		n /= len;
		++i;
	}
	return (i);
}
