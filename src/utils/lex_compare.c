/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_compare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 17:28:00 by satkins           #+#    #+#             */
/*   Updated: 2018/04/27 17:43:07 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int		lex_compare(void *insert_symb, void *existing_symb)
{
	t_symbol	*ins_symb;
	t_symbol	*exis_symb;

	ins_symb = insert_symb;
	exis_symb = existing_symb;
	return (ft_strcmp(ins_symb->name, exis_symb->name) <= 0);
}
