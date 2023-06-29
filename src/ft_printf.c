/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r-afonso < r-afonso@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:45:08 by r-afonso          #+#    #+#             */
/*   Updated: 2023/06/28 19:46:07 by r-afonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// conversões a lidar cspdiuxX%
#include "../include/printf.h"

static int	print_cs(char **str, va_list args)
{
	int		number_c;
	char	param_c;
	char	*param_str;

	number_c = -1;
	if (**str == 'c')
	{
		param_c = va_arg(args, int);
		write(1, &param_c, 1);
		(*str)++;
		number_c += 2;
	}
	else if (**str == 's')
	{
		param_str = va_arg(args, char *);
		while (++number_c, *param_str)
		{
			write(1, param_str, 1);
			param_str++;
		}
		(*str)++;
	}
	return (number_c);
}

static int	print_di(char **str, va_list args)
{
	int	param_c;

	param_c = va_arg(args, long int);
	ft_putnbr_fd(param_c, 1);
	return (ft_strlen((char *)param_c));
}

static int	print_x(char **str, va_list args)
{
	return (0);
}

static int	print_p(char **str, va_list args)
{
	return (0);
}



static int	print_control(char **str, va_list args)
{
	int	number_c;

	(*str)++;
	// OK
	if (**str == 'c' || **str == 's')
		number_c = print_cs(str, args);
	else if (**str == 'x' || **str == 'X')
		number_c = print_x(str, args);
	else if (**str == 'p')
		number_c = print_p(str, args);
	else if (**str == 'd' || **str == 'i')
		number_c = print_di(str, args);
	else
	{
		if (**str == '%')
			write(1, "%", 1);
		number_c = 1;
	}
	return (number_c);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		number_printed;

	number_printed = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str != '%')
		{
			write(1, str, 1);
			str++;
		}
		else
			number_printed += print_control((char **)&str, args);
	}
	va_end(args);
	return (number_printed);
}