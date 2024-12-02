/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:28:01 by nranna            #+#    #+#             */
/*   Updated: 2024/12/01 21:47:41 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <stdlib.h>

static int	check_unclosed_quotes(char *line);
static int	check_wrong_operator(char *line);
static int	check_consecutive_operators(char *line);
static int	check_token_after_operator(char *line);

int	syntax_scanner(char *line)
{
	int	i;

	i = 0;
	if (!line || line[i] == '\0')
		return (EXIT_FAILURE);
	while (line[i] && ft_isspace(line[i]))
	{
		i++;
		if (!line[i])
			return (EXIT_FAILURE);
	}
	printf("DEBUG: got in the syntax section... and line is [%s]\n", line); //debug
	if (check_unclosed_quotes(line) == EXIT_FAILURE)
		return (printf("Bad syntax: Unclosed quotes.\n"), EXIT_FAILURE);
	if (check_wrong_operator(line) == EXIT_FAILURE)
		return (printf("Bad syntax: Wrong operator usage.\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_unclosed_quotes(char *line)
{
	int		i;
	char	current_quote;

	i = 0;
	current_quote = '\0';
	while (line[i])
	{
		if (line[i] == '\\' && current_quote != '\'')
		{
			i += 2;
			continue ;
		}
		if ((line[i] == '\'' || line[i] == '"') && current_quote == '\0')
			current_quote = line[i];
		else if (line[i] == current_quote)
			current_quote = '\0';
		i++;
	}
	if (current_quote != '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_wrong_operator(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '|' /*|| line[i] == '<' || line[i] == '>'*/)
		return (EXIT_FAILURE);
	if (check_consecutive_operators(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_token_after_operator(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (line[i])
		i++;
	i--;
	while (i > 0 && ft_isspace(line[i]))
		i--;
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_consecutive_operators(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			skip_quotes(line, &i);
			continue ;
		}
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			if ((line[i] == '<' || line[i] == '>') && (line[i] == line[i + 1]))
				break ;
			j = i + 1;
			while (line[j] && ft_isspace(line[j]))
				j++;
			if (line[j] == '|' || line[j] == '<' || line[j] == '>')
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	check_token_after_operator(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			skip_quotes(line, &i);
		if ((line[i] == '|' || line[i] == '<' || line[i] == '>'))
		{
			if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>'
					&& line[i + 1] == '>'))
				i += 2;
			else
				i++;
			while (line[i] && ft_isspace(line[i]))
				i++;
			if (!line[i] || line[i] == '|' || line[i] == '<' || line[i] == '>')
				return (EXIT_FAILURE);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}
