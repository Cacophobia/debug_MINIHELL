/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:38:36 by nranna            #+#    #+#             */
/*   Updated: 2024/12/01 23:39:28 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <fcntl.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_SENTENCES 100

typedef enum e_token
{
	COMMAND,      // Executable or shell command
	PARAM,        // Parameters or arguments
	REDIR_IN,     // Input redirection (<)
	REDIR_OUT,    // Output redirection (>)
	REDIR_APPEND, // Append redirection (>>)
	HEREDOC,      // Here-document redirection (<<)
	ENV_VAR       // Environment variable ($)
} t_type;

typedef struct s_token_node
{
	char				*word;
	enum e_token		type;
	struct s_token_node	*next;
} t_token_node;

typedef struct s_sentence
{
	t_token_node		*token_lst;
	int					fd_in;
	int					fd_out;
	int					exit_status;
	pid_t				pid;
} t_sentence;

void					init_sentence(t_sentence *sentence);
int						parser(char *line, t_sentence *sentence);
int						token_addback(t_token_node **token_lst,
							t_token_node *new_token);
char					**ft_split(char const *s, char c);
int						free_split(char **words);
t_token_node			*new_node(char *word);
void					print_token_list(t_token_node *token_list, int z);
void					free_token_list(t_token_node *token_list);
int						syntax_scanner(char *line);
int						check_invalid_pipes(char *line);
void					skip_quotes(char *line, int *i);
int						ft_isspace(int c);
int						lexer(t_sentence *sentence);
int						executor(t_sentence *sentence);
#endif
