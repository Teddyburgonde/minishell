/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:23:17 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/16 21:34:09 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// function initialisation des structures ( malloc, char * NULL et pointer NULL) regarder la valeur de retour 
// function si allocation echoue message error , free, exit
// reprendre ft_strcspn 
// ft_lstnew
// ft_lstdel_one
// ft_lstaddback
// ft_lstlast ( si besoin )
// ft_lstsize 
// function print command_line


int	g_sig = 0;

static int	ft_readline(t_env **env, t_vars *vars)
{
	char							*command_line;

	command_line = NULL;
	while (1)
	{
		if (vars->exit == 1)
			free_exit(env, vars);
		if (command_line)
			free(command_line);
		command_line = NULL;
		set_interactive_mode(1);
		command_line = readline("minishell ~ ");
		set_interactive_mode(2);
		if (!command_line)
		{
			ft_putstr_fd("exit\n", 2);
			if (command_line)
				free(command_line);
			break ;
		}
		//command_line = verif_command_line(command_line, env, vars);
	}
	return (vars->exit_code);
}

int	run_readline(t_env *env, t_vars *vars)
{
	int	exit;

	exit = ft_readline(&env, vars);
	if (exit == 1)
	{
		ft_lstclear_env(&env);
		free(vars);
		return (1);
	}
	return (exit);
}

int	main(int ac, char **av, char *envp[])
{
	int		exit;
	t_env	*env;
	t_vars	*vars;

	(void)av;
	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (1);
	env = NULL;
	init_vars(vars);
	if (ac != 1)
	{
		ft_putstr_fd("Error: Too much arguments\n", 2);
		free(vars);
		return (1);
	}
	init_env(&env, envp);
	//print_linked_lst_env(env);
	if (env == NULL)
		return (1);
	run_signals();
	
	exit = run_readline(env, vars);
	// ft_lstclear_env(&env);
	// free(vars);
	return (exit);
}


