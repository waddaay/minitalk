/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywadday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:46:15 by ywadday           #+#    #+#             */
/*   Updated: 2022/04/15 23:54:59 by ywadday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	sign;

	i = 0;
	s = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		s = s * 10 + (str[i] - '0');
		i++;
	}
	return (s * sign);
}

char	*convert_to_binary(char c)
{
	int		j;
	char	ascii;
	char	*final;

	final = (char *)malloc(sizeof(char) * 8);
	ascii = c;
	j = 7;
	while (j >= 0)
	{
		final[j] = (ascii % 2) + '0';
		ascii /= 2;
		j--;
	}
	return (final);
}

void	send_message(char *message, int pid)
{
	int		j;
	int		i;
	char	*binary;

	i = 0;
	while (message[i] != '\0')
	{
		j = 0;
		binary = convert_to_binary(message[i++]);
		while (j < 8)
		{
			kill(pid, 30 + (binary[j++] - '0'));
			usleep(800);
		}
		free(binary);
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*string_to_send;

	if (argc != 3)
		write(1, "Invalid Arguments", 17);
	else
	{
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
		{
			write(1, "Invalid pid", 11);
			return (1);
		}
		string_to_send = argv[2];
		send_message(string_to_send, pid);
	}
}
