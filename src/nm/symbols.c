/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 12:48:15 by satkins           #+#    #+#             */
/*   Updated: 2018/04/28 16:03:19 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

char			g_section_type[MAX_SECT + 1];

char			segsec_type(__attribute__((unused))char *segname, char *sectname)
{
	if (ft_strequ(sectname, SECT_TEXT))
		return ('T');
	else if (ft_strequ(sectname, SECT_DATA))
		return ('D');
	else if (ft_strequ(sectname, SECT_BSS))
		return ('B');
	else
		return ('S');
}

/*
** Will iterate through commands. saving any section type encountered 
** in the global. Then will return the symbol tabel command.
*/

t_symtab_cmd	*get_symtab_cmd(void *command_head)
{
	uint32_t			i;
	int					k;
	t_load_cmd			*cmd_iter;
	t_segment_cmd_64	*seg;
	t_section			*p;

	k = 0;
	cmd_iter = command_head;
	while (cmd_iter->cmd != LC_SYMTAB)
	{
		if (cmd_iter->cmd == LC_SEGMENT_64)
		{
			seg = (t_segment_cmd_64 *)cmd_iter;
			p = (void *)seg + sizeof(struct segment_command_64);
			i = 0;
			while (i < seg->nsects && (++k))
			{
				g_section_type[k] =	segsec_type(p[i].segname, p[i].sectname);
				i++;
			}
		}
		cmd_iter = (void *)cmd_iter + cmd_iter->cmdsize;
	}
	return ((t_symtab_cmd *)cmd_iter);
}

char			get_type(t_nlist_64 symbol)
{
	symbol.n_type &= ~N_EXT;
	if (symbol.n_type == N_UNDF && !symbol.n_value)
		return ('U');
	else if (symbol.n_type == N_UNDF)
		return ('C');
	else if (symbol.n_type == N_ABS)
		return ('A');
	else if (symbol.n_type == N_INDR)
		return ('I');
	else if (symbol.n_type == N_SECT)
		return (g_section_type[symbol.n_sect]);
	else
		return ('\0');
}

t_pqueue		*get_symbol(t_nlist_64 *symtab, char *strtab, uint32_t num_syms)
{
	uint32_t	i;
	t_pqueue	*alph_queue;
	t_symbol	curr_symbol;

	if (!(alph_queue = init_pqueue()))
		return (NULL);
	i = 0;
	while (i < num_syms)
	{
		curr_symbol.value = symtab[i].n_type != N_UNDF ? symtab[i].n_value : 0;
		if ((curr_symbol.type = get_type(symtab[i])))
		{
			if (!(symtab[i].n_type & N_EXT))
				curr_symbol.type += 32;
			curr_symbol.name = strtab + symtab[i].n_un.n_strx;
			ft_enpqueue(alph_queue, &curr_symbol, sizeof(t_symbol), lex_compare);
		}
		i++;
	}
	return (alph_queue);
}

void			print_symbols(t_pqueue *symbols)
{
	t_symbol	*curr_symb;

	while ((curr_symb = ft_depqueue(symbols)))
	{
		if (ft_toupper(curr_symb->type) != 'U')
			ft_printf("%016llx ", curr_symb->value);
		else
			ft_printf("%17c", ' ');
		ft_printf("%c %s\n", curr_symb->type, curr_symb->name);
		free(curr_symb);
	}
	free(symbols);
}