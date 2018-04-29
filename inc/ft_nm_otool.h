/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 11:30:25 by satkins           #+#    #+#             */
/*   Updated: 2018/04/29 15:39:36 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_OTOOL_H

# define FT_NM_OTOOL_H

# include "libft.h"

# include <mach-o/nlist.h>
# include <mach-o/loader.h>
# include <sys/mman.h>
# include <sys/stat.h>

typedef struct symtab_command t_symtab_cmd;
typedef struct stat t_stat;
typedef struct load_command t_load_cmd;
typedef struct nlist_64 t_nlist_64;
typedef struct segment_command_64 t_segment_cmd_64;
typedef struct section t_section;
typedef struct mach_header_64 t_mach_header_64;

# define BIT_64 64

typedef struct	s_symbol
{
	char		type;
	char		*name;
	uint64_t	value;
}				t_symbol;

int				lex_compare(void *insert_str, void *existing_str);
t_symtab_cmd	*get_symtab_cmd(void *command_head);
t_pqueue		*get_symbol(t_nlist_64 *symtab, char *strtab, uint32_t num_syms);
void			print_symbols(t_pqueue *symbols);
void			*open_n_map_file(char *file);
int				validate_magic(void *file_ptr);
#endif
