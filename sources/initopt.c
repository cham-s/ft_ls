#include "ft_ls.h" 
void	initopt(t_opt *options)
{
		options->A = 0; 
		options->R = 0; 
		options->S = 0; 
		options->a = 0; 
		options->d = 0; 
		options->f = 0; 
		options->l = 0; 
		options->r = 0; 
		options->t = 0; 
}

void	addflag(t_opt *options, char c)
{
	if (c == 'A')
		options->A = 1;
	else if (c == 'R')
		options->R = 1;
	else if (c == 'S')
		options->S = 1;
	else if (c == 'a')
		options->a = 1;
	else if (c == 'd')
		options->d = 1;
	else if (c == 'f')
		options->f = 1;
	else if (c == 'l')
		options->l = 1;
	else if (c == 'r')
		options->r = 1;
	else if (c == 't')
		options->t = 1;
}
