/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:59 by axlee             #+#    #+#             */
/*   Updated: 2024/08/22 17:03:07 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	size;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen(s1);
	while (size && ft_strchr(set, s1[size]))
		size--;
	if (!size)
		return (ft_strdup(""));
	ret = ft_substr(s1, 0, size + 1);
	return (ret);
}*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen((char *)s1) - 1;
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	while (end > start && ft_strchr(set, s1[end]) && s1[end])
		end--;
	trimmed = ft_substr(s1, start, end - start + 1);
	return (trimmed);
}
