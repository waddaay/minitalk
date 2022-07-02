/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywadday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:55:13 by ywadday           #+#    #+#             */
/*   Updated: 2022/04/16 00:01:01 by ywadday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr(int n)
{
	int		count;
	long	nbr;

	nbr = n;
	count = 0;
	if (nbr <= 9)
	{
		count++;
		ft_putchar(nbr + '0');
	}
	else
	{
		count += ft_putnbr(nbr / 10);
		count += ft_putnbr(nbr % 10);
	}
	return (count);
}

char	convert_to_decimal(char binary[8])
{
	int		i;
	char	decimal;

	i = 0;
	decimal = 0;
	while (i < 8)
		decimal = decimal * 2 + (binary[i++] - '0');
	return (decimal);
}

void	message_handler(int signal, siginfo_t *info, void *vd)
{
	static int	count;
	char		c;
	static char	binary[8];
	static int	last;

	if (last != info->si_pid)
	{
		count = 0;
		binary[0] = '\0';
	}
	(void)vd;
	binary[count] = (signal - 30) + '0';
	count++;
	if (count == 8)
	{
		c = convert_to_decimal(binary);
		write(1, &c, 1);
		count = 0;
		binary[0] = '\0';
	}
	last = info->si_pid;
}

int	main(void)
{
	struct sigaction	sa;

	write(1, "PID : ", 6);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = &message_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		sleep(1);
}
