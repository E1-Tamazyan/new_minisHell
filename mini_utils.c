// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   mini_utils.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/12 15:29:05 by etamazya          #+#    #+#             */
// /*   Updated: 2024/09/18 22:21:25 by etamazya         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "minishell.h"

// ************************
// *** WARNING *** FULL ***
// ************************

//5 ->6 functions already

int	put_key(t_env *node, char	*src)
{
	// int	i;
	int	j;

	// i = 0;
    j = 0;
    while (src[j] && src[j] != '=')
            j++;
    node -> key = (char *)malloc(sizeof(char) * (j + 1));
    if (!node-> key)
        return (-1);	
    ft_strlcpy(node->key, (const char *)src, (j), 0, '=');    
	if (!node-> key)
        return (-1);
	return (j + 1);
}

void put_value(t_env *node, char *src, int pos)
{
	int	len;

	len = sgmnt_len((const char *)src, pos);
	if (len == -1)
		return ;
	node -> value = (char *)malloc(sizeof(char) * (len + 1));
	if (!node -> value)
		return ;
	ft_strlcpy(node -> value, src, len, pos, '\n');
        if (!node -> value)
            return ;
}

void    print_env(t_env *lst, int flag)
{
    // if (!lst)
    //     return ;
	while (lst)
	{
		if(lst -> key && lst -> value)
		{
        	if (flag == 1)
            	printf("declare -x %s=\"%s\"\n", lst -> key, lst -> value);
        	else
            	printf("%s=%s\n", lst -> key, lst -> value);
			lst = lst->next;
		}
	}
}

int	sgmnt_len(const char *str, int pos)
{
	int counter;

	counter = 0;
	while(str[pos] && str[pos] != '\n')
	{
		pos++;
		counter++;
	}
	return (counter);
}

void	clean_list(t_token **list)
{
	t_token	*temp;
	t_token	*next;

	temp = *list;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	*list = NULL;
}

// ************************
// ******* FUR MICH *******
// ************************
void print_tokens(t_token *head)
{
    t_token *current; 

	current = head;
    while (current != NULL)
	{
        printf("context: %s\n type: %d\n", current->context, current->type);
        current = current->next;
    }
} 
