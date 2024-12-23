/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:08 by algaboya          #+#    #+#             */
/*   Updated: 2024/12/23 17:37:31 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only intiational functions
// 5 functions already

// ***************************
// ****** WARNING FULL *******
// ***************************

void init_general(t_shell *general)
{
	general->tok_lst = NULL;
	general->env_lst = NULL;
	general->cmd_lst = NULL;
	general->doll_lst = (t_dollar *)malloc(sizeof(t_dollar)); // check this later
	general->sorted_env_lst = NULL;
	general->shlvl = -1;
	general->sg_quote = 0; //no quote
	general->db_quote = 0; // no quote
}

int	init_input(char *input, t_shell *general, char **env)
{
	input = "";
	init_general(general); // give every value of struct to it's corresponding one
	create_env(env, general);
	while (input)
	{
		input = readline("\033[38;5;51m\033[48;5;16mminisHell:\033[0m "); //neon
		// input = readline("\033[38;5;175m\033[48;5;153m minisHell:\033[0m "); // Pastel Theme
		// input = readline("\033[38;5;129m\033[48;5;233m minisShell:\033[38;5;81m\033[0m "); //bright purples and blues with a dark background 
		// input = readline("\033[38;5;51m\033[48;5;16m minisShell:\033[0m "); // cyan neon
		if (!input)
			exit (1); // change later
		if (input[0] != '\0')
			add_history(input);
		general -> tok_lst = NULL;
		init_tokens(input, general, 0);
		create_print_cmd(general); // to print commands
		//addd check_heredocs
		// if (check_cmd(env, general)) // if 1 error
		// 	return (free(input), clean_list(&general->tok_lst), 1);
		clean_list(&general->tok_lst);
		free(input);
	}
	return (printf("exit\n"), 0);
}

t_env *init_env_nodes(char **env)
{
	t_env	*list_env;
	t_env	*tmp;
	t_env	*new_node;
	int		i;

	i = 0;
	list_env = NULL;
	tmp = NULL;
	while (env[i] != NULL)
	{
		new_node = ft_lstnew(env[i]);
		if (!new_node) 
			return NULL;
		if (list_env == NULL)
		{
			list_env = new_node;
			tmp = list_env;
		}
		else
			ft_lstadd_back(tmp, new_node);
		i++;
	}
	return (list_env);
}

//the dollar sign should be oneend in tis function
short	init_tokens(char *input, t_shell *general, int i)
{
	int	start;
	int flag;
	// t_token *head;

	// head = general->tok_lst;
	flag = 0;
	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	while (flag >= 0 && input[i] != '\0')
	{
		if (flag >= 0 && input[i] && (input[i] == '|' || input[i] == '>'
			|| input[i] == '<' || input[i] == ' ' || input[i] == '$')) // added dollar sign - init_op_token
				i = init_op_token(input, i, &general->tok_lst);
		else
		{
			start = i;
			while (flag >= 0 && input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<'
				&& input[i] != ' ' && input[i] != 34 && input[i] != 39)
				i++;
			if (input[i] && flag >= 0 && (input[i] == 39 || input[i] == 34))
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
	// general->tok_lst= head;
	printf("****\n");
	print_tokens(general->tok_lst);
	printf("****\n");
	// general->tok_lst = exchange_to_commands(general->tok_lst, general);
	return (0);
}

int	init_op_token(char *input, int i, t_token **token_list)
{
	if (!input || !token_list)
		return i;
	if (input[i] && input[i] == '|') // ❗️❗️
	{
		if (!input[i + 1] || (!input[i + 2] && input[i + 1] != '|')) // change this part later
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
		// if (input[i] == '|') // ❗️❗️❗️ try to handle  bash-3.2$ | ls => bash: syntax error near unexpected token `|'
		if (input[i + 1] == '|')
			return (printf("minisHell: syntax error near unexpected token `||'\n"), -1);
		add_token_list(token_list, my_substr(input, i, 1), 1);
	}
	else if (input[i] && input[i] == '>')
	{
		if (!input[i + 1] || (input[i + 1] != '<' && !input[i + 2])) // DONEEEE
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
		if (input[i + 1] && input[i + 1] == '>') // DONEEE
		{
			// make this line shorter ⬇️ exchanging with the above one
			if ((input[i + 2] && input[i + 2] == '>' && (input[i + 3] && input[i + 3] == '>')) || ((input[i + 2] && input[i + 2] == '<') && (input[i + 3] && (input[i + 3] == '<' || input[i + 3] == '|'))))
				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[i + 2], input[i + 3]), -1);
			if (input[i + 2] && (input[i + 2] == '>' || input[i + 2] == '<' || input[i + 2] == '|'))
				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 2]), -1);
			add_token_list(token_list, my_substr(input, i, 2), 4);
			i++;
		}
		else if (input[i + 1] && (input[i + 1] == '<')) // DONE
		{
			if (input[i + 2] && input[i + 2] == '<' && input[i + 3] && input[i + 3] == '<') // ><> ><|
				return (printf("minisHell: syntax error near unexpected token `%c%c%c'\n", input[i + 1], input[i + 2], input[i + 3]), -1);
			if (input[i + 2] && (input[i + 2] == '>' || input[i + 2] == '<')) // ><> ><|
				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[i + 1], input[i + 2]), -1);
			return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 1]), -1);
		}
		else if ((input[i + 1] && input[i + 1] == '|') || !input[i + 2]) // added this part //DONEEEEEEE
		{
			//  grel pipe-i tramabanakan sharunakutyuny
			if (input[i + 2] && input[i + 3] && (input[i + 2] == '>' || input[i + 2] == '<' || input[i + 2] == '|')) // >|<, >|>, >||: // added this part
				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 2]), -1); // added this part
			else
				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 1]), -1); // added this part
		}
		else
			add_token_list(token_list, my_substr(input, i, 1), 3);
	}
	else if (input[i] && input[i] == '<') // ⛔️⛔️⛔️⛔️⛔️⛔️⛔️     <> <*|
	{
		if (!input[i + 1] || (input[i + 1] != '>' && !input[i + 2]))
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
		if (input[i + 1] && input[i + 1] == '<')
		{
			if ((input[i + 2] && input[i + 2] == '>') && (input[i + 3] && (input[i + 3] == '>' ||  input[i + 3] == '|')))
				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[i + 2], input[i + 3]), -1);
			if (input[i + 1] == '|' || (input[i + 2] && (input[i + 2] == '<' || input[i + 2] == '>' || input[i + 2] == '|')))
				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 2]), -1);
			add_token_list(token_list, my_substr(input, i, 2), 5);
			i++;
		}
		// else if (input[i + 1] == '>')
		// 	printf(">"); // ⛔️⛔️⛔️⛔️⛔️⛔️⛔️ try to understand do you need to implement this?  cmd:ls <> echo dasd (works only for existing file)
		else if (input[i + 1] == '|')
				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 1]), -1);
		else
			add_token_list(token_list, my_substr(input, i, 1), 2);
	}
	return (i);
}

int	create_env(char **env, t_shell *general)
{
	char	**sorted;

	general -> env_lst = init_env_nodes(env);
	sorted = sort_env(env);
	general -> sorted_env_lst = init_env_nodes(sorted);
	return (0);
}


// *********************
// ****** ARCHIVE ******
// *********************