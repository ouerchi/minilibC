#include "minilibc.h"

int	ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	len;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
	return (len);
}

static int	ft_ptr_len(unsigned long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

static void	ft_put_ptr(unsigned long num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_print_char(num + '0');
		else
			ft_print_char(num - 10 + 'a');
	}
}

int	ft_print_ptr(void *ptr)
{
	unsigned long	ptr_addr;
	int				len;

	ptr_addr = (unsigned long)ptr;
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	len = 0;
	write(1, "0x", 2);
	len += 2;
	ft_put_ptr(ptr_addr);
	len += ft_ptr_len(ptr_addr);
	return (len);
}

int	ft_print_nbr(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	len = ft_print_str(num);
	free(num);
	return (len);
}

int	ft_print_unsigned(unsigned int n)
{
	int		len;

    if (n >= 10)
        len = ft_print_unsigned(n / 10) + ft_print_unsigned(n % 10);
    else
        len = ft_print_char(n + '0');
    return (len);
}

int	ft_print_hex(unsigned int n, const char format)
{
	int	len;

    len = 0;
	if (n >= 16)
	{
		len += ft_print_hex(n / 16, format);
		len += ft_print_hex(n % 16, format);
	}
	else
	{
		if (n <= 9)
			len += ft_print_char(n + '0');
		else
		{
			if (format == 'x')
				len += ft_print_char(n - 10 + 'a');
			if (format == 'X')
				len += ft_print_char(n - 10 + 'A');
		}
	}
    return (len);
}
