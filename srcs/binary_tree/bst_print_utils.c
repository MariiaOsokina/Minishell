#include "minishell.h"

// void	print_outfiles(t_list *outfiles, int space)
// {
// 	int	i;

// 	i = 0;
// 	while (i < space + 2)
// 	{
// 		printf(" ");
// 		i++;
// 	}
// 	printf("[OUTFILES]: ");
// 	i = 0;
// 	while (outfiles)
// 	{
// 		printf("%s", (char *)((t_outf *)outfiles->content)->name);
// 		if (outfiles->next)
// 			printf(", ");
// 		outfiles = outfiles->next;
// 	}
// 	printf("\n");
// }

void	print_i_ofiles(t_list *in_ofiles, int space)
{
	int	i;

	i = 0;
	while (i < space + 2)
	{
		printf(" ");
		i++;
	}
	printf("[IN_OUT_FILES]: ");
	i = 0;
	while (in_ofiles)
	{
		printf("%s", (char *)((t_in_out *)in_ofiles->content)->name);
		if (in_ofiles->next)
			printf(", ");
		in_ofiles = in_ofiles->next;
	}
	printf("\n");
}

// void	print_infiles(t_list *infiles, int space)
// {
// 	int	i;

// 	i = 0;
// 	while (i < space + 2)
// 	{
// 		printf(" ");
// 		i++;
// 	}
// 	printf("[INFILES]: ");
// 	i = 0;
// 	while (infiles)
// 	{
// 		printf("%s", (char *)((t_inf *)infiles->content)->eof);
// 		if (infiles->next)
// 			printf(", ");
// 		infiles = infiles->next;
// 	}
// 	printf("\n");
// }

