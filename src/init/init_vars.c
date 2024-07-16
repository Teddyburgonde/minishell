/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:10:54 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/16 18:14:32 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_vars(t_vars *vars)
{
	vars->env = NULL;
	//vars->exit = FALSE;
	vars->exit_code = 0;
	vars->exit_code_signal = 0;
}