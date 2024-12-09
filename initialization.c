/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:08 by algaboya          #+#    #+#             */
/*   Updated: 2024/12/09 11:18:09 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only intiational functions
// 5 functions already

// ***************************
// ****** WARNING FULL *******
// ***************************

int	init_input(char *input, t_shell *general, char **env)
{
	input = "";
	create_env(env, general);
	while (input)
	{
		input = readline("\033[38;5;51m\033[48;5;16mminisHell:\033[0m "); //neon
		// input = readline("\033[38;5;175m\033[48;5;153m minisHell:\033[0m "); // Pastel Theme
		// input = readline("\033[38;5;129m\033[48;5;233m minisShell:\033[38;5;81m\033[0m "); //bright purples and blues with a dark background 
		// input = readline("\033[38;5;51m\033[48;5;16m minisShell:\033[0m "); // cyan neon
		add_history(input);
		if (!input)
			return (1);
		// init_general(general) // give every value of struct to it's corresponding one
		general -> tok_lst = NULL;
		// printf("aaaaaaaaa\n");
		init_tokens((const char *)input, general, 0);
		// printf("bbbbbbbb\n");
		//addd check_heredocs
		exchange_to_cmd(general);
		if (check_cmd(env, general)) // if 1 error
			return (free(input), clean_list(&general->tok_lst), 1);
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
	int i;

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
			ft_lstadd_back(&tmp, new_node);
		i++;
	}
	return (list_env);
}

//the dollar sign should be oneend in tis function
short	init_tokens(const char *input, t_shell *general, int i)
{
	int	start;

	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	while (i >= 0 && input[i] != '\0')
	{
		if (i >= 0 && input[i] && (input[i] == '|' || input[i] == '>'
			|| input[i] == '<' || input[i] == ' ' || input[i] == '$')) // added dollar sign - init_op_token
				i = init_op_token(input, i, &general->tok_lst);
		else
		{ 
			start = i;
			while (i >= 0 && input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<'
				&& input[i] != ' ' && input[i] != 34 && input[i] != 39)
				i++;
			if (i >= 0 && (input[i] == 39 || input[i] == 34))
				i = check_cut_quotes(input,  start,  i, general); // and added dollar sign here check_cut_quotes
			else if (i > start)
				add_token_list(&general->tok_lst, my_substr(input, start, i - start), 0);
			i--;
		}
		if(i < 0)
			return (clean_list(&general->tok_lst), -1);
		if (input[i])
			i++;
	}
	print_tokens(general->tok_lst);
	// general->tok_lst = exchange_to_commands(general->tok_lst, general);
	return (0);
}

// ***************
// ***************
// ***************

//voch te type-n e command ayl inqy avelanum e cmd-neri cankin vory struct-i popoxakan e
// t_cmd_lst *exchange_to_commands(t_token *tok_lst, t_shell *general)
// {
// 	(void)tok_lst;
// 	(void)general;
	// add the cmd_token in general
    // t_token *tmp;
	// t_cmd_lst	*temp;

	// tmp = tok_lst;
	// temp = general->cmd_list;
    // if (tok_lst)
    //     tok_lst->type = "COMMAND";
    // while (tok_lst && tok_lst->next)
    // {
    //     if (tok_lst->type == 1)
    //     {
    //         if (tok_lst->next)
    //             tok_lst->next->type = "COMMAND";
    //     }
	// 	tok_lst->type = "WORD"
    //     tok_lst = tok_lst->next;
    // }
    // return tmp;
// }

// ***************
// ***************
// ***************

int	init_op_token(const char *input, int i, t_token **token_list)
{
	if (!input || !token_list)
		return i;
	if (input[i] && input[i] == '|') // not done ❗️
	{
		if (!input[i + 1] || (!input[i + 2] && input[i + 1] != '|')) // change this part later
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
		// if (input[i] == '|') // ❗️❗️❗️ try to handle  bash-3.2$ | ls => bash: syntax error near unexpected token `|'
		if (input[i + 1] == '|')
			return (printf("minisHell: syntax error near unexpected token `||'\n"), -1);
		add_token_list(token_list, my_substr(input, i, 1), 1);
		// i += 1; // try to do this //at the end of function
	}
	else if (input[i] && input[i] == '>') // >
	{
		if (!input[i + 1] || (input[i + 1] != '<' && !input[i + 2])) // DONEEEE
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
		if (input[i + 1] && input[i + 1] == '>') // DONEEE
		{
			// try with this one
			// if ((input[i + 2] == '>' && input[i + 3] == '>') || (input[i + 2] == '<' && (input[i + 3] == '<' || input[i + 3] == '|')))
			// make this line shorter ⬇️ exchanging with the above one
			if ((input[i + 2] && input[i + 2] == '>' && (input[i + 3] && input[i + 3] == '>')) || ((input[i + 2] && input[i + 2] == '<') && (input[i + 3] && (input[i + 3] == '<' || input[i + 3] == '|'))))
				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[i + 2], input[i + 3]), -1);
			if (input[i + 2] && (input[i + 2] == '>' || input[i + 2] == '<' || input[i + 2] == '|'))
				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 2]), -1);
			add_token_list(token_list, my_substr(input, i, 2), 4);
			i += 2;          // 
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
		add_token_list(token_list, my_substr(input, i, 1), 3);
	}
	else if (input[i] && input[i] == '<') // not done yet                                 <> <*|
	{
		// 		if (!input[i + 1] || 
		//     (!input[i + 2] && input[i + 1] != '|') || 
		//     (((input[i + 1] == '>' || input[i + 1] == '<') && input[i + 2] != '|') && input[i + 2] == '<' && !input[i + 3]))
		// {
		//     return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
		// }

		// if (!input[i + 1] || (!input[i + 2] && input[i + 1] != '|') || (((input[i + 1] == '>' || input[i + 1] == '<') && input[i + 2] != '|') && input[i + 2] == '<' && !input[i + 3]))
		// 	return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
		if (input[i + 1] && input[i + 1] == '<')
		{
			if ((input[i + 2] && input[i + 2] == '>') && (input[i + 3] && (input[i + 3] == '>' ||  input[i + 3] == '|')))
				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[i + 2], input[i + 3]), -1);
			if (input[i + 1] == '|' || (input[i + 2] && (input[i + 2] == '<' || input[i + 2] == '>' || input[i + 2] == '|')))
				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 2]), -1);
			printf("%d, i = %c\n", i, input[i]);
			add_token_list(token_list, my_substr(input, i, 2), 5);
		// 	i++;
		// 	if (input[i])
		// 		printf("1_%d, i = %c\n", i, input[i]);
		}
		else if (input[i + 1] == '>')
			printf(">");
		else if (input[i + 1] == '|')
				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 1]), -1);
		add_token_list(token_list, my_substr(input, i, 1), 2);
		i++;
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


// init_op_token ---- shorten formmm maybe completed and maybe will be "needable"
// else if (input[i] == '>') // >
// {
//     if (!input[i + 1] || (input[i + 1] != '<' && !input[i + 2])) // Newline or invalid following token
//         return printf("minisHell: syntax error near unexpected token `newline'\n"), -1;
//     if (input[i + 1] == '>') // >>
//     {
//         if ((input[i + 2] && ((input[i + 2] == '>' && input[i + 3] == '>') || (input[i + 2] == '<' && (input[i + 3] == '<' || input[i + 3] == '|')))) ||
//             (input[i + 2] && (input[i + 2] == '>' || input[i + 2] == '<' || input[i + 2] == '|')))
//             return printf("minisHell: syntax error near unexpected token `%c%c'\n", input[i + 2], input[i + 3]), -1;
//         add_token_list(token_list, my_substr(input, i, 2), 4);
//         i += 2;
//     }
//     else if (input[i + 1] == '<') // ><
//     {
//         if ((input[i + 2] && input[i + 2] == '<' && input[i + 3] == '<') || (input[i + 2] && (input[i + 2] == '>' || input[i + 2] == '<')))
//             return printf("minisHell: syntax error near unexpected token `%c%c%c'\n", input[i + 1], input[i + 2], input[i + 3]), -1;     
//         return printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 1]), -1;
//     }
//     else if ((input[i + 1] == '|') || !input[i + 2]) // handle pipes and end of input
//     {
//         if (input[i + 2] && input[i + 3] && (input[i + 2] == '>' || input[i + 2] == '<' || input[i + 2] == '|'))
//             return printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 2]), -1;       
//         return printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 1]), -1;
//     }
//     add_token_list(token_list, my_substr(input, i, 1), 3);
// }