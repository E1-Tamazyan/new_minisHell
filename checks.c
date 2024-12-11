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
		// index = ft_strchr((const char *)tmp->context, '$');
		// if (index != -1)
		// {
		// 	// j = check_print_dollar(tmp->context, general->env_lst, (index + 1));
		// 	if (j == -1)
		// 		return (0);
		// }
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
int	ft_isalnum(int arg)
{
	if ((arg >= 48 && arg <= 57) || (arg >= 65 && arg <= 90)
		|| (arg > 96 && arg < 123))
		return (1);
	else
		return (0);
}

// int	check_cut_quotes(const char *input, int start, int i, t_shell *general)
// {
// 	int flag_db_quote = 0;
// 	int flag_single_quote = 0;
// 	int	st;
// 	char	*temp;
// 	char	*env_var;
	
// 	while (input[i])
// 	{
// 		if (input[i] == '\"' && !flag_single_quote)
// 			flag_db_quote = !flag_db_quote;
// 		else if (input[i] == '\'' && !flag_db_quote)
// 			flag_single_quote = !flag_single_quote;
// 		else if ((input[i] == ' ' || input[i] == '|' || input[i] == '>'
// 				|| input[i] == '<') && !flag_db_quote && !flag_single_quote)
// 		{
// 			if (i > start)
// 				add_token_list(&general->tok_lst, my_substr(input, start, i - start), 7);
// 			if (input[i] && (input[i] == '|' || input[i] == '>'
// 					|| input[i] == '<' || input[i] == ' '))
// 				return (init_op_token(input, i, &general->tok_lst));
// 		}
// 		if (flag_db_quote && input[i] == '$')
// 		{
// 			// check if after $ is ? sign or not
// 			// dfsd "$USER ddfsdfd"
// 			// while (input[i] && !ft_isalnum(input[i]))
// 			// 	i++;
// 			st = i;
// 			i++;
// 			while (input[i] && input[i] != '\"' && input[i] != '$' && !(input[i] == 32 || (input[i] >= 9 && input[i] <= 13)))
// 				i++;
// 			temp = ft_substr(input, st, (i - st));
// 			env_var = check_env_var(general->env_lst , temp);
			
// 			printf("env = %s\n", env_var);
// 		}
// 		i++;
// 	}
// 	if (flag_db_quote || flag_single_quote)
// 		return (printf("Error: Unclosed quotes found in input.\n"), -1);
// 	if (i > start)
// 		add_token_list(&general->tok_lst, my_substr(input, start, i - start), 7);
// 	return (i);
// }




int	check_dollar_sign(char *input, int i, t_shell *general)
{
	(void)input;
	(void)i;
	(void)general;

	printf("hello\n");
	return (0);
}

// *********** ARCHIVE ***********


// int check_cut_quotes(const char *input, int start, int i, t_shell *general)
// {
//     int flag_db_quote = 0;
//     int flag_single_quote = 0;
//     int st;
//     char *temp;
//     char *env_var;
//     char *modified_input;
//     int modified_len = 0;
//     int j = 0;

//     // Allocate memory for modified input
//     modified_input = malloc(strlen(input) + 1);  // +1 for null terminator
//     if (!modified_input)
//     {
//         printf("Error: Memory allocation failed.\n");
//         return -1;
//     }

//     while (input[i]) 
//     {
//         if (input[i] == '\"' && !flag_single_quote)
//             flag_db_quote = !flag_db_quote;
//         else if (input[i] == '\'' && !flag_db_quote)
//             flag_single_quote = !flag_single_quote;
//         else if ((input[i] == ' ' || input[i] == '|' || input[i] == '>' || input[i] == '<') && !flag_db_quote && !flag_single_quote)
//         {
//             // If we found a space or operator, create a token for the part of the string before it
//             if (i > start)
//             {
//                 modified_input[modified_len] = '\0';  // Null-terminate the current modified input part
//                 add_token_list(&general->tok_lst, modified_input, 7);
//                 modified_len = 0;  // Reset the modified input length
//             }

//             if (input[i] && (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == ' '))
//                 return (init_op_token(input, i, &general->tok_lst));
//         }

//         // If inside double quotes, check for variable substitution
//         if (flag_db_quote && input[i] == '$') 
//         {
//             st = i;  // Mark the start of the variable name
//             i++;  // Skip past the '$'

//             // Extract the variable name
//             while (input[i] && isalnum(input[i])) 
//                 i++;

