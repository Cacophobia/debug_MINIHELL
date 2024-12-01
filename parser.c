/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:16:59 by nranna            #+#    #+#             */
/*   Updated: 2024/12/01 16:39:53 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <stdlib.h>

static int		create_sentence(t_sentence *sentence, char *raw_sentence);
static int		create_token_lst(t_token_node **token_lst, char **raw_token);

int	parser(char *line, t_sentence *sentence)
{
	printf("DEBUG: got in the parser section...\n"); //DEBUG
	int		i;
	char	**raw_sentence;

	i = 0;
	raw_sentence = ft_split(line, '|');
	if (!raw_sentence)
		return (printf("Error: couldn't malloc."), EXIT_FAILURE);
	while (raw_sentence[i])
	{
		if (create_sentence(&sentence[i], raw_sentence[i]) == EXIT_FAILURE)
		{
			free_split(raw_sentence);
			return (printf("Error: couldn't create sentence."), EXIT_FAILURE);
		}
		i++;
	}
	free_split(raw_sentence);
	return (EXIT_SUCCESS);
}

static int	create_sentence(t_sentence *sentence, char *raw_sentence)
{
	char			**raw_token;

	init_sentence(sentence);
	raw_token = ft_split(raw_sentence, ' ');
	if (!raw_token)
		return (printf("Error: couldn't malloc."), EXIT_FAILURE);
	//sentence->token_lst = NULL;
	if (create_token_lst(&sentence->token_lst, raw_token) == EXIT_FAILURE)
	{
		free_split(raw_token);
		free_token_list(sentence->token_lst);
		return (printf("Error: couldn't create token list."), EXIT_FAILURE);
	}
	free_split(raw_token);
	return (EXIT_SUCCESS);
}

static int	create_token_lst(t_token_node **token_lst, char **raw_token)
{
	int		i;
	
	i = 0;
	while (raw_token[i])
	{
		if (token_addback(token_lst, new_node(raw_token[i])) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
