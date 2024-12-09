/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:11:10 by elen_t13          #+#    #+#             */
/*   Updated: 2024/12/05 18:19:55 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exchange_to_cmd(t_shell *general)
{
    t_token     *tmp_tok;
    t_cmd_lst   *tmp;
    t_cmd_lst   *head;

    tmp = general->cmd_list;
    head = general->cmd_list;
    while (general->tok_lst)
    {
        tmp_tok = general->tok_lst;
        general-> args_count = counter_args(general);
        // if (general-> args_count < 0) // -2 error
        printf("dddd = %d, %s\n", general->args_count, general->tok_lst->context);
        // general->cmd_list->args = (char **)malloc(sizeof(char *) * (general->args_count + 1));
        // ete tesav nshana kanchum a funckia ov cmd sarqi, sarqeluc heto pointery araj a talis
    }
    return (0);
}

int counter_args(t_shell *general)
{
    general->args_count = 0;
    while (general->tok_lst)
    {
        if (general->tok_lst->type != 0)
            return (general-> args_count);
        general-> args_count++;
        general->tok_lst = general->tok_lst->next;
    }
    return (0);
}