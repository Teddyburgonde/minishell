/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:16:43 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/18 17:36:14 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	extract_line_until_next_separator(char **remaining_line, char **extracted_line)
{
	int	len_to_quote;
	int	len_to_next_separator;

	len_to_quote = ft_strcspn(*remaining_line, "\'\"");
	len_to_next_separator = ft_strcspn(*remaining_line, "| <>\t\n\0");
	if (len_to_next_separator <= len_to_quote)
	{
		*extracted_line = ft_substr(*remaining_line, 0, len_to_next_separator);
//		printf("remain_line %s\n", *remaining_line);
//		printf("len separator %d\n", len_to_next_separator);
//		exit(1);
		//printf("extracted_line %s\n", *extracted_line);
		*remaining_line += len_to_next_separator;
//		printf("remain_line %s\n", *remaining_line);

	}
	else
	{
		printf("create a function when there is a quote in remaining_line\n");	
	}
	return (0);
}

int	extract_line(char **remaining_line, char **extracted_line)
{
	if (*remaining_line[0] == '\'')
	{
		printf("simple quote\n");
		// function extract_line_until_next_simple_quote
		// if error, return 1;
	}
	else if (*remaining_line[0] == '\"')
	{
		printf("double quote\n");
		// function extract_line_until_next_double_quote
		// if error, return 1;
		
	}
	else 
	{
		extract_line_until_next_separator(remaining_line, extracted_line);
		// if error, return 1;
	}
	return (0);
}