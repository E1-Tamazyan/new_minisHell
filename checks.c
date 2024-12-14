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
    int len;
    int j;

    dup_inp = malloc(strlen(input) + 1);
    check_malloc(dup_inp);
    i = start;
    len = 0;
    while (input[i]) 
    {
        if (input[i] == '\"' && !flag_single_quote)
            flag_db_quote = !flag_db_quote;
        else if (input[i] == '\'' && !flag_db_quote)
            flag_single_quote = !flag_single_quote;
        else if ((input[i] == ' ' || input[i] == '|' || input[i] == '>' || input[i] == '<') && !flag_db_quote && !flag_single_quote)
        {
            // printf("1_input[i] = %c, i = %d\n", input[i], i);
            if (len > 0)
            {
                dup_inp[len] = '\0';
                printf("dup = %s, i = %d\n", dup_inp, i);
                add_token_list(&general->tok_lst, dup_inp, 7);
                len = 0;
            }
            if (input[i] && (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == ' '))
            {
                printf("input = %s, i = %d\n", input, i);
                return (init_op_token(input, i, &general->tok_lst));
            }
        }
        if (flag_db_quote && input[i] == '$') 
        {
            st = i;
            i++;
            printf("inside db quote. input[i] = %c, i = %d\n", input[i], i);
            while (input[i] && isalnum(input[i])) 
                i++;
            printf("inside db quote. input[i] = %c, i = %d\n", input[i], i);
            temp = my_substr(input, st + 1, i - st - 1);
            printf("st = %d, temp. input[i] = %c, i = %d\n", st, input[i], i);
            printf("temp = %s. input[i] = %c, i = %d\n", temp, input[i], i);
            if (general->env_lst && temp) 
            {
                env_var = check_env_var(general->env_lst, temp);
                printf("temp = %s. input[i] = %c, i = %d, env_var = %s\n", temp, input[i], i, env_var);
                if (env_var)
                {
                    j = 0;
                    printf("here env_var[j] = %c\n", env_var[j]);
                    while (env_var[j] != '\0')
                        dup_inp[len++] = env_var[j++];
                }
                else
                {
                    printf("why dup_inp\n");
                    dup_inp[len++] = '$';
                }
            } 
            else 
                return (free(temp), free(dup_inp), -1);
            free(temp);
        } 
        else
            dup_inp[len++] = input[i++];
    }
    if (flag_db_quote || flag_single_quote)
        return (free(dup_inp), printf("Error: Unclosed quotes found in input.\n"), -1);
    dup_inp[len] = '\0';
    if (len > 0)
        add_token_list(&general->tok_lst, dup_inp, 7);
    return (free(dup_inp), i);
}
