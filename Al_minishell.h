/* ************************************************************************** */
/*	                                                                         */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:32 by etamazya          #+#    #+#             */
/*   Updated: 2024/11/11 18:19:30 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS_EXIT 0
# define FAILURE_EXIT 1
# define EXPORT 1
# define ENV 0
// # include <std.h> // exit(),
# include <stdio.h> // readline(), perror()
# include <stdlib.h> // exit(),
# include <unistd.h> // fork(), access(),
# include <readline/readline.h> // rl_clear_history(), rl_on_new_line(), rl_replace_line(), rl_redisplay(), 
# include <readline/history.h> // rl_clear_history(), add_history(),
# include <sys/wait.h> // wait(), waitpid(), wait3(), 
# include <sys/resource.h> // (struct rusage *rusage), 
# include <signal.h> //signal(), 
# include <limits.h>

typedef enum s_ttype
{
	T_WORD = 0,				// commands and arguments
	T_PIPE = 1,				// '|'
	T_REDIR_IN = 2,			// '<'
	T_REDIR_OUT = 3,		// '>'
	T_REDIR_APPEND = 4,		// '>>'
	T_REDIR_HEREDOC = 5,	// '<<'
	T_ENV_VAR = 6,			// environment variables
	T_SGL_QUOTES = 7,		// ''
	T_DBL_QUOTES = 8,		// ""
	T_SPACE = 9,			// ' '
}				t_ttype;

typedef struct s_token
{
	char			*context;
	t_ttype			type;
	struct s_token	*next;
}			t_token;

//**************************************
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_cmd_lst
{
	char	*cmd;
	char	**args;
	// int		stdin;
	// int		stdout;
	struct s_cmd_lst	*next;
}			    t_cmd_lst;

typedef struct s_shell
{
	t_token		*tok_lst;
	t_env		*env_lst;
	t_env		*sorted_env_lst; //for export, to not change the original env_lst above
	int			shlvl; // check
	t_cmd_lst	*cmd_lst;
	// char		pwd; // check
	// char		*oldpwd; // check
}			   t_shell;
//**************************************

// ***_____main_functions_____***
int		init_input(char *input, t_shell *gen, char **env);
int		check_cmd(char **env, t_shell *general);
t_env	*init_env_nodes(char **env);

// ***____env_sorting_____***
char    **sort_env(char **env);
void    quick_sort(char **arr, int low, int high);
int     partition(char **arr, int low, int high);
void    swap(char **a, char **b);

// ***_____utils_____***
void    print_env(t_env *new, int flag);
void	print_tokens(t_token *head);
int		put_key(t_env *node, char	*src);
void	put_value(t_env *node, char *src, int pos);
int		sgmnt_len(const char *str, int pos);
void	my_list_iter(t_token *head);
int		check_print_dollar(const char *context, t_env *env_lst, int i);
int		create_env(char **env, t_shell *general);
// t_token	*optimize_tokens(&general->tok_lst);


// ***_____lib utils_____***
void	ft_strlcpy(char *dest, const char *src, int size, int pos, char limiter);
t_env	*ft_lstnew(char *context);
void	 ft_lstadd_back(t_env *lst, t_env *node);
int		 ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *str);
char	*my_substr(const char *s, unsigned int start, int len);
int		ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);

// ***_____tokenization_____***
short	init_tokens(const char *input, t_shell *general, int i);
int		init_op_token(const char *input, int i, t_token *token_list);
void	add_token_list(t_token **list, char *content, t_ttype type);
t_token	*create_token(char *content, t_ttype type);

// ** additional
void	printStrings(char **strings);
int		new_check_quotes(const char *input, int i, t_shell *general);
int		new_check_sgl_quote(const char *input, int i, t_shell *general);
void	clean_list(t_token **list);
void	clean_env_list(t_env **list);


// builtins
// void	builin(t_token *token_list);
int		export_valid(t_token *token_list);
int		pwd_builtin(t_shell *general);
int		echo_builtin(t_shell *general);
int		cd_builtin(t_shell *general);
int		export_builtin(t_shell *general, char *command);
void	error_message(char *var);
void	free_ptr(void *ptr);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
t_env	**add_env_lst_var(t_token cur_node, t_shell *general, int i);
t_env	**add_env_no_var(char *context, t_shell *general);
int		count_lst_len(t_env *env_lst);
char	*ft_strjoin(char const *s1, char const *s2);
char	**list_to_array(t_env *env);
size_t	my_strlcpy(char *dst, const char *src, size_t dstsize);
void	free_array(char **arr);
t_env	*my_lstnew(char *key, char *value);
// int	is_same_key(t_env *env_lst, char *key);
// t_env	**remove_node(t_shell *general, t_env *tmp);
int		print_export(char *new);
t_env	*bubble_sort_lst(t_env *lst);
void	swap_node(t_env	*a, t_env *b);
int		change_home(t_shell *general);
char 	*get_value(t_shell *general, char *keyik);
int		change_env_value(t_env *lst, char *keyik, char *valik);
int		change_prev_dir(t_shell *general);
int		change_dir(t_shell *general, char *dir);
int		unset_builtin(t_shell *general);
int		unset_exp_var(t_shell *general, char *new);
int		delete_exp_node(t_env **lst, t_env *nodik);
void	free_node(t_env *node);
int		exit_builtin(t_shell *general);
int		is_valid(char **args, int count);
long	ft_atol(char *str);
int		count_args(char **args);
// void	print_exp_noargs(char *str);

void lalala(t_shell *general);


// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

// char	*ft_strchr(const char *s, int c);

// **************
// archive
char	*ft_substr(char const *s, unsigned int start, int len);
 // void	 *check_db_quote(char *str);
// int		new_check_sgl_quote(const char *input, int i, t_token *t_list);
// int		count_tokens(const char *s);
// char	**split_tokens(const char *s);
// int		check_quotes(const char *input, int i);
// int		check_sgl_quote(const char *input, int *i);
// int		check_symbols(const char *input, int i);
// short	my_check_quotes(const char *input, t_token **token_list, int i, int flag);
// int		check1(char c);
// char		*init_some_tokens(int len, char **s);
// char		*cut_quote(char **s, int *len);
// int		fill_t_sgl_quotes(char *s, int len, int flag);
// int		fill_t_dbl_quotes(int len, char *s);
// int		fill_tokens(char **arr, char *s, int i, int len);
// int		single_quote(char *s, int i, int flag2);
// int		if_double(int i, int *count, int *flag, char *s);

#endif