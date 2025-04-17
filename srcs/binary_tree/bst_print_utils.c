#include "minishell.h"

void	print_int_out_files(t_list *i_ofiles, int space) //MO: added
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
	while (i_ofiles)
	{
		printf("%s", (char *)((t_in_out *)i_ofiles->content)->name);
		printf("%s", (char *)((t_in_out *)i_ofiles->content)->eof);
		if (i_ofiles->next)
			printf(", ");
		i_ofiles = i_ofiles->next;
	}
	printf("\n");
}


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

