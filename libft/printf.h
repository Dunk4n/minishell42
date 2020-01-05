/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:12:52 by niduches          #+#    #+#             */
/*   Updated: 2019/10/28 14:37:29 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>

# define HEX "0123456789abcdef"
# define UHEX "0123456789ABCDEF"
# define CONVERSIONS "cspdiuxX%nfge"
# define FLAGS "-0.*lh\'# +"
# define NB_FLAGS 10

int				ft_printf(const char *str, ...);
size_t			ft_putnstr(const char *str, size_t n);
int				ft_isflag(char c);
int				ft_isconv(char c);
int				ft_makeconv(const char *str, int *size, va_list list,
size_t nb_print);
void			get_flags(int *flags, const char *str, size_t size,
va_list list);
int				conv_char(va_list list, int *flags);
int				conv_str(va_list list, int *flags);
int				conv_ptr(va_list list, int *flags);
int				conv_int(va_list list, int *flags);
int				conv_uint(va_list list, int *flags);
int				conv_hex(va_list list, int *flags);
int				conv_uhex(va_list list, int *flags);
int				conv_nb_print_char(va_list list, int *flags);
int				conv_float_print(double nb, int *flags, int round);
int				conv_sct_print(double nb, int *flags, int round);
int				conv_g(va_list list, int *flags);
int				make_g(double nb, int *flags);
size_t			put_long_nbr(long long nb, int len, int nb_c);
double			float_round(double nb, int *flags, int round);

#endif
