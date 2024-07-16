/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:23:17 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/16 18:06:09 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_sig = 0;

int	main(int ac, char **av, char *envp[])
{
	//int		exit;
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
	if (env == NULL)
		return (1);
	run_signals();
	// exit = run_readline(env, vars);
	// ft_lstclear_env(&env);
	// free(vars);
	//return (exit);
}