/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywadday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:56:23 by ywadday           #+#    #+#             */
/*   Updated: 2022/04/16 00:59:23 by ywadday          ###   ########.fr       */
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
	if (!str)
		return (0);
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

void	handler(int sig)
{
	(void)sig;
	write(1, "your message has been received successfully.", 44);
}

void	send_message(char *message, int pid)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	while (1)
	{
		j = 0;
		while (j < 8)
		{
			res = ((message[i]) << j++) & 128;
			if (res)
				res = 1;
			kill(pid, 30 + res);
			usleep(800);
		}
		if (message[i++] == '\0')
			break ;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		write(1, "Invalid Arguments", 17);
	else
	{
		signal (SIGUSR2, &handler);
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
		{
			write(1, "Invalid pid", 11);
			return (1);
		}
		send_message (argv[2], pid);
	}
}