//             // Extract the variable name substring (skip the '$')
//             temp = my_substr(input, st + 1, i - st - 1);

//             // Ensure that the environment list is valid and lookup the variable
//             if (general->env_lst && temp) 
//             {
//                 env_var = check_env_var(general->env_lst, temp);  // Get the value of the environment variable
//                 if (env_var) 
//                 {
//                     // Replace the variable with its value directly in the input string
//                     printf("Replacing $%s with: %s\n", temp, env_var);  // Debugging output
//                     // Add the environment variable value to the modified input
//                     for (j = 0; env_var[j] != '\0'; j++) {
//                         modified_input[modified_len++] = env_var[j];
//                     }
//                 }
//                 else 
//                 {
//                     printf("Warning: Environment variable %s not found.\n", temp);
//                     modified_input[modified_len++] = '$';  // If not found, just add '$'
//                 }
//             } 
//             else 
//             {
//                 printf("Error: Invalid environment list or memory allocation failed.\n");
//                 free(temp);
//                 free(modified_input);
//                 return -1;  // Return error if env list is invalid
//             }

//             free(temp);  // Free the allocated memory for the variable name
//         } 
//         else 
//         {
//             // Add the current character to the modified input
//             modified_input[modified_len++] = input[i];
//             i++;
//         }
//     }

//     // Check for unclosed quotes
//     if (flag_db_quote || flag_single_quote)
//     {
//         free(modified_input);
//         return (printf("Error: Unclosed quotes found in input.\n"), -1);
//     }

//     // Null-terminate the modified input and add the remaining part as a token
//     modified_input[modified_len] = '\0';
//     if (modified_len > 0)
//     {
//         add_token_list(&general->tok_lst, modified_input, 7);
//     }

//     // Free the modified input
//     free(modified_input);

//     return i;  // Return the final index after processing
// }


// int check_cut_quotes(const char *input, int start, int i, t_shell *general)
// {
//     int flag_db_quote = 0;      // Flag to track if we're inside double quotes
//     int flag_single_quote = 0;  // Flag to track if we're inside single quotes
//     int modified_len = 0;       // Length of the current token in modified_input
//     char *modified_input;       // Modified input string where tokens are stored
//     char *env_var;              // Holds the environment variable value

//     // Allocate memory for modified input (including null terminator)
//     modified_input = malloc(strlen(input) + 1);
//     if (!modified_input)
//     {
//         printf("Error: Memory allocation failed.\n");
//         return -1;
//     }

//     while (input[i])
//     {
//         // Handle toggling of quote flags
//         if (input[i] == '\"' && !flag_single_quote)
//             flag_db_quote = !flag_db_quote;
//         else if (input[i] == '\'' && !flag_db_quote)
//             flag_single_quote = !flag_single_quote;

//         // Handle spaces or operators outside quotes (to create tokens)
//         if ((input[i] == ' ' || input[i] == '|' || input[i] == '>' || input[i] == '<') && !flag_db_quote && !flag_single_quote)
//         {
//             // If we've already collected a token, store it
//             if (modified_len > 0)
//             {
//                 modified_input[modified_len] = '\0';  // Null-terminate the current token
//                 add_token_list(&general->tok_lst, modified_input, 7);
//                 modified_len = 0;  // Reset the token length for the next one
//             }

//             // Handle the operator token (return early if an operator is found)
//             if (input[i] == ' ' || input[i] == '|' || input[i] == '>' || input[i] == '<')
//                 return init_op_token(input, i, &general->tok_lst);
//         }

//         // If inside double quotes, check for variable substitution
//         if (flag_db_quote && input[i] == '$')
//         {
//             int var_start = ++i;  // Skip the '$' symbol

//             // Find the end of the variable name (alphanumeric characters)
//             while (input[i] && (isalnum(input[i]) || input[i] == '_'))
//                 i++;

//             // Extract the variable name substring (from var_start to the current i position)
//             char *var_name = my_substr(input, var_start, i - var_start);
//             if (var_name)
//             {
//                 // Look up the environment variable
//                 env_var = check_env_var(general->env_lst, var_name);
//                 free(var_name);  // Free the variable name after lookup

