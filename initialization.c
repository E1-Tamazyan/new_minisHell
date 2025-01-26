/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:08 by algaboya          #+#    #+#             */
/*   Updated: 2025/01/26 21:11:23 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 3 functions already

void init_general(t_shell *general)
{
	general->tok_lst = NULL;
	general->env_lst = NULL;
	general->cmd_lst = NULL;
	general->doll_lst = NULL; // check this later
	general->sorted_env_lst = NULL;
	general->shlvl = -1;
	general->sg_quote = 0; //no quote
	general->db_quote = 0; // no quote
}

int	init_input(char *input, t_shell *general, char **env)
{
	input = "";
	general->name = get_pid();
	init_general(general); // give every value of struct to it's corresponding one
	create_env(env, general);
	while (input)
	{
		input = readline("\033[38;5;51m\033[48;5;16mminisHell:\033[0m "); //neon
		// input = readline("\033[38;5;175m\033[48;5;153m minisHell:\033[0m "); // Pastel Theme
		// input = readline("\033[38;5;129m\033[48;5;233m minisShell:\033[38;5;81m\033[0m "); //bright purples and blues with a dark background 
		// input = readline("\033[38;5;51m\033[48;5;16m minisShell:\033[0m "); // cyan neon
		if (!input)
			exit (1); // change later with exit status
		if (input[0] != '\0')
			add_history(input);
		general -> tok_lst = NULL;
		init_tokens_cmds(input, general, 0);
		clean_list(&general->tok_lst);
		// free(input);
	}
	return (printf("exit\n"), 0);
} // echo ba"rev $USER$USER jan" vonc es
void	check_heredoc_syntax(t_token *head)
{
	while (head)
	{
		if(head->type == 5)
		{
			head = head->next;
			if (head->type == 1 || head->type == 2 \
			|| head->type == 3 || head->type == 4 \
			|| head->type == 5)
			{
				printf("\nsyntax error unexpected token %s\n", head->context);
				exit(2); // waiting for Alla's exit status
			}
		}
		head = head->next;
	}
}
void	check_heredoc_limit(t_shell *general)
{
	t_token	*head;
	int	count;

	count = 0;
	head = general->tok_lst;
	
	while (head)
	{
		if (head->type == 5)
			count++;
		head = head->next;
	}
	if (count > 16)
	{
		printf("minisHell: maximum here-document count exceeded\n"); // check later pleaseee. SIGSEGV
		// waiting for Alla's cleaning function, general for this
		exit(2);
	}
	head = general->tok_lst;
	check_heredoc_syntax(head);
}
//the dollar sign should be oneend in tis function
short	init_tokens_cmds(char *input, t_shell *general, int i)
{
	int	start;
	int flag;

	flag = 0;
	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	while (flag >= 0 && input[i] != '\0')
	{
		if (flag >= 0 && input[i] && (input[i] == '|' || input[i] == '>'
			|| input[i] == '<' || input[i] == ' '))
				flag = init_op_token(input, &i, &general->tok_lst);
		else
		{
			start = i;
			while (flag >= 0 && input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<'
				&& input[i] != ' ' && input[i] != '$' && input[i] != 34 && input[i] != 39)
				i++;
			if (input[i] && flag >= 0)
				flag = check_cut_quotes(general, &input, &i, start); // and added dollar sign here check_cut_quotes
			else if (i > start)
				add_token_list(&general->tok_lst, my_substr((const char *)input, start, i - start), 0);
			i--;
		}
		if(flag < 0)
			return (clean_list(&general->tok_lst), -1);
		if (input[i])
			i++;
	}
	general->tok_lst = remove_extra_quotes(general);
	// printf("hajordiv handle redir\n");
	check_heredoc_limit(general);
	// printf("hajordiv create cmd\n");
	create_cmd_lst(general);
	print_tokens(general->tok_lst); // print
	print_cmd(general->curr_cmd);	// print
	clean_list(&general->tok_lst);
	return (0);
}

// double free
//     #1 0x55dc39867010 in init_input /home/elen_t13/projects/new_minisHell/initialization.c:55
    // #1 0x55dc3986c88f in expand_var /home/elen_t13/projects/new_minisHell/expand_dol.c:29


t_cmd_lst	*initialize_new_cmd()
{
	t_cmd_lst	*new_cmd;

	new_cmd = (t_cmd_lst	*)malloc(sizeof(t_cmd_lst));
	check_malloc(new_cmd);
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