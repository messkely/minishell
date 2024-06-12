/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:35:30 by messkely          #+#    #+#             */
/*   Updated: 2024/06/08 11:38:55 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*new_s;
	size_t				i;

	new_s = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (new_s[i] == (unsigned char)c)
			return ((void *)&new_s[i]);
		i++;
	}
	return (0);
}
