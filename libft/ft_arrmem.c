/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:41:54 by wtorwold          #+#    #+#             */
/*   Updated: 2020/02/01 11:49:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_arrmem(char const *str, int index, char c)
{
	int		count;
	int		word;

	word = 0;
	while (*str != '\0')
	{
		count = 0;
		if (*str == c)
			str++;
		else
		{
			while (*str != '\0' && *str != c)
			{
				str++;
				count++;
			}
			word++;
			if (word == index)
				break ;
		}
	}
	return (NULL);
}
