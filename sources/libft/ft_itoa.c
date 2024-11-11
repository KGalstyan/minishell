/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:11:44 by vkostand          #+#    #+#             */
/*   Updated: 2024/09/30 20:22:39 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chars_quantity(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len += 1;
	while (n != 0)
	{
		len += 1;
		n /= 10;
	}
	return (len);
}

static int	ifneg(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	int		length;
	char	*str;

	length = (chars_quantity(n));
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	str[length] = '\0';
	if (n < 0)
		str[0] = '-';
	while (n != 0)
	{
		str[--length] = ifneg(n % 10) + '0';
		n /= 10;
	}
	return (str);
}

/*static int	chars_quantity(int num)
{
	int	len;

	len = 0;
	if (num < 0)
	{
		len = len + 1;
		num = num * -1;
	}
	while (num != 0)
	{
		len = len + 1;
		num = num / 10;
	}
	return (len);
}

static int	chars_order(int len)
{
	int	tens;

	tens = 1;
	while (len > 1)
	{
		tens *= 10;
		len--;
	}
	return (tens);
}

static char	*tochar(int n, char *str, int i)
{
	int	ten;
	int	num;

	ten = chars_order(chars_quantity(n));
	while (n != 0)
	{
		num = n / ten;
		str[i++] = num + '0';
		n = n - num * ten;
		ten /= 10;
	}
	str[i] = '\0';
	return (str);
}

static int	start(int n, char *str, int i, int neg)
{
	int	ten;
	int	len;

	ten = chars_order(chars_quantity(n));
	if ( neg == -1 && len = 11)
	{
		i = 2
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		index;
int			len;

	len = chars_quantity(n) + 1;
	str = (char *)malloc(sizeof(char) * len);
	if (str == NULL)
		return (NULL);
	index = 0;
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	if (n == 0)
		str[0] = '0';
	str[len] = '\0';
	while (n != 0)
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (str);*/
/*static char  *intmin(int n, char *str, int length)
{
len = chars_quantity(n);
if (n < 0 && len == 11)
{
	length = 2;
	str[0] = '-';
	str[1] = '2';
	n = 147483648;
}
return (str);
}*/

/*
int	main(void)
{
	int n = 1234;
	int i = 0;
	char *st;
	st = ft_itoa(n);
	while (i < 4)
	{
		printf("%s", st);
		i++;
	}
	return (0);
}*/
