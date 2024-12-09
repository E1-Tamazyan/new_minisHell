/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:41:54 by etamazya          #+#    #+#             */
/*   Updated: 2024/12/11 12:05:06 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** CAUTION *** FULL ***
// ************************
// 2 function

int	check_cmd(char **env, t_shell *general)
{
	// int		index;
	// int		j;
	t_token	*tmp;

	tmp = general->tok_lst;
	(void)env;
	while (tmp)
	{
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

int check_cut_quotes(const char *input, int start, int i, t_shell *general)
{
    int flag_db_quote = 0;
    int flag_single_quote = 0;
    int st;
    char *temp;
    char *env_var;
    char *dup_inp;
    int modified_len = 0;
    int j;

    dup_inp = malloc(strlen(input) + 1);
    check_malloc(dup_inp);
    i = start;
    j = 0;
    while (input[i]) 
    {
        if (input[i] == '\"' && !flag_single_quote)
            flag_db_quote = !flag_db_quote;
        else if (input[i] == '\'' && !flag_db_quote)
            flag_single_quote = !flag_single_quote;
        else if ((input[i] == ' ' || input[i] == '|' || input[i] == '>' || input[i] == '<') && !flag_db_quote && !flag_single_quote)
        {
            if (modified_len > 0)
            {
                dup_inp[modified_len] = '\0';
                add_token_list(&general->tok_lst, dup_inp, 7);
                modified_len = 0;
            }
            if (input[i] && (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == ' '))
                return init_op_token(input, i, &general->tok_lst);
        }
        if (flag_db_quote && input[i] == '$') 
        {
            st = i;
            i++;
            while (input[i] && isalnum(input[i])) 
                i++;
            temp = my_substr(input, st + 1, i - st - 1);
            if (general->env_lst && temp) 
            {
                env_var = check_env_var(general->env_lst, temp);
                if (env_var) 
                    while (env_var[j] != '\0') 
                        dup_inp[modified_len++] = env_var[j++];
                else 
                    dup_inp[modified_len++] = '$';
            } 
            else 
                return (free(temp), free(dup_inp), -1);
            free(temp);
        } 
        else 
            dup_inp[modified_len++] = input[i++];
    }
    if (flag_db_quote || flag_single_quote)
        return (free(dup_inp), printf("Error: Unclosed quotes found in input.\n"), -1);
    dup_inp[modified_len] = '\0';
    if (modified_len > 0)
        add_token_list(&general->tok_lst, dup_inp, 7);
    return (free(dup_inp), i);
}
