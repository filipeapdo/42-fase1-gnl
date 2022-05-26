#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int		main(void)
{
	int		fd;
	char	*pl;
	
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("r1");
		exit(1);
	}
	
	/*
	/ calling order :	[main]pl == NULL > 
							[get_next_line]line == NULL > 
								[build_line]line_aux == NULL

								/ pss : [build_line]line_aux = ft_strdup(s1)
									/ pss : [ft_strdup]s_dup = malloc(5) | | | | | |
									/ pss : [ft_strdup]s_dup = ft_strlcpy |1|2|3|4|\0|
									/ pss : [ft_strdup]s_dup == "1234\0"
									/ pss : [ft_strdup]s_dup > return (s_dup) -> que é o ponteiro para a primeira posição do espaco alocado pelo malloc na "ft_strdup", neste caso, reperesentado pelo valor 1
								/ pss : [build_line]line_aux > s_dup
								/ pss : [build_line]line_aux == "1234\0"
								/ pss : [build_line]line_aux > return (line_aux) -> que é o "mesmo" ponteiro para a primeira posição do espaco alocado pelo malloc na "ft_strdup, neste caso, reperesentado pelo valor 1
							/ pss : [get_next_line]line = build_line(fd, chunck)
							/ pss : [get_next_line]line == "1234\0"
							/ pss : [get_next_line]line > return (line) -> que é o "mesmo" ponteiro para a primeira posição do espaco alocado pelo malloc na "ft_strdup, neste caso, reperesentado pelo valor 1
						/ pss : [main]pl = get_next_line(fd)
						/ pss : [main]pl == "1234\0"
						/ pss : [main]pl > printf(pl) -> que é o "mesmo" ponteiro para a primeira posição do espaco alocado pelo malloc na "ft_strdup, neste caso, reperesentado pelo valor 1
						/ pss : [main]pl = free(pl) >>>
							/ pss : [get_next_line]line = free(line) >>>
								/ pss : [build_line]line_aux = free(line_aux) >>>
									/ pss : [ft_strdup]s_dup = free(s_dup), aqui é, de fato, liberado o bloco de memoria ::: | | | | | | free(5)

	/ return order : 				< [ft_strdup]s_dup == "1234\0"
								< [build_line]line_aux == "1234\0"
							< [get_next_line]line == "1234\0"
						[main]pl == "1234\0"
	*/
	pl = get_next_line(fd);
	printf("   1   test.c: %s@", pl); // |1|2|3|4|\n|\0|[6]
	free(pl);
	pl = get_next_line(fd);
	printf("   2   test.c: %s@", pl); // |2|2|2|2|2|2|2|\n|\0|[9]
	free(pl);
	pl = get_next_line(fd); 
	printf("   3   test.c: %s@", pl); // |1|1|1|1|\n|\0|[6]
	free(pl);
	pl = get_next_line(fd);
	printf("   4   test.c: %s@", pl); // |2|2|2|2|3|\n|\0|[7]
	free(pl);
	pl = get_next_line(fd);
	printf("   5   test.c: %s@", pl); // |\n|\0|[2]
	free(pl);
	pl = get_next_line(fd);
	printf("   6   test.c: %s@", pl);
	free(pl);
	pl = get_next_line(fd);
	printf("   7   test.c: %s@", pl);
	free(pl);
	pl = get_next_line(fd);
	printf("   8   test.c: %s@", pl);
	free(pl);
	pl = get_next_line(fd);
	printf("   9   test.c: %s@", pl);
	free(pl);
	pl = get_next_line(fd);
	printf("   10   test.c: %s@", pl);
	free(pl);
	
	// char			*s1 = "1234";
	// char			*s2 = "abcd";
	// char			*s3 = "&*()";
	// static char		*s;

	// s = ft_strdup(s1 + 3);
	// printf("%s\n", s);
	// s = flp_gnljoin(s, s2);
	// printf("%s\n", s);
	// s = flp_gnljoin(s, s3);
	// printf("%s\n", s);
	// free(s);

	return (0);
}
