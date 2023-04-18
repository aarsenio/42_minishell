#include <minishell.h>

long long	ft_atoll(const char *str)
{
	long long	s;
	long long	res;

	s = 1;
	res = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (s *(*str - '0'));
		str++;
	}
	return (res);
}
