/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:10 by elen_t13          #+#    #+#             */
/*   Updated: 2024/12/19 20:56:11 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** CAUTION *** FULL ***
// ************************
// 4 function

int check_cmd(char **env, t_shell *general)
{
    // int		index;
    // int		j;
    t_token *tmp;

    tmp = general->tok_lst;
    (void)env;
    while (tmp)
    {
        if (ft_strcmp((const char *)tmp->context, "env") == 0)
            return (export_builtin(general, tmp->context), 0);
        else if (ft_strcmp((const char *)tmp->context, "export") == 0)
            return (export_builtin(general, tmp->context), 0); // 1 error
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

char *sgmnt_cpy(const char *input, int *i)
{
    char    *result;
    int  j;
    int  length;

    length = 0;
    while (input[*i + length] && input[*i + length] != ' ' \
        && input[*i + length] != '$' && input[*i + length] != '"')
        length++;
    result = (char *)malloc((length + 1) * sizeof(char));
    j = 0;
    while (input[*i] && input[*i] != ' ' && input[*i] != '$' && input[*i] != '"')
    {
        result[j++] = input[*i];
        (*i)++;
    }
    result[j] = '\0';
    //check leak here 
    return (result);
}

char *open_dollar(t_shell *general, const char *input, int *i, int start)
{
    // char    *new_inp;
        
    (void)start;
    // new_inp = NULL;

    // this iterates one character more
    if (input[*i] && input[*i] == '$')
    {
		printf("------");
        (*i)++;
        general->doll_lst->u_key = sgmnt_cpy(input, i);
        // printf("segment = %s\n", general->doll_lst->u_key);
        general->doll_lst->value = check_env_var(general->env_lst, general->doll_lst->u_key);
        // general->doll_lst->value = ft_strjoin(general->doll_lst->value, check_env_var(general->env_lst, general->doll_lst->u_key));
    }
    return (general->doll_lst->value); 
    // return (NULL);
} // sadf ba"rev $USER jan"

int check_cut_quotes(t_shell *general, const char *input, int *i, int start)
{
    char    *dup;

    dup = NULL;
	printf("---- %c %d\n", input[*(i)], *(i));
    while (input[*(i)])
    {
		printf("bbbb %c\n", input[*(i)]);
        // printf("0.5 len = %d, dup_inp[len] = %c\n", len, dup_inp[len]);
        if (input[*(i)] == '\"')
		{
            general->db_quote = !general->db_quote;
			printf("ov a");
		}
        else if (input[*(i)] == '\'' && !general->sg_quote)
            general->sg_quote = !general->sg_quote;
        else if (input[(*i)] == '$' && general->db_quote)
        {
            dup = open_dollar(general, input, i, start);
            
            //don't forget to free dup in the function below
            printf("dup = %s\n", dup);
            // (void)dup;
            // ..here should be while to take the part of dollar sign
            //open return or not return the add_token value
            //mkamki--;
            (*i)--;
        }
        else if ((input[*(i)] == ' ' || input[*(i)] == '|' || input[*(i)] == '>' || input[*(i)] == '<') && !general->db_quote && !general->sg_quote)
        {
            if (input[*(i)] == ' ')
                return (add_token_list(&general->tok_lst, my_substr(input, start, ((*i) - start)), 0), 0);
            *i = init_op_token(input, *i, &general->tok_lst);
            // printf("input[*(i)] = %c\n", input[*(i)]);
        }
        (*i)++;
    }
	printf("aaaa %d - %d\n", general->db_quote, general->sg_quote);
    if (general->db_quote || general->sg_quote)
        return (printf("Error: Unclosed quotes found in input.\n"), -1);
    return (0);
}
