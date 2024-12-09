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
	int	i;
	int	j;

	i = 0;
    j = 0;
    while (src[j] && src[j] != '=')
            j++;
    node -> key = (char *)malloc(sizeof(char) * (j + 1));
    if (!node-> key)
        return (-1);
    ft_strlcpy(node-> key, (const char *)src, j, 0, '=');
	// printf("key = %s\n", node->key);
    if (!node-> key)
        return (-1);
	return (j + 1);
}

void put_value(t_env *node, char *src, int pos)
{
	int	len;

	(void)node;
	if (ft_strcmp(node->key, "OLDPWD") == 0)
	{
		node->value = NULL;
		return ;
	}
	len = sgmnt_len((const char *)src, pos); // len-y talis e minchev '\n', '\n'-y neraryal
	if (len == -1)
		return ;
	node -> value = (char *)malloc(sizeof(char) * (len + 1)); //check thisss \n-i poxaren dnum enq \0
	if (!node -> value)
		return ;
	ft_strlcpy(node -> value, src, len, pos, '\n');
	// printf("value = %s\n", node->value);
    if (!node -> value)
        return ;
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

int	print_export(char *new)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	// printf("sxtorik\n");
	printf("declare -x ");
	while (new[j++] != '=')
	{
		j--;
		printf("%c", new[j]);
		j++;
	}
	if (new[j] == '\0')
	{
		// if (k == 0)
			printf("\n");
		// else
		// 	printf("=\n");
		return (1);
	}
	printf("=\"");
	j--;
	while (new[j++] != '\0')
		printf("%c", new[j]);
	printf("\"\n");
	j = 0;
	return (0);
}

// void	print_exp_noargs(char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[i] != '=' && str[i++] != '\0')
// 	{
// 		printf("declare -x %c", str[i]);
// 		i++;
// 	}
// }

void	swap_node(t_env	*a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

t_env	*bubble_sort_lst(t_env *lst)
{
	int		flag;
	t_env	*tmp;
	t_env	*i;

	i = NULL;
	flag = 1;
	if (lst == NULL)
		return (NULL);
	while (flag == 1)
	{
		tmp = lst;
		flag = 0;
		while (tmp && tmp->next)
		{
			i = tmp->next;
			if (ft_strcmp(tmp->key, i->key) > 0)
			{
				swap_node(tmp, i);
				flag = 1;
			}
			tmp = tmp->next;
		}
	}
	return (lst);
}

void	print_env(t_env *new, int flag)
{
	// char	**new;
	// int		i;
	// int		j;

	// i = 0;
	// j = 0;
	// new = sort_env(list_to_array(lst));
	// while (new[i])
	// {
	// 	if (flag == EXPORT)
	// 	{
	// 		print_export(new[i]);
	// 	}
	// 	else
	// 	{
	// 		printf("olala %s\n", new[i]);
	// 		// i++;
	// 	}
	// 		i++;
	// }
	t_env *lst = bubble_sort_lst(new);

	while (lst != NULL)
	{
		// printf("hoho\n");
		if (flag == 1)
		{
			if (lst -> value == NULL)
				printf("declare -x %s\n", lst -> key);
			else
				printf("declare -x %s=\"%s\"\n", lst -> key, lst -> value);
		}
		else
		{
			if (lst -> value == NULL)
				printf("%s\n", lst -> key);
			else
				printf("%s=%s\n", lst -> key, lst -> value);
		}
		lst = lst->next;
	}
}

// ************************
// ******* FUR MICH *******
// ************************


// **** ARCHIVE ****

// void put_value(t_env *node, char *src)
// {
	// int	i;
	// int	n;
	// int	pos;
	// int	counter;

	// i = 0;
	// counter = 0;
		// printf("start_***\n");
	// while(i < len && src[j])
	// {
	// 	printf("%c", src[j]);
	// 	i++;
	// 	j++;
	// } // correct
	// printf("\nend_***\n");
	// while (src[i] && src[i] != '\n')
	// {
	// 	// here is the main problem
	// 	n = sgmnt_len((const char *)src, &pos);
	// 	printf("1_hii\n"); //doesn't reach here
	// 	if (n == -1)
	// 		return ;
	// 	node -> value = (char *)malloc(sizeof(char) * (n + 1)); //check thisss
	// 	if (!node -> value)
	// 		return ;
    //     ft_strlcpy(node -> value, src, n, pos, '\n');
    //     if (!node -> value)
    //         return ;
    //     i++;
	// }
// }


// int	sgmnt_len(const char *str, int *pos)
// {
// 	// int	i;
// 	// int	counter;

// 	// i = 0;
// 	// counter = 0;
// 	// if (!str)
// 	// 	return (-1);
// 	// // while (str[i] != '=')
// 	// // 	i++;
// 	// // if (str[i] == '=') // only once
// 	// // 	i++;
// 	// *pos = i;
// 	// while (str[i] && str[i] != '\n')
// 	// {
// 	// 	i++;
// 	// 	counter++;
// 	// }
// 	// return (counter);
// }
