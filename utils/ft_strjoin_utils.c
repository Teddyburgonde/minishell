/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:31:47 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/20 15:33:39 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_dup(char *s1, char *s2)
{
	char	*tab;
	int		i;
	int		j;
	
	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	tab = malloc((1 + ft_strlen(s1) + ft_strlen(s2)) * sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	tab = ft_strcpy(tab, s1);
	while (s2 && s2[j])
	{
		tab[i] = s2[j];
		j++;
		i++;
	}
	tab[i] = 0;
	free(s1);
	free(s2);
	return (tab);
}

char	*ft_strjoin(char const *s1, char *s2)
{
	char	*tab;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (0);
	tab = malloc((1 + ft_strlen(s1) + ft_strlen(s2)) * sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		tab[i] = s2[j];
		j++;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*tab;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	tab = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tab)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tab[i + j] = s2[j];
		j++;
	}
	tab[i + j] = '\0';
	free(s1);
	s1 = NULL;
	return (tab);
}
