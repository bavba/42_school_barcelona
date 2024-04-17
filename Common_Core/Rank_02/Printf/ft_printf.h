/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:10:35 by aricalle          #+#    #+#             */
/*   Updated: 2023/08/31 16:10:39 by aricalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
int		ft_print_char(char c, int *len);
void	ft_print_string(char *s, int *len);
void	ft_print_number(int a, int *len);
void	ft_print_unsigned(unsigned int b, int *len);
void	ft_print_hex(int n, int *len, char c);
void	ft_print_pointer(unsigned long p, int *len);

#endif