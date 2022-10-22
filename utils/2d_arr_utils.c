/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_arr_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:25:01 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 09:08:35 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/str_utils.h"

void	free_tab(char **tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(tab[i]);
	free(tab);
}

char	**extend_tab(char **tab, int *size, char *elem)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (*size + 2));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < *size)
		new[i] = tab[i];
	new[i++] = dup_no_newline(elem);
	free(elem);
	new[i] = NULL;
	(*size)++;
	free(tab);
	return (new);
}
