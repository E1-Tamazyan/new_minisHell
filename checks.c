/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:41:54 by etamazya          #+#    #+#             */
/*   Updated: 2024/12/09 19:35:03 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** CAUTION *** FULL ***
// ************************
// 2 function

int	check_cmd(char **env, t_shell *general)
{
	int		index;
	int		j;
	t_token	*tmp;

	tmp = general->tok_lst;
	(void)env;
	while (tmp)
	{
		index = ft_strchr((const char *)tmp->context, '$');
		if (index != -1)
		{
			j = check_print_dollar(tmp->context, general->env_lst, (index + 1));
			if (j == -1)
				return (0);
		}
		if (ft_strcmp((const char *)tmp->context, "env") == 0)
			return (export_builtin(general, tmp->context), 0);
		else if (ft_strcmp((const char *)tmp->context, "export") == 0)
			return (export_builtin(general, tmp->context), 0); //1 error
		else if (ft_strcmp((const char *)tmp->context, "pwd") == 0)
			return (pwd_builtin(general), 0);
		else if (ft_strcmp((const char *)tmp->context, "cd") == 0)
			return (cd_builtin(general), 0);
		else if (ft_strcmp((const char *)tmp->context, "unset") == 0)
			return (unset_builtin(general), 0);
		// else if (ft_strcmp((const char *)tmp->context, "echo") == 0)
		// 	return (echo_builtin(general), 0);
		else if (ft_strcmp((const char *)tmp->context, "exit") == 0)
			return (exit_builtin(general), 0);
		tmp = tmp->next;
	}
	return (0);
}

int	check_cut_quotes(const char *input, int start, int i, t_shell *general)
{
	int flag_db_quote = 0;
	int flag_single_quote = 0;

	while (input[i])
	{
		if (input[i] == '\"' && !flag_single_quote)
			flag_db_quote = !flag_db_quote;
		else if (input[i] == '\'' && !flag_db_quote)
			flag_single_quote = !flag_single_quote;
		else if ((input[i] == ' ' || input[i] == '|' || input[i] == '>'
				|| input[i] == '<') && !flag_db_quote && !flag_single_quote)
		{
			if (i > start)
				add_token_list(&general->tok_lst, my_substr(input, start, i - start), 7);
			if (input[i] && (input[i] == '|' || input[i] == '>'
					|| input[i] == '<' || input[i] == ' '))
				return (init_op_token(input, i, &general->tok_lst));
		}
		i++;
	}
	if (flag_db_quote || flag_single_quote)
		return (printf("Error: Unclosed quotes found in input.\n"), -1);
	if (i > start)
		add_token_list(&general->tok_lst, my_substr(input, start, i - start), 7);
	return (i);
}

int	check_dollar_sign(char *input, int i, t_shell *general)
{
	(void)input;
	(void)i;
	(void)general;

	printf("hello\n");
	return (0);
}

// *********** ARCHIVE ***********