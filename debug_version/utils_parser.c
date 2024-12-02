/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:12:19 by nranna            #+#    #+#             */
/*   Updated: 2024/12/01 12:43:16 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <stdlib.h>

void	init_sentence(t_sentence *sentence)
{
	if (!sentence)
		return ;
	memset(sentence, 0, sizeof(t_sentence));//ft_memset here pls
	sentence->token_lst = NULL;
	sentence->fd_in = STDIN_FILENO;
	sentence->fd_out = STDOUT_FILENO;
	sentence->pid = -1;
}

t_token_node	*new_node(char *word)
{
	t_token_node	*new_token_node;

	if (!word)
		return (NULL);
	new_token_node = malloc(sizeof(t_token_node));
	if (!new_token_node)
		return (NULL);
	new_token_node->word = strdup(word);
	new_token_node->type = COMMAND;
	new_token_node->next = NULL;
	return (new_token_node);
}

int	token_addback(t_token_node **token_lst, t_token_node *new_token)
{
	t_token_node	*tmp;

	if (!token_lst || !new_token)
		return (EXIT_FAILURE);
	if (*token_lst == NULL)
	{
		*token_lst = new_token;
		return (EXIT_SUCCESS);
	}
	tmp = *token_lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	return (EXIT_SUCCESS);
}

void	print_token_list(t_token_node *token_list, int z)
{
	t_token_node	*current;

	current = token_list;
	while (current)
	{
		printf("Sentence[%d] Token: %s, Type: %d\n", z, current->word,
				current->type);
		current = current->next;
	}
	return ;
}

void	free_token_list(t_token_node *token_list)
{
	t_token_node	*tmp;

	if (!token_list)
		return ;
	tmp = token_list;
	while (token_list != NULL)
	{
		tmp = token_list;
		token_list = token_list->next;
		free(tmp->word);
		free(tmp);
	}
	return ;
}
