/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:06:54 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 09:43:13 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_UTILS_H
# define STR_UTILS_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*ft_strchr(char	*s, int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	free_tab(char **tab, int size);
char	**extend_tab(char **tab, int *size, char *elem);
int		min(int a, int b);
int		ft_isspace(char c);
char	*dup_no_newline(char *s);
char	*skip_whitespaces(char *s);
void	ft_bzero(void *p, int n);
char	*dup_line_with_length(char *line, int length);
char	*get_next_line(int fd);
int		ft_strncmp(char *s1, char *s2, size_t n);

#endif
