/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:13:38 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/16 20:13:51 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exit(t_env **env, t_vars *vars)
{
	int	exit_code;

	exit_code = vars->exit_code;
	ft_lstclear_env(env);
	free(vars);
	exit(exit_code);
}
