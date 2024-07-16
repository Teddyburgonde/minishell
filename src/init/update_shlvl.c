/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:43:39 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/16 18:21:58 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	adjust_shlvl(int shlvl)
{
	if (shlvl > 255 || shlvl <= 0)
		return (1);
	else
		return (shlvl);
}

static int	calculate_length(int shlvl)
{
	int		tmp;
	int		len;

	len = 0;
	tmp = shlvl;
	while (tmp / 10 != 0)
	{
		tmp /= 10;
		len++;
	}
	if (shlvl > 9 && (shlvl % 10 == 0 || tmp != 0))
		len++;
	if (shlvl % 10 != 0 && shlvl < 10)
		len++;
	return (len);
}

static char	*convert_to_string(int shlvl, int len)
{
	char	*result;

	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len != 0)
	{
		if (len > 1)
			result[len - 1] = shlvl % 10 + '0';
		else
			result[len - 1] = shlvl + '0';
		shlvl /= 10;
		len--;
	}
	return (result);
}

char	*update_shlvl(int shlvl)
{
	char	*result;
	int		len;

	shlvl = adjust_shlvl(shlvl);
	len = calculate_length(shlvl);
	result = convert_to_string(shlvl, len);
	return (result);
}
