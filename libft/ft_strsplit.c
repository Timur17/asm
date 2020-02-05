/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:41:54 by wtorwold          #+#    #+#             */
/*   Updated: 2020/02/01 11:47:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *str, char c)
{
	int		count;
	char	**arr;
	int		index;

	if (str == NULL)
		return (NULL);
	count = ft_countword(str, c);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (arr == NULL)
		return (NULL);
	index = 0;
	while (count > index)
	{
		arr[index] = (char *)ft_arrmem(str, index + 1, c);
		index++;
	}
	arr = ft_arrsplit(str, count, arr, c);
	return (arr);
}
