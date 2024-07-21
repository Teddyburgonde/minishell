/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:47:25 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/21 16:19:46 by tebandam         ###   ########.fr       */
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

char	*expand_in_double_quotes(t_command_data *command_data, char *extracted)
{
	char	*return_value;
	char	*extracted_copy;
	char	*tmp;
	int		i;
	
	return_value = NULL;
	while (extracted[0])
	{
		i = 0;
		extracted_copy = extracted;
		while (extracted[0] && extracted[0] != '$')
		{
			extracted++;
			i++;
		}
		if (i != 0)
		{
			tmp = ft_substr(extracted_copy, 0, i);
			return_value = ft_strjoin_dup(return_value, tmp);
			extracted_copy = extracted;
			i = 0;
		}
		if (extracted[0] == '$')
		{
			extracted++;
			while (extracted[0] && ft_isspace(extracted[0]) == 0 && extracted[0] != '\'' && extracted[0] != '$')
			{
				extracted++;
				i++;
			}
			tmp = ft_substr(extracted_copy, 1, i);
			tmp = make_expansion(command_data, &tmp);
			return_value = ft_strjoin_dup(return_value, tmp);
		}
	}
	if (!return_value)
		return(ft_strdup(""));
	return (return_value);
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
			extracted = expand_in_double_quotes(command_data, extracted);
			argument->expanded_content = ft_strjoin_dup(argument->expanded_content, extracted);
		}
		if (content_to_expand_copy[0] == '$')
		{
			content_to_expand_copy++;
			extracted = make_expansion(command_data, &content_to_expand_copy);
			argument->expanded_content = ft_strjoin_dup(argument->expanded_content, extracted);
		}
		else
		{
			extracted = get_var_to_expand(&content_to_expand_copy);
			argument->expanded_content = ft_strjoin_dup(argument->expanded_content, extracted);
		}
	}
}

int	check_ambiguous_redirection(t_command_data *command_data, char *line)
{
	t_env	*tmp_env;
	char	*var;

	tmp_env = command_data->env;
	var = get_var_to_expand(&line);
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->env_name, var) != 0)
		{
			tmp_env = tmp_env->next;
			continue ;
		}
		else
		{
			if (tmp_env->env_value != NULL && tmp_env->env_value[0] != '\0')
				return (0);
		}
		tmp_env = tmp_env->next;
	}
	return (1);
}

int	expand_redirection(t_command_data *command_data, t_redirection *redirection)
{
	char	*extracted;
	char	*content_to_expand_copy;

	content_to_expand_copy = redirection->content_to_expand;
	while (content_to_expand_copy[0])
	{
		if (content_to_expand_copy[0] == '\'')
		{
			extracted = extract_from_quotes(&content_to_expand_copy, content_to_expand_copy[0]);
			redirection->expanded_content = ft_strjoin_dup(redirection->expanded_content, extracted);
		}
		if (content_to_expand_copy[0] == '"')
		{
			extracted = extract_from_quotes(&content_to_expand_copy, content_to_expand_copy[0]);
			if (redirection->redirection_type != REDIRECTION_HEREDOC)
				extracted = expand_in_double_quotes(command_data, extracted);
			redirection->expanded_content = ft_strjoin_dup(redirection->expanded_content, extracted);
		}
		if (content_to_expand_copy[0] == '$' && redirection->redirection_type != REDIRECTION_HEREDOC)
		{
			content_to_expand_copy++;
			if (check_ambiguous_redirection(command_data, content_to_expand_copy) == 1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(content_to_expand_copy, 2);
				ft_putstr_fd(" : Ambiguous redirect\n", 2);
				command_data->exit_code = 1;
				return (1);
			}
			extracted = make_expansion(command_data, &content_to_expand_copy);
			redirection->expanded_content = ft_strjoin_dup(redirection->expanded_content, extracted);
		}
		else
		{
			if (content_to_expand_copy[0] == '$' && redirection->redirection_type == REDIRECTION_HEREDOC)
			{
				content_to_expand_copy++;
				extracted = ft_strdup("$");
				extracted = ft_strjoin_dup(extracted, get_var_to_expand(&content_to_expand_copy));
			}
			else
				extracted = get_var_to_expand(&content_to_expand_copy);
			redirection->expanded_content = ft_strjoin_dup(redirection->expanded_content, extracted);
		}
	}
	return (0);
}

int	expand(t_command_data *command_data)
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
			if (expand_redirection(command_data, tmp_redirections))
				return (1);
			tmp_redirections = tmp_redirections->next;
		}
		tmp_segments = tmp_segments->next;
	}
	return (0);
}