/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:38:34 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/17 20:07:07 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_linked_lst_env(t_env *env)
{
	t_env *tmp;
	tmp = env;

	while(tmp)
	{
		printf("env_var : %s\n", tmp->env_var);
		printf("env_name : %s\n", tmp->env_name);
		printf("env_value : %s\n", tmp->env_value);
		tmp = tmp->next;
	}
}
t_segment	*ft_lst_last1(t_segment *head)
{
	t_segment	*last_element;

	if (!head)
		return (NULL);
	if (!head->next)
		last_element = head;
	else
	{
		last_element = head;
		while (last_element->next)
			last_element = last_element->next;
	}
	return (last_element);
}

t_redirection	*ft_lst_last2(t_redirection *head)
{
	t_redirection	*last_element;

	if (!head)
		return (NULL);
	if (!head->next)
		last_element = head;
	else
	{
		last_element = head;
		while (last_element->next)
			last_element = last_element->next;
	}
	return (last_element);
}

t_argument	*ft_lst_last3(t_argument *head)
{
	t_argument	*last_element;

	if (!head)
		return (NULL);
	if (!head->next)
		last_element = head;
	else
	{
		last_element = head;
		while (last_element->next)
			last_element = last_element->next;
	}
	return (last_element);
}

size_t	ft_lst_size1(t_segment *head)
{
	size_t		len;
	t_segment	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last1(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}

size_t	ft_lst_size2(t_redirection *head)
{
	size_t					len;
	t_redirection	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last2(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}

size_t	ft_lst_size3(t_argument *head)
{
	size_t				len;
	t_argument	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last3(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}

void	print_e_redirection(int e_redirection, int fd)
{
	if (e_redirection == 0)
		ft_putstr_fd("REDIRECTION_OUTFILE", fd);
	if (e_redirection == 1)
		ft_putstr_fd("REDIRECTION_INFILE", fd);
	if (e_redirection == 4)
		ft_putstr_fd("REDIRECTION_INDEFINED", fd);
	if (e_redirection == 2)
		ft_putstr_fd("REDIRECTION_APPEND", fd);
	if (e_redirection == 3)
		ft_putstr_fd("REDIRECTION_HEREDOC", fd);
	if (e_redirection == 5)
		ft_putstr_fd("REDIRECTION_TEXT", fd);
}

static void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
static void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	ft_putchar_fd((n % 10) + '0', fd);
}


void	ft_native_lst_print(t_command_data command_data, int fd)
{
	size_t					i;
	size_t					j;
	t_segment				*tmp1;
	t_redirection			*tmp2;
	t_argument				*tmp3;

	i = 0;
	tmp1 = command_data.segments;
	while (command_data.segments && i < ft_lst_size1(command_data.segments))
	{
		ft_putstr_fd("segment ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(" : \n", fd);
		j = 0;
		tmp2 = tmp1->redirections;
		while (tmp1->redirections && j < ft_lst_size2(tmp1->redirections))
		{
			ft_putstr_fd("\t-redirection ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			ft_putstr_fd(tmp2->content_to_expand, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-redirection_type ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			print_e_redirection (tmp2->redirection_type, fd);
			ft_putstr_fd("\n", fd);
			tmp2 = tmp2->next;
			j++;
		}
		j = 0;
		tmp3 = tmp1->arguments;
		while (tmp1->arguments && j < ft_lst_size3(tmp1->arguments))
		{
			ft_putstr_fd("\t-argument_to_expand ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : ", fd);
			ft_putstr_fd(tmp3->content_to_expand, fd);
			ft_putstr_fd("\n", fd);
			tmp3 = tmp3->next;
			j++;
		}
		ft_putstr_fd("\n", fd);
		tmp1 = tmp1->next;
		i++;
	}
}

/*void	ft_expanded_lst_print(t_command_line *command_line, int fd)
{
	size_t					i;
	size_t					j;
	t_substring				*tmp1;
	t_expanded_redirection	*tmp2;
	t_expanded_argument		*tmp3;

	i = 0;
	tmp1 = command_line->substrings;
	while (command_line->substrings && i < ft_lst_size1(command_line->substrings))
	{
		ft_putstr_fd("substring ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(" : \n", fd);
		j = 0;
		tmp2 = tmp1->exp_redirections;
		while (tmp1->exp_redirections && j < ft_lst_size4(tmp1->exp_redirections))
		{
			ft_putstr_fd("\t-exp_redirection ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			ft_putstr_fd(tmp2->content, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-exp_redirection_type ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			print_e_redirection (tmp2->e_redirection, fd);
			ft_putstr_fd("\n", fd);
			tmp2 = tmp2->next;
			j++;
		}
		j = 0;
		tmp3 = tmp1->exp_arguments;
		while (tmp1->exp_arguments && j < ft_lst_size5(tmp1->exp_arguments))
		{
			ft_putstr_fd("\t-exp_argument ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : ", fd);
			ft_putstr_fd(tmp3->content, fd);
			ft_putstr_fd("\n", fd);
			tmp3 = tmp3->next;
			j++;
		}
		ft_putstr_fd("\n", fd);
		tmp1 = tmp1->next;
		i++;
	}
}

void	ft_execution_lst_print(t_exec_struct *exec_struct, int fd)
{
	size_t				i;
	size_t				j;
	t_exec_substring	*tmp1;
	t_exec_redirection	*tmp2;
	t_exec_argument		*tmp3;

	i = 0;
	tmp1 = exec_struct->exec_substrings;
	while (exec_struct->exec_substrings && i < ft_lst_size7(exec_struct->exec_substrings))
	{
		ft_putstr_fd("exec_substring ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(" : \n", fd);
		j = 0;
		tmp2 = tmp1->exec_redirections;
		while (tmp1->exec_redirections && j < ft_lst_size8(tmp1->exec_redirections))
		{
			ft_putstr_fd("\t-redirection ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			ft_putstr_fd(tmp2->file, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-redirection_type ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			print_e_redirection (tmp2->e_redirection, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-fd_input ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t\t", fd);
			ft_putnbr_fd(tmp2->fd_input, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-fd_output ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t\t", fd);
			ft_putnbr_fd(tmp2->fd_output, fd);
			ft_putstr_fd("\n", fd);
			tmp2 = tmp2->next;
			j++;
		}
		j = 0;
		tmp3 = tmp1->exec_arguments;
		while (tmp1->exec_arguments && j < ft_lst_size9(tmp1->exec_arguments))
		{
			ft_putstr_fd("\t-argument ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : ", fd);
			ft_putstr_fd(tmp3->argument, fd);
			ft_putstr_fd("\n", fd);
			tmp3 = tmp3->next;
			j++;
		}
		ft_putstr_fd("\n", fd);
		tmp1 = tmp1->next;
		i++;
	}
}

	size_t				i;
	size_t				j;
	t_exec_substring	*tmp1;
	t_exec_redirection	*tmp2;
	t_exec_argument		*tmp3;

	i = 0;
	tmp1 = exec_struct->exec_substrings;
	while (exec_struct->exec_substrings && i < ft_lst_size7(exec_struct->exec_substrings))
	{
		ft_putstr_fd("exec_substring ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(" : \n", fd);
		j = 0;
		tmp2 = tmp1->exec_redirections;
		while (tmp1->exec_redirections && j < ft_lst_size8(tmp1->exec_redirections))
		{
			ft_putstr_fd("\t-redirection ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			ft_putstr_fd(tmp2->file, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-redirection_type ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			print_e_redirection (tmp2->e_redirection, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-fd_input ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t\t", fd);
			ft_putnbr_fd(tmp2->fd_input, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-fd_output ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t\t", fd);
			ft_putnbr_fd(tmp2->fd_output, fd);
			ft_putstr_fd("\n", fd);
			tmp2 = tmp2->next;
			j++;
		}
		j = 0;
		tmp3 = tmp1->exec_arguments;
		while (tmp1->exec_arguments && j < ft_lst_size9(tmp1->exec_arguments))
		{
			ft_putstr_fd("\t-argument ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : ", fd);
			ft_putstr_fd(tmp3->argument, fd);
			ft_putstr_fd("\n", fd);
			tmp3 = tmp3->next;
			j++;
		}
		ft_putstr_fd("\n", fd);
		tmp1 = tmp1->next;
		i++;
	}
}

			ft_putstr_fd(" : \t", fd);
			print_e_redirection (tmp2->e_redirection, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-fd_input ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t\t", fd);
			ft_putnbr_fd(tmp2->fd_input, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-fd_output ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t\t", fd);
			ft_putnbr_fd(tmp2->fd_output, fd);
			ft_putstr_fd("\n", fd);
			tmp2 = tmp2->next;
			j++;
		}
		j = 0;
		tmp3 = tmp1->exec_arguments;
		while (tmp1->exec_arguments && j < ft_lst_size9(tmp1->exec_arguments))
		{
			ft_putstr_fd("\t-argument ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : ", fd);
			ft_putstr_fd(tmp3->argument, fd);
			ft_putstr_fd("\n", fd);
			tmp3 = tmp3->next;
			j++;
		}
		ft_putstr_fd("\n", fd);
		tmp1 = tmp1->next;
		i++;
	}
}

}

void	ft_execution_lst_print(t_exec_struct *exec_struct, int fd)
{
	size_t				i;
	size_t				j;
	t_exec_substring	*tmp1;
	t_exec_redirection	*tmp2;
	t_exec_argument		*tmp3;

	i = 0;
	tmp1 = exec_struct->exec_substrings;
	while (exec_struct->exec_substrings && i < ft_lst_size7(exec_struct->exec_substrings))
	{
		ft_putstr_fd("exec_substring ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(" : \n", fd);
		j = 0;
		tmp2 = tmp1->exec_redirections;
		while (tmp1->exec_redirections && j < ft_lst_size8(tmp1->exec_redirections))
		{
			ft_putstr_fd("\t-redirection ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			ft_putstr_fd(tmp2->file, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-redirection_type ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			print_e_redirection (tmp2->e_redirection, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-fd_input ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t\t", fd);
			ft_putnbr_fd(tmp2->fd_input, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-fd_output ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t\t", fd);
			ft_putnbr_fd(tmp2->fd_output, fd);
			ft_putstr_fd("\n", fd);
			tmp2 = tmp2->next;
			j++;
		}
		j = 0;
		tmp3 = tmp1->exec_arguments;
		while (tmp1->exec_arguments && j < ft_lst_size9(tmp1->exec_arguments))
		{
			ft_putstr_fd("\t-argument ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : ", fd);
			ft_putstr_fd(tmp3->argument, fd);
			ft_putstr_fd("\n", fd);
			tmp3 = tmp3->next;
			j++;
		}
		ft_putstr_fd("\n", fd);
		tmp1 = tmp1->next;
		i++;
	}
}*/

