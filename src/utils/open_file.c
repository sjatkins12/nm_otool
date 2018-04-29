/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 12:46:22 by satkins           #+#    #+#             */
/*   Updated: 2018/04/29 14:20:31 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	*open_n_map_file(char *file)
{
	int				fd;
	void			*file_head;
	t_stat			sb;

	file_head = NULL;
	if ((fd = open(file, O_RDWR)) < 0
		|| fstat(fd, &sb) == -1
		|| (file_head = mmap(file_head, sb.st_size, PROT_READ,
		MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (NULL);
	close(fd);
	return (file_head);
}
