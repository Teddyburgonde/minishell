/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:51:50 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/17 09:07:08 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	char			*tab;

	tab = s;
	i = 0;
	while (i < n)
	{
		tab[i] = c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*ptr;
	long int	size_alloc;

	size_alloc = nmemb * size;
	if (size_alloc < 0 || ((int)nmemb < 0 && (int)size < 0))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr)
		ft_memset(ptr, '\0', nmemb * size);
	return (ptr);
}

int		ft_strcspn(const char *s, char *reject)
{
	int	i;
	int	j;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		j = 0;
		while (reject[j] != '\0')
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
