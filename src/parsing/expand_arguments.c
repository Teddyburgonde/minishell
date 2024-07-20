/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:47:25 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/20 19:20:29 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	search_leng(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	fill_str(char *str, int n, size_t len)
{
	size_t	i;

	str[len] = '\0';
	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		i = 1;
	}
	while (len > i)
	{
		len--;
		if (n < 0)
		{
			str[len] = n % 10 * (-1) + '0';
			n = n / 10;
		}
		else
		{
			str[len] = n % 10 + '0';
			n = n / 10;
		}
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	len = search_leng(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	fill_str(str, n, len);
	return (str);
}


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
	(*remaining_line)++;
	extracted_line = ft_substr(remaining_line_copy, 0, i);
	return (extracted_line);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
}
char	*get_var_to_expand(char **remaining_line)
{
	char	*remaining_line_copy;
	char	*return_value;
	int		i;

	remaining_line_copy = *remaining_line;
	i = 0;
	while (remaining_line[0][0] && ft_strcspn(*remaining_line, "'\"$") != 0)
	{
		(*remaining_line)++;
		i++;
	}
	return_value = ft_substr(remaining_line_copy, 0, i);
	return (return_value);
}

char	*make_expansion(t_command_data *command_data, char **remaining_line)
{
	t_env	*tmp_env;
	char	*var_to_expand;

	if (!remaining_line[0][0])
		return (ft_strdup("$"));
	if (remaining_line[0][0] == '$')
	{
		(*remaining_line)++;
		return (ft_strdup("$"));
	}
	else
	{
		if (remaining_line[0][0] == '?')
		{
			(*remaining_line)++;
			return (ft_itoa(command_data->exit_code));
		}
		var_to_expand = get_var_to_expand(remaining_line);
		tmp_env = command_data->env;
		while (tmp_env)
		{
			if (ft_strcmp(tmp_env->env_name, var_to_expand) == 0)
				return (ft_strdup(tmp_env->env_value));
			tmp_env = tmp_env->next;
		}
	}
	return (ft_strdup(""));
}

void    expand_argument(t_command_data *command_data, t_argument *argument)
{
	char	*extracted;
	char	*content_to_expand_copy;

	content_to_expand_copy = argument->content_to_expand;
	while (content_to_expand_copy[0])
	{
		if (content_to_expand_copy[0] == '\'')
		{
			extracted = extract_from_quotes(&content_to_expand_copy, content_to_expand_copy[0]);
			argument->expanded_content = ft_strjoin_dup(argument->expanded_content, extracted);
		}
		if (content_to_expand_copy[0] == '"')
		{
			extracted = extract_from_quotes(&content_to_expand_copy, content_to_expand_copy[0]);
			
		}
		if (content_to_expand_copy[0] == '$')
		{
			content_to_expand_copy++;
			extracted = make_expansion(command_data, &content_to_expand_copy);
			argument->expanded_content = ft_strjoin_dup(argument->expanded_content, extracted);
			printf("exp_content : %s\n",argument->expanded_content);	
		}
		else
		{
			extracted = get_var_to_expand(&content_to_expand_copy);
			argument->expanded_content = ft_strjoin_dup(argument->expanded_content, extracted);
		}
	}
}

void	expand(t_command_data *command_data)
{
	t_segment		*tmp_segments;
	t_argument		*tmp_arguments;
	t_redirection	*tmp_redirections;

	tmp_segments = command_data->segments;
	while (tmp_segments)
	{
		tmp_arguments = tmp_segments->arguments;
		tmp_redirections = tmp_segments->redirections;
		while (tmp_arguments)
		{
			expand_argument(command_data, tmp_arguments);
			tmp_arguments = tmp_arguments->next;
		}
		while(tmp_redirections)
		{
			// expand redirection;
			tmp_redirections = tmp_redirections->next;
		}
		tmp_segments = tmp_segments->next;
	}
}