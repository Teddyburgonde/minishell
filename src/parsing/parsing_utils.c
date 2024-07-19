/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:16:43 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/19 17:56:02 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_skip_quote(char **str, char quote)
{
	int	i;

	i = 1;
	(*str)++;
	while (str[0][0] && str[0][0] != quote)
	{
		(*str)++;
		i++;
	}
	return (i);
}

int	extract_line(char **remaining_line, char **extracted_line)
{
	int		i;
	char	quote;
	char	*remaining_line_copy;

	i = 0;
	remaining_line_copy = *remaining_line;
	while (ft_strcspn(*remaining_line, " |\t\n<>\0") != 0)
	{
		if (remaining_line[0][0] == '\'' || remaining_line[0][0] == '\"')
		{
			quote = remaining_line[0][0];
			i += ft_skip_quote(remaining_line, quote);
			if (remaining_line[0][0] != quote)
				return (1);
		}
		(*remaining_line)++;
		i++;	
	}
	if (i == 0)
		return(1);
	*extracted_line = ft_substr(remaining_line_copy, 0, i);
	return (0);
}
