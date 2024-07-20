/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:47:25 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/20 15:40:58 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_from_quotes(char **remaining_line, char quote)
{
	char	*extracted_line;
	char	*remaining_line_copy;
	int		i;
	
	(*remaining_line)++;
	remaining_line_copy = *remaining_line;
	i = 0;
	while (remaining_line[0][0] && remaining_line[0][0] != quote)
	{
		(*remaining_line)++;
		i++;
	}
	extracted_line = ft_substr(remaining_line_copy, 0, i);
	return (extracted_line);
}

void    expand_argument(t_argument *argument)
{
	char	*extracted_from_quote;
	char	*content_to_expand_copy;

	content_to_expand_copy = argument->content_to_expand;
	while (content_to_expand_copy[0])
	{
		if (content_to_expand_copy[0] == '\'')
		{
			extracted_from_quote = extract_from_quotes(&content_to_expand_copy, content_to_expand_copy[0]);
			argument->expanded_content = ft_strjoin_dup(argument->expanded_content, extracted_from_quote);
		}
		if (content_to_expand_copy[0] == '"')
		{
			extracted_from_quote = extract_from_quotes(&content_to_expand_copy, content_to_expand_copy[0]);
			
		}
		if (content_to_expand_copy[0] == '$')
		{
			
		}
	}
}

void	expand_arguments(t_command_data *command_data)
{
	t_argument	*tmp_arguments;
	t_segment	*tmp_segments;

	tmp_segments = command_data->segments;
	while (tmp_segments)
	{
		tmp_arguments = tmp_segments->arguments;
		while (tmp_arguments)
		{
			
			tmp_arguments = tmp_arguments->next;
		}
		tmp_segments = tmp_segments->next;
	}
}