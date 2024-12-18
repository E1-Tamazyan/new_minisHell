/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:10 by elen_t13          #+#    #+#             */
/*   Updated: 2024/12/18 18:22:01 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** CAUTION *** FULL ***
// ************************
// 2 function

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
    int     j;
    int length;

    length = 0;
    while (input[*i + length] && input[*i + length] != ' ' && input[*i + length] != '$' && input[*i + length] != '"')
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
    char    *new_inp;
    
    (void)start;
    if (input[*i] == '$')
    {
        (*i)++;
        general->doll_lst->u_key = sgmnt_cpy(input, i);
        printf("-->%s<--\n", general->doll_lst->u_key);
        general->doll_lst->value = check_env_var(general->env_lst, general->doll_lst->u_key);
        printf("_-->%s<--\n", general->doll_lst->value);
        // printf("env = %s\n", temp);
        (void)new_inp;
    }
    return (NULL);
}

int check_cut_quotes(t_shell *general, const char *input, int *i, int start)
{
    char    *dup;

    dup = NULL;
    while (input[*(i)])
    {
        // printf("0.5 len = %d, dup_inp[len] = %c\n", len, dup_inp[len]);
        if (input[*(i)] == '\"' && !general->sg_quote)
            general->db_quote = !general->db_quote;
        else if (input[*(i)] == '\'' && !general->db_quote)
            general->sg_quote = !general->sg_quote;
        else if (input[(*i)] == '$' && general->db_quote)
        {
            dup = open_dollar(general, input, i, start);
            (void)dup;
            // ..here should be while to take the part of dollar sign
            //open return or not return the add_token value
            
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
    if (general->db_quote || general->sg_quote)
        return (printf("Error: Unclosed quotes found in input.\n"), -1);
    return (0);
}
