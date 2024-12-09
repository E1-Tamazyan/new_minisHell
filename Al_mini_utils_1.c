/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:50:05 by etamazya          #+#    #+#             */
/*   Updated: 2024/11/06 15:55:01 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_print_dollar(const char *context, t_env *env_lst, int i)
{
    int end;
    char *var;
    t_env *tmp;

    end = i;
    tmp = env_lst;
    if (!context)
        return (-1);
    while (context[end] && (context[end] != ' ' && (context[end] < 9 || context[end] > 13 || context[end] != '$')))
        end++;
    var = ft_substr(context, (unsigned int)i, (end - i));
    if (!var)
        return (1);
    while (tmp)
    {
        if (ft_strcmp(tmp->key, var) == 0)
            return (printf("%s\n", tmp->value), 0);
        tmp = tmp->next;
    }
    free(var);
    return (1);
}
