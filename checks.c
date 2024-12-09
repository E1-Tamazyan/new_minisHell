/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:41:54 by etamazya          #+#    #+#             */
/*   Updated: 2024/11/24 19:44:41 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** CAUTION *** FULL ***
// ************************
// 2 function

int check_cmd(char **env, t_shell *general)
{
	t_token	*tmp;
	int		index;

	tmp = general->tok_lst;
	(void)env;
	while (tmp)
	{
		//this is not gonna work here the dollar sign should have been come alreade opened up;
		index = ft_strchr((const char *)tmp->context, '$');
		if (index != -1)
		{	
			int j = check_print_dollar(tmp->context, general -> env_lst, (index + 1));
			if (j == -1)
				return(0);
		}
		if (ft_strcmp((const char *)tmp->context, (const char *)"env") == 0)
			return (print_env(general -> env_lst, 0), 0);			
	    // else if (ft_strcmp((const char *)tmp->context, (const char *)"export") == 0)
	        // return (print_env(general -> sorted_env_lst, 1), 0);
		tmp = tmp->next;
	}
	if (general->env_lst)
		clean_env_list(&general->env_lst);		
    return (0);
}

int check_cut_quotes(const char *input, int start, int i, t_shell *general)
{
    int flag_double_quote = 0;
    int flag_single_quote = 0;

    while (input[i])
    {
		if (input[i] == '\"' && !flag_single_quote)
			flag_double_quote = !flag_double_quote;
		else if (input[i] == '\'' && !flag_double_quote)
			flag_single_quote = !flag_single_quote;
        else if ((input[i] == ' ' || input[i] == '|' || input[i] == '>' || input[i] == '<') && !flag_double_quote && !flag_single_quote)
        {
            if (i > start)
                add_token_list(&general->tok_lst, my_substr(input, start, i - start), 7);
			if (input[i] && (input[i] == '|' || input[i] == '>'
			|| input[i] == '<' || input[i] == ' '))
				return (init_op_token(input, i, &general->tok_lst));
        }
        i++;
    }
    if (flag_double_quote || flag_single_quote)
        return(printf("Error: Unclosed quotes found in input.\n"), -1);
    if (i > start)
        add_token_list(&general->tok_lst, my_substr(input, start, i - start), 7);
    return (i);
}

int check_dollar_sign(char *input, int i, t_shell *general)
{
	(void)input;
	(void)i;
	(void)general;

	printf("hello\n");
	return (0);
}

// *********** ARCHIVE ***********