#include "get_next_line.h"

static char *ft_strdup(char *str)
{
	char *dup;
	int i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while(str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*get_next_line(int fd)
{
	char		line[70000];
	static char buffer[BUFFER_SIZE];
	static int	bytes_read;
	static int	buffer_position;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	while (1)
	{
		if (buffer_position >= bytes_read)
		{
			buffer_position = 0;
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
				break ;
		}
		line[i] = buffer[buffer_position++];
		if (line[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	line[i] = '\0';
	if (!i)
		return (NULL);
	return (ft_strdup(line));
}