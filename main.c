/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:30:57 by nranna            #+#    #+#             */
/*   Updated: 2024/12/01 23:33:33 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <stdio.h>
#include <stdlib.h>

static void	init_all_sentences(t_sentence *sentence);
static void	free_sentences(t_sentence *sentence);
static void	clean_minishell(char *line, t_sentence *sentence);

int	main(void)
{
	char		*line;
	t_sentence	*sentence;

	line = NULL;
	//start linked list for envp here.
	sentence = (t_sentence *)malloc(sizeof(t_sentence) * MAX_SENTENCES);
	if (!sentence)
		return (printf("Minishell: Error mallocing sentence\n"), 1);
	init_all_sentences(sentence);
	while (42)
	{
		line = readline("Enter a line: ");
		if (!line)
			return (printf("Minishell: Logging out\n"), 0);
		if (syntax_scanner(line) == EXIT_SUCCESS)
		{
			if (parser(line, sentence) == EXIT_SUCCESS)
			{
				if (lexer(sentence) == EXIT_SUCCESS)
				{
					if (executor(sentence) == EXIT_FAILURE)
						clean_minishell(line, sentence);
				}
			}
		}
		clean_minishell(line, sentence);
	}
	free(sentence);
	return (0);
}

static void	init_all_sentences(t_sentence *sentence)
{
	int	i;

	i = 0;
	while (i < MAX_SENTENCES)
	{
		init_sentence(&sentence[i]);
		i++;
	}
	return ;
}

static void	free_sentences(t_sentence *sentence)
{
	int	i;

	i = 0;
	if (!sentence[0].token_lst)
		return ;
	while (sentence[i].token_lst)
	{
		free_token_list(sentence[i].token_lst);
		sentence[i].token_lst = NULL;
		i++;
	}
	return ;
}

static void	clean_minishell(char *line, t_sentence *sentence)
{
	if (line)
		free(line);
	free_sentences(sentence);
	return ;
}
