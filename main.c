/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:13 by etamazya          #+#    #+#             */
/*   Updated: 2024/12/09 15:56:14 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** WARNING *** FULL ***
// ************************

int main(int argc, char **argv, char **env)
{
    (void)argv;
    t_shell *general;
    char    *input;

    input = NULL;
    general = malloc(sizeof(t_shell));
    if (!general)
        return (1); 
    if (argc == 1)
    {
        if (init_input(input, general, env)) // if 1 error
            return (free(general), 1);
    }
    return (free(general), 0);
}