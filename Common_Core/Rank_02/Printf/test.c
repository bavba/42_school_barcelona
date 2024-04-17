
#include "ft_printf.h"

int main()
{
	char	c = 'o';
	char	*str = "Hello Barcelona";
	int 	num = -42;
	unsigned int	unum = 2882343476;
	
	ft_printf("Test for %%c\t-->\t%c\n", c);
	printf("OG for %%c\t-->\t%c\n", c);
	ft_printf("--------------------------------------------\n");
	ft_printf("Test for %%s\t-->\t%s\n", str);
	printf("OG for %%s\t-->\t%s\n", str);
	ft_printf("--------------------------------------------\n");
	ft_printf("Test for %%i\t-->\t%i\n", num);
	printf("OG for %%i\t-->\t%i\n", num);
	ft_printf("--------------------------------------------\n");
	ft_printf("Test for %%d\t-->\t%d\n", num);
	printf("OG for %%d\t-->\t%d\n", num);
	ft_printf("--------------------------------------------\n");
	ft_printf("Test for %%u\t-->\t%u\n", unum);
	printf("OG for %%u\t-->\t%u\n", unum);
	ft_printf("--------------------------------------------\n");
	ft_printf("Test for %%X\t-->\t%X\n", unum);
	printf("OG for %%X\t-->\t%X\n", unum);
	ft_printf("--------------------------------------------\n");
	ft_printf("Test for %%x\t-->\t%x\n", unum);
	printf("OG for %%x\t-->\t%x\n", unum);
	ft_printf("--------------------------------------------\n");
	ft_printf("Test for %%p\t-->\t%p\n", str);
	printf("OG for %%p\t-->\t%p\n", str);
	ft_printf("--------------------------------------------\n");
	ft_printf("Test for all %%\n\n%c\n%s\n%i\n%d\n%u\n%X\n%x\n%p\n", c, str, 
	num, num, unum, unum, unum, str);
	ft_printf("--------------------------------------------\n");
}