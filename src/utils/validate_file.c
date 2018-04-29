/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 13:20:13 by satkins           #+#    #+#             */
/*   Updated: 2018/04/29 15:39:26 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int		validate_magic(void *file_ptr)
{
	t_mach_header_64	*header;

	if (!(header = file_ptr))
		return (EXIT_FAILURE);
	if (header->magic == MH_MAGIC_64)
		return (BIT_64);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}