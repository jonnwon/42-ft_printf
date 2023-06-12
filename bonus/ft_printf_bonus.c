/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:43:40 by jonchoi           #+#    #+#             */
/*   Updated: 2022/09/26 16:50:11 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_count_print(char *form, va_list ap)
{
	int			result;
	t_flag		*opt;
	long long	arg;

	result = 0;
	opt = (t_flag *)malloc(sizeof(t_flag));
	if (!opt)
		return (0);
	ft_bzero(opt, sizeof(t_flag));
	while (*form)
	{
		if (*form == '%' && ft_parsing(&form, opt, ap))
		{
			if (opt->error)
				break ;
			arg = ft_arg(opt, ap);
			result += ft_output(opt, arg);
		}
		else
			result += write(1, form++, 1);
	}
	free(opt);
	return (result);
}

int	ft_printf(const char *form, ...)
{
	int		result;
	va_list	ap;

	result = 0;
	va_start(ap, form);
	result = ft_count_print((char *)form, ap);
	va_end(ap);
	return (result);
}
