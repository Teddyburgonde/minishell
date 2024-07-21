/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:23:17 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/21 16:28:54 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_sig = 0;

// mettre function si allocation echoue message error , free, exit

// function print command_line

static void	ft_readline(t_command_data *command_data)
{
	char							*line;

	while (1)
	{
		line = readline("minishell ~ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			// function free_all
			break ;
		}
		if (parse_command_line(command_data, line) == 1)
		{
			free_segments_struct(command_data->segments);
			command_data->segments = NULL;
			free(line);
			continue ;
		}
		if (expand(command_data))
		{
			free_segments_struct(command_data->segments);
			command_data->segments = NULL;
			free(line);
			continue ;
		}
		free(line);
		ft_native_lst_print(*command_data, 2);
		ft_expanded_lst_print(command_data, 2);
		free_segments_struct(command_data->segments);
		command_data->segments = NULL;
	}
}

int	main(int ac, char **av, char *envp[])
{
	t_command_data	command_data;
	command_data.env = NULL;
	command_data.segments = NULL;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("Error: Too much arguments\n", 2);
		return (1);
	}
	if(init_env(&command_data.env, envp) == 1)
		return (1);
	command_data.exit_code = 0;
	run_signals();
	ft_readline(&command_data);
	return (command_data.exit_code);
}
