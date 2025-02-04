/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:14:38 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 18:56:25 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dollar_sign(char *input, int *i, t_token **token_list)
{
	if (input[*i] && input[*i] == '$')
	{
		if (input[*i + 1] && input[*i + 1] == '$')
			add_token_list(token_list, my_substr(input, *i, 2), 4);
		(*i)++;
		return (1);
	}
	return (0);
}

static int	check_pipe_sign(char *input, int *i, t_token **token_list)
{
	if (input[*i] && input[*i] == '|')
	{
		if (!input[*i + 1] || (input[*i + 1] != '|' && !input[*i + 2]))
			return (syntax_error("newline"), -1);
		if (input[*i + 1] == '|')
			return (syntax_error("||"), -1);
		add_token_list(token_list, my_substr(input, *i, 1), 1);
		return (1);
	}
	return (0);
}

static int	check_greater_than_sign(char *input, int *i, t_token **token_list)
{
	if (input[*i] && input[*i] == '>')
	{
		if (!input[*i + 1] || (input[*i + 1] != '<' && !input[*i + 2]))
			return (syntax_error("newline"), -1);
		if (input[*i + 1] && input[*i + 1] == '>')
		{
			if (input[*i + 2] && (input[*i + 2] == '>'
					|| input[*i + 2] == '<' || input[*i + 2] == '|'))
				return (syntax_error_2(input[*i + 2], input[*i + 3]), -1);
			add_token_list(token_list, my_substr(input, *i, 2), 4);
			(*i)++;
		}
		else if (input[*i + 1] && input[*i + 1] == '<')
			return (syntax_error_2(input[*i + 1], input[*i + 2]), -1);
		else
			add_token_list(token_list, my_substr(input, *i, 1), 3);
		return (1);
	}
	return (0);
}

static int	check_less_than_sign(char *input, int *i, t_token **token_list)
{
	if (input[*i] && input[*i] == '<')
	{
		if (!input[*i + 1] || (input[*i + 1] != '>' && !input[*i + 2]))
			return (syntax_error("newline"), -1);
		if (input[*i + 1] && input[*i + 1] == '<')
		{
			if (input[*i + 2] && (input[*i + 2] == '>' || input[*i + 2] == '<'))
				return (syntax_error_2(input[*i + 2], input[*i + 3]), -1);
			add_token_list(token_list, my_substr(input, *i, 2), 5);
			(*i)++;
		}
		else
			add_token_list(token_list, my_substr(input, *i, 1), 2);
		return (1);
	}
	return (0);
}

int	init_op_token(char *input, int *i, t_token **token_list)
{
	if (!input || !token_list)
		return (-1);
	if (check_dollar_sign(input, i, token_list) == -1)
		return (-1);
	if (check_pipe_sign(input, i, token_list) == -1)
		return (-1);
	if (check_greater_than_sign(input, i, token_list) == -1)
		return (-1);
	if (check_less_than_sign(input, i, token_list) == -1)
		return (-1);
	return (*i);
}
