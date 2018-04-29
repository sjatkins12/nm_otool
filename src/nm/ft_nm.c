/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 11:29:58 by satkins           #+#    #+#             */
/*   Updated: 2018/04/28 15:28:09 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int		nm(char *file)
{
	t_symtab_cmd	*symcmd;
	void			*file_head;
	t_pqueue		*symbols;

	if (!(file_head = open_n_map_file(file)))
		return (EXIT_FAILURE);
	if (validate_magic(file_head) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	symcmd = get_symtab_cmd(file_head + sizeof(struct mach_header_64));
	symbols = get_symbol(file_head + symcmd->symoff, file_head + symcmd->stroff,
		symcmd->nsyms);
	if (symbols == NULL)
		return (EXIT_FAILURE);
	print_symbols(symbols);
	return (EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
	int	i;
	int	ret;

	if (argc > 1)
	{
		i = 1;
		ret = 0;
		while (i < argc && ret != EXIT_FAILURE)
		{
			ret = nm(argv[i]);
			i++;
		}
	}
	else
		nm("a.out");
	return (0);
}