//                 // If the environment variable exists, add its value to modified_input
//                 if (env_var)
//                 {
//                     int j = 0;
//                     while (env_var[j] != '\0')
//                     {
//                         modified_input[modified_len++] = env_var[j++];
//                     }
//                 }
//                 else
//                 {
//                     modified_input[modified_len++] = '$';  // If not found, just add '$'
//                 }
//             }
//         }
//         else
//         {
//             // Otherwise, add the current character to modified_input
//             modified_input[modified_len++] = input[i];
//             i++;
//         }
//     }

//     // Check for unclosed quotes (either single or double)
//     if (flag_db_quote || flag_single_quote)
//     {
//         free(modified_input);
//         return printf("Error: Unclosed quotes found in input.\n"), -1;
//     }

//     // If there's any remaining token, null-terminate it and add it to the token list
//     if (modified_len > 0)
//     {
//         modified_input[modified_len] = '\0';
//         add_token_list(&general->tok_lst, modified_input, 7);
//     }

//     // Free the modified input buffer and return the final index
//     free(modified_input);
//     return i;
// }






























// int check_cut_quotes(const char *input, int start, int i, t_shell *general)
// {
//     int flag_db_quote = 0;       // Flag for double quotes
//     int flag_single_quote = 0;   // Flag for single quotes
//     int len = 0;                 // Length of the current token
//     int st;                      // Start index for variable names
//     char *temp;                  // Temporary variable to hold substrings
//     char *env_var;               // Environment variable value
//     char *modified_input;        // Buffer for modified input
//     int j = 0;                   // Loop index

//     // Allocate memory for the modified input
//     modified_input = malloc(strlen(input) + 1);  // +1 for null terminator
//     if (!modified_input)
//     {
//         printf("Error: Memory allocation failed.\n");
//         return -1;
//     }

//     while (input[i]) 
//     {
//         // Handle double quotes
//         if (input[i] == '\"' && !flag_single_quote)
//         {
//             flag_db_quote = !flag_db_quote;  // Toggle double quote flag
//             modified_input[len++] = '\"';    // Include the quote in the token
//         }

//         // Handle single quotes
//         else if (input[i] == '\'' && !flag_db_quote)
//         {
//             flag_single_quote = !flag_single_quote;  // Toggle single quote flag
//             modified_input[len++] = '\'';            // Include the single quote in the token
//         }

//         // Handle spaces or operators (token boundaries) outside of quotes
//         else if ((input[i] == ' ' || input[i] == '|' || input[i] == '>' || input[i] == '<') && !flag_db_quote && !flag_single_quote)
//         {
//             // If we found a space or operator, create a token for the part of the string before it
//             if (i > start) 
//             {
//                 modified_input[len] = '\0';  // Null-terminate the current token
//                 add_token_list(&general->tok_lst, my_substr(input, start, i - start), 7);
//                 len = 0;  // Reset the modified input length
//             }

//             // Handle operators as separate tokens
//             if (input[i] && (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == ' '))
//                 return init_op_token(input, i, &general->tok_lst);
//         }

//         // Handle environment variable substitution inside double quotes
//         else if (flag_db_quote && input[i] == '$') 
//         {
//             st = i;  // Mark the start of the variable name
//             i++;  // Skip past the '$'

//             // Extract the variable name
//             while (input[i] && isalnum(input[i])) 
//                 i++;

//             // Extract the variable name substring (skip the '$')
//             temp = my_substr(input, st + 1, i - st - 1);

//             // Ensure that the environment list is valid and lookup the variable
//             if (general->env_lst && temp) 
//             {
//                 env_var = check_env_var(general->env_lst, temp);  // Get the value of the environment variable
//                 if (env_var) 
//                 {
//                     // Replace the variable with its value directly in the input string
//                     printf("Replacing $%s with: %s\n", temp, env_var);  // Debugging output
//                     // Add the environment variable value to the modified input
//                     for (j = 0; env_var[j] != '\0'; j++) {
//                         modified_input[len++] = env_var[j];
//                     }
//                 }
//                 else 
//                 {
//                     printf("Warning: Environment variable %s not found.\n", temp);
//                     modified_input[len++] = '$';  // If not found, just add '$'
//                 }
//             } 
//             else 
//             {
//                 printf("Error: Invalid environment list or memory allocation failed.\n");
//                 free(temp);
//                 free(modified_input);
//                 return -1;  // Return error if env list is invalid
//             }

//             free(temp);  // Free the allocated memory for the variable name
//         } 

//         // Regular character: Append it to the modified input
//         else 
//         {
//             modified_input[len++] = input[i];
//             i++;
//         }
//     }

