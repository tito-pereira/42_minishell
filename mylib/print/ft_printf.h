/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:53:47 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/11 10:37:44 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "../lib/libft.h"

struct	s_params
{
	int		size;
	char	*str;
	int		*i;
	int		psize;
	int		pex;
};

typedef struct s_params	t_pain;

int		ft_printf(const char *s, ...);
int		normie(va_list args, int *c, t_pain bois);
int		see_if_spec(char c);
int		ff_strlen(char *str); //aqui, ft_strlen
int		ft_strlen_p(char *str, int psize);
void	ft_putstr(char *str);
int		ft_putstr_c(char *str);
int		ft_putstr_c_p(char *str, int psize);
void	ft_putchar(char c);
int		ft_putchar_c(char c);
void	ft_putnbr_c(int n, int *c);
void	ft_putnbr_pos(int n, int *c);
void	ft_put_uns_nbr(unsigned int n, int *c);
char	check_letter_p(long unsigned int i);
void	ft_putphex_c(long unsigned int n, int *c);
char	*f_itoa(int n);
char	*ft_long_itoa(unsigned int n);
char	*ft_hbx_itoa(unsigned int n);
char	*ft_hx_itoa(unsigned int n);
char	*ft_lhx_itoa(long unsigned int n);
char	check_letter_x(unsigned int i);
void	ft_puthex_c(unsigned int n, int *c);
char	check_letter_bx(unsigned int i);
void	ft_putbhex_c(unsigned int n, int *c);
int		ft_c_spec(va_list arg);
int		ft_s_spec(va_list arg, t_pain bois);
int		ft_p_spec(va_list arg, char f);
int		ft_d_spec(va_list arg, char f, t_pain bois);
int		ft_u_spec(va_list arg, t_pain bois);
int		ft_x_spec(va_list arg, char f, t_pain bois);
int		ft_bx_spec(va_list arg, char f, t_pain bois);
char	ft_control_flag(char *str, int *i);
char	ft_check_spec(char *str, int *j);
char	ft_check_d(char *s, int *j);
char	ft_check_x(char *s, int *j);
char	p_control_flag(char *str, int *i);
char	p_check_spec(char *str, int *j);
char	p_check_spec_2(char *str, int *j);
char	p_check_d(char *s, int *j);
char	p_check_x(char *s, int *j);
int		ip_c_spec(va_list arg, t_pain bois);
int		ip_s_spec(va_list arg, t_pain bois);
int		ip_p_spec(va_list arg, t_pain bois);
int		ip_d_spec(va_list arg, t_pain bois);
int		ip_p_spec_null(void *tmp, t_pain bois);
int		ip_u_spec(va_list arg, t_pain bois);
int		ip_x_spec(va_list arg, t_pain bois);
int		ip_bx_spec(va_list arg, t_pain bois);
char	*p_null_support(long unsigned int tmp, t_pain *bois, char *ito);
void	d_support(t_pain *bois, char f1, int tmp, int *c);
int		p_c_spec_r(int tmp, int size, char pad);
int		p_s_spec_r(char *tmp, t_pain bois, char pad);
int		p_p_spec_zeros(long unsigned int i, int size, char pad, char f1);
int		p_d_spec_space_m(int tmp, t_pain bois, char pad, char f1);
int		p_d_spec_space_f(int tmp, t_pain bois, char pad, char f1);
int		p_u_spec_left(unsigned int tmp, t_pain bois, char pad);
int		p_x_spec_space_f(unsigned int tmp, t_pain bois, char pad, char f1);
int		p_x_spec_space_m(unsigned int tmp, t_pain bois, char pad, char f1);
int		p_bx_spec_space_f(unsigned int tmp, t_pain bois, char pad, char f1);
int		p_bx_spec_space_m(unsigned int tmp, t_pain bois, char pad, char f1);
int		p_c_spec_l(int tmp, int size, char pad);
int		p_s_spec_l(char *tmp, t_pain bois, char pad);
int		p_p_spec_space_m(long unsigned int i, int size, char pad, char f1);
int		p_p_spec_space_f(long unsigned int i, int size, char pad, char f1);
int		p_d_spec_zero(int tmp, t_pain bois, char pad, char f1);
int		p_u_spec_right(unsigned int tmp, t_pain bois, char f2);
int		p_x_spec_zero(unsigned int tmp, t_pain bois, char pad, char f1);
int		p_bx_spec_zero(unsigned int tmp, t_pain bois, char pad, char f1);
int		ft_check_mw(char *str, int *i);
int		c_valid_min_w(char *str, int *j);
int		c_valid_point(char *str, int *j);
int		c_valid_mw_point(char *str, int *j);
int		ft_check_if_one(char *str, int *j);
int		ft_check_if_s(char *str, int *j);
int		ft_mini_atoi(char *str, int *j);
char	ft_check_z_m(char *str, int *j);
int		check_mw_size(char *str, int *i);
int		check_point_size(char *str, int *i);
void	death_star(va_list args, char *str, int *j, int *c);
int		pain(va_list args, int *c, t_pain bois);
int		write_right(va_list args, t_pain bois);
int		write_left(va_list args, t_pain bois);
int		ft_inic(va_list args, t_pain bois);

#endif
