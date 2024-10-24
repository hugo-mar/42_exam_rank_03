#include <unistd.h>
#include <stdarg.h>

int ft_putchar(char chr)
{
	return(write(1, &chr, 1));
}

int	ft_putstr(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (write(1, "(NULL)", 6));
	while (*str)
		len += write (1, str++, 1);
	return (len);
}

int	ft_strlen(char *str)
{
	int len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	ft_putnbr_base(int nbr, char *digits)
{
	int len;
	int	base;

	len = 0;
	base = ft_strlen (digits);
	if (nbr >= base)
		len += ft_putnbr_base (nbr / base, digits);
	len += ft_putchar (digits[nbr % base]);
	return (len);
}

int	fs_handler(char fs, va_list va)
{
	int	len;
	
	if (fs == 's')
		len = ft_putstr(va_arg(va, char*));
	else if (fs == 'd')
		len = ft_putnbr_base(va_arg(va, int), "0123456789");
	else if (fs == 'x')
		len = ft_putnbr_base(va_arg(va, int), "0123456789abcdef");
	else
		len = -1;
	return (len);
}

int ft_printf(const char *format, ... )
{
	int		len;
	int		c_len;
	va_list	va;

	if (!format)
		return (-1);
	va_start(va, format);
	while (*format)
	{
		if (*format != '%')
			len += ft_putchar(*format);
		else
		{
			format++;
			c_len = fs_handler(*format, va);
			if (c_len == -1)
				return (-1);
			len += c_len;
		}
		format++;
	}
	va_end(va);
	return (len);
}