//     // Check for unclosed quotes
//     if (flag_db_quote || flag_single_quote)
//     {
//         free(modified_input);
//         return (printf("Error: Unclosed quotes found in input.\n"), -1);
//     }

//     // Null-terminate the modified input and add the remaining part as a token
//     modified_input[len] = '\0';
//     if (len > 0)
//     {
//         add_token_list(&general->tok_lst, my_substr(input, start, len), 7);  // Add the token created from start to current position
//     }

//     // Free the modified input
//     free(modified_input);

//     return i;  // Return the final index after processing
// }


int check_cut_quotes(const char *input, int start, int i, t_shell *general)
{
    int flag_db_quote = 0;       // Flag for double quotes
    int flag_single_quote = 0;   // Flag for single quotes
    int len = 0;                 // Length of the current token
    int st;                      // Start index for variable names
    char *temp;                  // Temporary variable to hold substrings
    char *env_var;               // Environment variable value
    char *modified_input;        // Buffer for modified input
    int j = 0;                   // Loop index

    // Allocate memory for the modified input
    modified_input = malloc(strlen(input) + 1);  // +1 for null terminator
    if (!modified_input)
    {
        printf("Error: Memory allocation failed.\n");
        return -1;
    }

    while (input[i]) 
    {
        // Handle double quotes
        if (input[i] == '\"' && !flag_single_quote)
        {
            flag_db_quote = !flag_db_quote;  // Toggle double quote flag
            modified_input[len++] = '\"';    // Include the quote in the token
        }

        // Handle single quotes
        else if (input[i] == '\'' && !flag_db_quote)
        {
            flag_single_quote = !flag_single_quote;  // Toggle single quote flag
            modified_input[len++] = '\'';            // Include the single quote in the token
        }

        // Handle spaces or operators (token boundaries) outside of quotes
        else if ((input[i] == ' ' || input[i] == '|' || input[i] == '>' || input[i] == '<') && !flag_db_quote && !flag_single_quote)
        {
            // If we found a space or operator, create a token for the part of the string before it
            if (i > start) 
            {
                modified_input[len] = '\0';  // Null-terminate the current token
                add_token_list(&general->tok_lst, my_substr(input, start, len), 7);
                len = 0;  // Reset the modified input length
            }

            // Handle operators as separate tokens
            if (input[i] && (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == ' '))
                return init_op_token(input, i, &general->tok_lst);
        }

        // Handle environment variable substitution inside double quotes
        else if (flag_db_quote && input[i] == '$') 
        {
            st = i;  // Mark the start of the variable name
            i++;  // Skip past the '$'

            // Extract the variable name
            while (input[i] && isalnum(input[i])) 
                i++;

            // Extract the variable name substring (skip the '$')
            temp = my_substr(input, st + 1, i - st - 1);

            // Ensure that the environment list is valid and lookup the variable
            if (general->env_lst && temp) 
            {
                env_var = check_env_var(general->env_lst, temp);  // Get the value of the environment variable
                if (env_var) 
                {
                    // Replace the variable with its value directly in the input string
                    printf("Replacing $%s with: %s\n", temp, env_var);  // Debugging output
                    // Add the environment variable value to the modified input
                    for (j = 0; env_var[j] != '\0'; j++) {
                        modified_input[len++] = env_var[j];
                    }
                }
                else 
                {
                    printf("Warning: Environment variable %s not found.\n", temp);
                    modified_input[len++] = '$';  // If not found, just add '$'
                }
            } 
            else 
            {
                printf("Error: Invalid environment list or memory allocation failed.\n");
                free(temp);
                free(modified_input);
                return -1;  // Return error if env list is invalid
            }

            free(temp);  // Free the allocated memory for the variable name
        } 

        // Regular character: Append it to the modified input
        else 
        {
            modified_input[len++] = input[i];
            i++;
        }
    }

    // Check for unclosed quotes
    if (flag_db_quote || flag_single_quote)
    {
        free(modified_input);
        return (printf("Error: Unclosed quotes found in input.\n"), -1);
    }

    // Null-terminate the modified input and add the remaining part as a token
    modified_input[len] = '\0';
    if (len > 0)
    {
        add_token_list(&general->tok_lst, my_substr(input, start, len), 7);  // Add the token created from start to current position
    }

    // Free the modified input
    free(modified_input);

    return i;  // Return the final index after processing
}
