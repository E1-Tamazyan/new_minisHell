/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:46:57 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/16 21:47:31 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_op_token(char *input, int *i, t_token **token_list)
{
	if (!input || !token_list)
		return -1;
	// Check for '$' character
	// deleted this part (it doesn;t make token with $$ it should just open them)
	// if (input[*i] && input[*i] == '$')
	// {
	// 	if (input[*i + 1] && input[*i + 1] == '$')
	// 		add_token_list(token_list, my_substr(input, *i, 2), 4);
	// 	(*i)++;
	// }
	// Check for '|' character
	if (input[*i] && input[*i] == '|')
	{
		if (!input[*i + 1] || (input[*i + 1] != '|' && !input[*i + 2])) // Handle syntax error
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);

		if (input[*i + 1] == '|')
			return (printf("minisHell: syntax error near unexpected token `||'\n"), -1);

		add_token_list(token_list, my_substr(input, *i, 1), 1);
	}
	else if (input[*i] && input[*i] == '>')
	{
		// Handle '>' and '>>' tokens
		if (!input[*i + 1] || (input[*i + 1] != '<' && !input[*i + 2])) // Handle error
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
		if (input[*i + 1] && input[*i + 1] == '>')
		{
			if (input[*i + 2] && (input[*i + 2] == '>' || input[*i + 2] == '<' || input[*i + 2] == '|'))
				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 2], input[*i + 3]), -1);
			add_token_list(token_list, my_substr(input, *i, 2), 4);
			(*i)++;
		}
		else if (input[*i + 1] && input[*i + 1] == '<')
			return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 1], input[*i + 2]), -1); //Handle error for invalid combinations like '><' or '<|'
		else
			add_token_list(token_list, my_substr(input, *i, 1), 3);
	}
	else if (input[*i] && input[*i] == '<')
	{
		// Handle '<' and '<<' tokens
		if (!input[*i + 1] || (input[*i + 1] != '>' && !input[*i + 2])) // Handle error
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
		if (input[*i + 1] && input[*i + 1] == '<')
		{
			if (input[*i + 2] && (input[*i + 2] == '>' || input[*i + 2] == '<'))
				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 2], input[*i + 3]), -1);
			add_token_list(token_list, my_substr(input, *i, 2), 5);
			(*i)++;
		}
		else
			add_token_list(token_list, my_substr(input, *i, 1), 2);
	}
	return (*i);
}


// *********************
// ****** ARCHIVE ******
// *********************

// keep this in mind, mesto init_op_token

// int check_dollar_sign(char *input, int *i, t_token **token_list)
// {
// 	if (input[*i] && input[*i] == '$')
// 	{
// 		if (input[*i + 1] && input[*i + 1] == '$')
// 			add_token_list(token_list, my_substr(input, *i, 2), 4);
// 		(*i)++;
// 		return 1;
// 	}
// 	return 0;
// }

// int check_pipe_sign(char *input, int *i, t_token **token_list)
// {
// 	if (input[*i] && input[*i] == '|')
// 	{
// 		if (!input[*i + 1] || (input[*i + 1] != '|' && !input[*i + 2])) // Syntax error
// 			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
// 		if (input[*i + 1] == '|') // Handle `||` error
// 			return (printf("minisHell: syntax error near unexpected token `||'\n"), -1);
// 		add_token_list(token_list, my_substr(input, *i, 1), 1);
// 		return 1;
// 	}
// 	return 0;
// }

// int check_greater_than_sign(char *input, int *i, t_token **token_list)
// {
// 	if (input[*i] && input[*i] == '>')
// 	{
// 		if (!input[*i + 1] || (input[*i + 1] != '<' && !input[*i + 2])) // Syntax error
// 			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);

// 		if (input[*i + 1] && input[*i + 1] == '>')
// 		{
// 			if (input[*i + 2] && (input[*i + 2] == '>' || input[*i + 2] == '<' || input[*i + 2] == '|'))
// 				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 2], input[*i + 3]), -1);
// 			add_token_list(token_list, my_substr(input, *i, 2), 4);
// 			(*i)++;
// 		}
// 		else if (input[*i + 1] && input[*i + 1] == '<')
// 		{
// 			return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 1], input[*i + 2]), -1);
// 		}
// 		else
// 			add_token_list(token_list, my_substr(input, *i, 1), 3);
// 		return 1;
// 	}
// 	return 0;
// }

// int check_less_than_sign(char *input, int *i, t_token **token_list)
// {
// 	if (input[*i] && input[*i] == '<')
// 	{
// 		if (!input[*i + 1] || (input[*i + 1] != '>' && !input[*i + 2])) // Syntax error
// 			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);

// 		if (input[*i + 1] && input[*i + 1] == '<')
// 		{
// 			if (input[*i + 2] && (input[*i + 2] == '>' || input[*i + 2] == '<'))
// 				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 2], input[*i + 3]), -1);
// 			add_token_list(token_list, my_substr(input, *i, 2), 5);
// 			(*i)++;
// 		}
// 		else
// 			add_token_list(token_list, my_substr(input, *i, 1), 2);
// 		return 1;
// 	}
// 	return 0;
// }

// int init_op_token(char *input, int *i, t_token **token_list)
// {
// 	if (!input || !token_list)
// 		return -1; // Return error if input or token_list is invalid
// 	// Check for specific tokens
// 	if (check_dollar_sign(input, i, token_list) == -1)
// 		return -1;
// 	if (check_pipe_sign(input, i, token_list) == -1)
// 		return -1;
// 	if (check_greater_than_sign(input, i, token_list) == -1)
// 		return -1;
// 	if (check_less_than_sign(input, i, token_list) == -1)
// 		return -1;
// 	return (*i);
// }
