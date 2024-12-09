/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:08 by algaboya          #+#    #+#             */
/*   Updated: 2024/12/07 16:25:23 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only intiational functions
// 5 functions already

// ***************************
// ****** WARNING FULL *******
// ***************************

// static t_env *create_node(const char *key, const char *value) {
//     t_env *new_node = malloc(sizeof(t_env));
//     if (!new_node) {
//         perror("Failed to allocate memory for new node");
//         exit(EXIT_FAILURE);
//     }

//     // Allocate memory for key and value strings and copy the strings into the node
//     new_node->key = strdup(key);   // strdup() allocates memory and copies the string
//     new_node->value = strdup(value);

//     new_node->next = NULL;  // Initially set next to NULL
//     return new_node;
// }


// static void add_to_end(t_env **head, const char *key, const char *value) {
//     t_env *new_node = create_node(key, value);
    
//     if (*head == NULL) {
//         *head = new_node;  // If the list is empty, the new node becomes the head
//     } else {
//         t_env *current = *head;
//         while (current->next) {  // Traverse to the last node
//             current = current->next;
//         }
//         current->next = new_node;  // Add the new node at the end
//     }
// }


int	init_input(char *input, t_shell *general, char **env)
{
	input = "";
	create_env(env, general);
	while (input)
	{
		// input = readline("\033[105;78;15;201m minisHell:\033[0:000m "); // magenta = [38;5;201m | cyan [38;5;51m
		input = readline("\033[38;5;201mminisHell:\033[0:000m "); // magenta = [38;5;201m | cyan [38;5;51m
		add_history(input);
		if (!input)
			return (1);
		// init_general(general) // give every value to it's corresponding one
		general -> tok_lst = NULL;
		init_tokens((const char *)input, general, 0);
		lalala(general);
		// print_tokens(general->tok_lst);
		// printf("%d\n", count_lst_len(general->env_lst));
		if (check_cmd(env, general)) // if 1 error
			{
				return (free(input), clean_list(&general->tok_lst), 1);}
		// printf("blabla\n");
		clean_list(&general->tok_lst);
		free(input);
	}
	printf("exit\n");
    return (0);
}

t_env *init_env_nodes(char **env)
{
    t_env	*list_env;
    t_env	*tmp;
	t_env	*new_node;
    int i;

	i = 0;
	list_env = NULL;
	tmp = NULL;
    while (env[i] != NULL) 
	{
		// printf(":::%s\n", env[i]);
        new_node = ft_lstnew(env[i]);
        if (!new_node)
            return NULL;
        if (list_env == NULL) 
		{
            list_env = new_node;
            tmp = list_env;
        }
		else
            ft_lstadd_back(tmp, new_node);
        i++;
    }
    return (list_env);
}

short	init_tokens(const char *input, t_shell *general, int i)
{
	int	start;

	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	while (input[i] != '\0' && i >= 0)
	{
		if (i >= 0 && (input[i] == 39 || input[i] == 34))
			i = new_check_quotes(input, i, general);
		if (i >= 0 && input[i] && (input[i] == '|' || input[i] == ' ' || input[i] == '>'
			|| input[i] == '<'))
				i = init_op_token(input, i, general->tok_lst);
		else
		{ 
			start = i;
			while (i >= 0 && input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<'
				&& input[i] != ' ' && input[i] != 34 && input[i] != 39)
				i++;
			if (i > start)
				add_token_list(&general->tok_lst, my_substr(input, start, i - start), 0);
			i--;
		}
		if(i < 0)
			return (clean_list(&general->tok_lst), -1);
		i++;
	}
	// print_tokens(general->tok_lst);
	return (0);
}

// t_token	*optimize_tokens(t_token *tok_lst)
// {
// 	// int	type;
// 	t_token	*tmp;

// 	tmp = tok_lst;
// 	while (tmp)
// 	{
// 		tmp = tmp -> next;
// 	}
// 	return (tok_lst); // still this is okayd
// }


int	init_op_token(const char *input, int i, t_token *token_list)
{
	if (input[i] && input[i] == '|')
		add_token_list(&token_list, my_substr(input, i, 1), 1);
	else if (input[i] && input[i] == ' ')
	{
		add_token_list(&token_list, my_substr(input, i, 1), 9);
		// while (i
	}
	else if (input[i] && input[i] == '>')
		if (input[i] && input[++i] && input[i] && input[i] == '>')
			return (add_token_list(&token_list, my_substr(input, i - 1, 2), 4), i);
		else
			add_token_list(&token_list, my_substr(input, --i, 1), 3);
	else if (input[i] && input[i] == '<')
	{
		if (input[i] && input[++i] && input[i] && input[i] == '<')
			return (add_token_list(&token_list, my_substr(input, i - 1, 2), 5), i);
		else
			add_token_list(&token_list, my_substr(input, --i, 1), 2);
	}
	return (i);
}

int create_env(char **env, t_shell *general)
{
	char    **sorted;

	general -> env_lst = init_env_nodes(env);
	sorted = sort_env(env);
	general -> sorted_env_lst = init_env_nodes(sorted);
	return (0);
}

// *******************
// ******ARCHIVE******
// *******************

// t_env *init_env_nodes(char **env)
// {
//     t_env   *list_env;
//     t_env   *tmp;
//     int     i;

//     i = 0;
//     list_env = NULL;
//     tmp = list_env;
//     tmp = ft_lstnew(env[i]);
//     if (!list_env)
//         return (NULL);
//     i += 1;
// 	printf("%s=%s\n", tmp->key, tmp->value);
//     while (env[i] != '\0' || env[i] != NULL)
//     {
// 		printf("i = %d, env[i] == %s\n", i, env[i]);
//         ft_lstadd_back(&tmp, ft_lstnew(env[i]));
// 		printf("i = %d, ***_env %s%s\n", i, tmp->key, tmp->value);
//         i++;
//     } 
// 	printf("tmp = %s=%s\n", tmp->key, tmp->value);
//     list_env = tmp;
//     return (list_env);
// }