/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:08 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/04 23:03:09 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_general(t_shell *general)
{
	general->tok_lst = NULL;
	general->env_lst = NULL;
	general->cmd_lst = NULL;
	general->doll_lst = (t_dollar *)malloc(sizeof(t_dollar));
	general->sorted_env_lst = NULL;
	general->sg_quote = 0;
	general->db_quote = 0;
	general->pipe_index = 0;
	general->pipe_count = 0;
	general -> original_stdin = dup(STDIN_FILENO);
	general -> original_stdout = dup(STDOUT_FILENO);
}

int	init_input(char *input, t_shell *general)
{
	static int	index;

	while (1)
	{
		index = 0;
		init_signal(1);
		input = readline("\033[38;5;51m\033[48;5;16mminisHell:\033[0m ");
		if (input && input[0] != '\0')
		{
			add_history(input);
			if (init_tokens_cmds(input, general, 0, 0) == 0)
			{
				execution(general, index);
				cmd_free(general);
				close_pipes(general->fd, general->pipe_count);
			}
			free(input);
		}
		else if (input && input[0] == '\0')
			free(input);
		else if (!input)
			clean_gen_exit(general, get_exit_status(), 0, 1);
		free_fd(general);
	}
	return (free(input), get_exit_status());
}

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		printf("context: %s\n type: %d\n", current->context, current->type);
		current = current->next;
	}
}

int	init_tokens_cmds(char *input, t_shell *g, int i, int flag)
{
	int	st;

	st = 0;
	if (process_input_validation(g, input, &i) == -1)
		return (-1);
	while (flag >= 0 && input[i] != '\0')
	{
		if (flag >= 0 && input[i] && (is_not_symbol(input[i], 1) == 1))
			flag = init_op_token(input, &i, &g->tok_lst);
		else
		{
			st = i;
			while (flag >= 0 && input[i] && (is_not_symbol(input[i], 0) == 1))
				i++;
			if (input[i] && flag >= 0)
				flag = check_cut_quotes(g, &input, &i, st);
			else if (i > st)
				add_token_list(&g->tok_lst, my_substr(input, st, i - st), 0);
			if (i > 0)
				i--;
		}
		if (check_flag_incr_input(g, input, &i, flag) == -1)
			return (-1);
	}
	return (cmd_stuff(g), 0);
}

t_cmd_lst	*initialize_new_cmd(void)
{
	t_cmd_lst	*new_cmd;

	new_cmd = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	new_cmd->cmd = NULL;
	new_cmd->args = NULL;
	new_cmd->next = NULL;
	new_cmd->heredoc = NULL;
	new_cmd->red_in = NULL;
	new_cmd->red_out = NULL;
	new_cmd->red_append = NULL;
	new_cmd->std_in = -2;
	new_cmd->std_out = -2;
	return (new_cmd);
}
