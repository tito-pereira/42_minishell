/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:52:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 00:52:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*get_next_line(int fd);
size_t	ft_strlen2(const char *s);
char	*ft_strchr2(const char *str, int c);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strtrim_l(char *bufftxt);
char	*ft_strtrim_r(char *bufftxt);
char	*ft_get_text(int fd, char *bufftxt);

#endif
