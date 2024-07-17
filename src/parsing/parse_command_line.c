/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:40:03 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/17 21:01:02 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}


int	count_redirection_symbol(char *str)
{
	int	count;

	count = 0;
//	while (str && (*str == '<' || *str == '>' || ft_isspace(*str) == 1))
	while (str && (*str == '<' || *str == '>'))
	{
		if (*str == '<' || *str == '>')
			count++;
		str++;
	}
	return (count);
}

e_redirection_type	get_redirection_type(char **str)
{
	if (count_redirection_symbol(*str) > 2)
		return(UNASIGNED);
	else if (count_redirection_symbol(*str) == 2)
	{
		if (str[0][0] == '<' && str[0][1] == '<')
			return (REDIRECTION_HEREDOC);
		else if (str[0][0] == '>' && str[0][1] == '>')
			return (REDIRECTION_APPEND);
		else
			return (UNASIGNED);
		*str += 2;
	}
	else if (count_redirection_symbol(*str) == 1)
	{
		if (str[0][0] == '<')
			return (REDIRECTION_INFILE);
		else if (str[0][0] == '>')
			return (REDIRECTION_OUTFILE);
		*str += 1;
	}
	return (UNASIGNED);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*tab;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	j = ft_strlen(s + start);
	if (j < len)
		len = j;
	tab = malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = s[start + i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}



int	extract_line_until_next_separator(char **remaining_line, char **extracted_line)
{
	int	len_to_quote;
	int	len_to_next_separator;

	len_to_quote = ft_strcspn(*remaining_line, "\'\"");
	len_to_next_separator = ft_strcspn(*remaining_line, "| <>\t\n\0");
	if (len_to_next_separator <= len_to_quote)
	{
		*extracted_line = ft_substr(*remaining_line, 0, len_to_next_separator);
		printf("remain_line %s\n", *remaining_line);
		printf("len separator %d\n", len_to_next_separator);
		exit(1);
		//printf("extracted_line %s\n", *extracted_line);
		*remaining_line += len_to_next_separator;
		printf("remain_line %s\n", *remaining_line);

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

int    get_redirection(t_command_data *command_data, t_segment *segment, char **remaining_line)
{
	e_redirection_type	redirection_type;
	char				*extracted_line;
	t_redirection		*new_redirection;

	redirection_type = get_redirection_type(remaining_line);
	remaining_line += 1;
	if (redirection_type == UNASIGNED)
	{
		ft_putstr_fd("Syntax error\n", 2);
		command_data->exit_code = 2;
		return (1);
	}
	printf("remain_line %s\n", *remaining_line);
	*remaining_line = skip_whitespace(*remaining_line);
	if (*remaining_line)
	{
		if (extract_line(remaining_line, &extracted_line) != 0)
		{
			ft_putstr_fd("Syntax error\n", 2);
			command_data->exit_code = 2;
			return (1);
		}
	}
	else
	{
		ft_putstr_fd("Syntax error\n", 2);
		command_data->exit_code = 2;
		return (1);
	}
	new_redirection = ft_lstnew_redirection(extracted_line, redirection_type);
	ft_lstadd_back_redirection(&segment->redirections, new_redirection);
	return (0);	
}



void parse_command_line(t_command_data *command_data, char *line)
{
	t_segment   *segment;
	char		*remaining_line;

	remaining_line = skip_whitespace(line);
	while (remaining_line)
	{
		segment = ft_lstnew_segment();
		ft_lstadd_back_segment(&command_data->segments, segment);
		while (remaining_line && *remaining_line != '|')
		{
			if (*remaining_line == '<' || *remaining_line == '>')
			{
				if (get_redirection(command_data, segment, &remaining_line) != 0)
				{
					// function all free
					return ; 
				}
			}   
		}
				
		remaining_line = skip_whitespace(remaining_line);
		ft_native_lst_print(*command_data, 2);
	}
}
