/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:11:09 by nranna            #+#    #+#             */
/*   Updated: 2024/12/01 19:36:48 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	check_type(char *word, t_type *type);

int	lexer(t_sentence *sentence)
{
    t_token_node	*current;
    int				is_first_token;
	int				i;

	i = 0;
	while (sentence[i].token_lst)
	{
		current = sentence[i].token_lst;
		is_first_token = 1;
		while (current)
		{
			if (is_first_token)
			{
				current->type = COMMAND;
				is_first_token = 0;
			}
			else
				check_type(current->word, &current->type);
			current = current->next;
		}
		i++;
	}
    return (EXIT_SUCCESS);
}

static void	check_type(char *word, t_type *type)
{
	if (word[0] == '<')
	{
		if (word[1] == '<')
			*type = HEREDOC;
		else
			*type = REDIR_IN;
	}
	else if (word[0] == '>')
	{
		if (word[1] == '>')
			*type = REDIR_APPEND;
		else
			*type = REDIR_OUT;
	}
	else if (word[0] == '$')
		*type = ENV_VAR;
	else
		*type = PARAM;
	return ;
}
