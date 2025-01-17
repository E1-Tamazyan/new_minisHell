/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:08 by algaboya          #+#    #+#             */
/*   Updated: 2025/01/17 20:00:34 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only intiational functions
// 3 functions already

// ***************************
// ****** WARNING FULL *******
// ***************************

void init_general(t_shell *general)
{
	general->tok_lst = NULL;
	general->env_lst = NULL;
	general->cmd_lst = NULL;
	general->doll_lst = (t_dollar *)malloc(sizeof(t_dollar)); // check this later
	general->sorted_env_lst = NULL;
	general->shlvl = -1;
	general->sg_quote = 0; //no quote
	general->db_quote = 0; // no quote
}

int	init_input(char *input, t_shell *general, char **env)
{
	input = "";
	general->name = get_pid();
	init_general(general); // give every value of struct to it's corresponding one
	create_env(env, general);
	while (input)
	{
		input = readline("\033[38;5;51m\033[48;5;16mminisHell:\033[0m "); //neon
		// input = readline("\033[38;5;175m\033[48;5;153m minisHell:\033[0m "); // Pastel Theme
		// input = readline("\033[38;5;129m\033[48;5;233m minisShell:\033[38;5;81m\033[0m "); //bright purples and blues with a dark background 
		// input = readline("\033[38;5;51m\033[48;5;16m minisShell:\033[0m "); // cyan neon
		if (!input)
			exit (1); // change later with exit status
		if (input[0] != '\0')
			add_history(input);
		general -> tok_lst = NULL;
		init_tokens(input, general, 0);
		if (check_cmd(env, general)) // if 1 error
			return (free(input), clean_list(&general->tok_lst), 1);
		clean_list(&general->tok_lst);
		// free(input);
	}
	return (printf("exit\n"), 0);
} // echo ba"rev $USER$USER jan" vonc es

//the dollar sign should be oneend in tis function
short	init_tokens(char *input, t_shell *general, int i)
{
	int	start;
	int flag;

	flag = 0;
	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	while (flag >= 0 && input[i] != '\0')
	{
		if (flag >= 0 && input[i] && (input[i] == '|' || input[i] == '>'
			|| input[i] == '<' || input[i] == ' '))
				flag = init_op_token(input, &i, &general->tok_lst);
		else
		{
			start = i;
			while (flag >= 0 && input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<'
				&& input[i] != ' ' && input[i] != '$' && input[i] != 34 && input[i] != 39)
				i++;
			if (input[i] && flag >= 0)
				flag = check_cut_quotes(general, &input, &i, start); // and added dollar sign here check_cut_quotes
			else if (i > start)
				add_token_list(&general->tok_lst, my_substr((const char *)input, start, i - start), 0);
			i--;
		}
		if(flag < 0)
			return (clean_list(&general->tok_lst), -1);
		if (input[i])
			i++;
	}
	printf("****\n");
	print_tokens(general->tok_lst);
	printf("****\n");
	general->tok_lst = remove_extra_quotes(general);
	printf("__****\n");
	print_tokens(general->tok_lst);
	printf("__****\n");
	printf("tokkkk = %s\n", general->tok_lst->context);
	general->cmd_lst = create_cmd_lst(general->tok_lst);
	print_cmd(general->cmd_lst);
	return (0);
}


//     #1 0x55dc39867010 in init_input /home/elen_t13/projects/new_minisHell/initialization.c:55
    // #1 0x55dc3986c88f in expand_var /home/elen_t13/projects/new_minisHell/expand_dol.c:29