/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_so.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:39:30 by hmoumani          #+#    #+#             */
/*   Updated: 2020/11/02 18:39:31 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	ft_treat_so(char *line)
{
	char *file_name;

	if (g_conf.so.height != -1)
		ft_error("South texture repeated.\n");
	file_name = ft_strtrim(line + 2, " ");
	if (!ft_is_end_with(file_name, ".xpm"))
		ft_error("in South texture. file extension is not valid!\n");
	g_conf.so.img = mlx_xpm_file_to_image(g_env.ptr, file_name, \
	&g_conf.so.width, &g_conf.so.height);
	if (!g_conf.so.img)
		ft_error("in south texture. can't open file! \n");
	g_conf.so.addr = (unsigned int *)mlx_get_data_addr(g_conf.so.img, \
	&g_conf.so.bpp, &g_conf.so.line_length, &g_conf.so.endian);
	g_conf.count++;
	free(file_name);
}
