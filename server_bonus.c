/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywadday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:59:35 by ywadday           #+#    #+#             */
/*   Updated: 2022/04/16 01:05:00 by ywadday          ###   ########.fr       */
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

void	message_handler(int signal, siginfo_t *info, void *vd)
{
	static int	count;
	static char	binary;
	static int	last;

	(void)vd;
	if (last != info->si_pid || count == 8)
	{
		count = 0;
		binary = 0;
	}
	binary = (binary << 1) | ((signal - 30));
	count++ ;
	if (count == 8)
	{
		if (binary == '\0')
			kill (info->si_pid, SIGUSR2);
		else
			write (1, &binary, 1);
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
