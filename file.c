/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 12:03:49 by hmoumani          #+#    #+#             */
/*   Updated: 2020/10/23 12:04:04 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include "lib.h"



void ft_init_config(char **line)
{
    g_conf = (t_config){-1, -1, (t_rgb){-1, -1, -1}, (t_rgb){-1, -1, -1}};
    g_conf.no = (t_texture){NULL, -1, -1};
    g_conf.so = (t_texture){NULL, -1, -1};
    g_conf.we = (t_texture){NULL, -1, -1};
    g_conf.ea = (t_texture){NULL, -1, -1};
    g_conf.spr = (t_texture){NULL, -1, -1};
    g_conf.count = 0;
    g_conf.max_width = 0;
    *line = NULL;
    g_conf.head = NULL;
}

void ft_read_conf(char *line)
{
    char **ptr;

    if ((ptr = ft_split(line, ' ', ft_count_words(line, ' '))) == NULL)
    {
        ft_putstr_fd("Error\nrestart the game please", 1);
        exit(1);
    }
    ft_redirect_to(ptr);
}

void	ft_read_map(char *line)
{
    int     len;
    t_list  *new;

    len = ft_strlen(line);
	g_conf.max_width = g_conf.max_width > len ? g_conf.max_width : len;
    new = ft_lstnew(line);
    // printf("%p\n", new->content);
    ft_lstadd_back(&g_conf.head, new);
}

int main(int argc, char **argv)
{
    int fd;
    char *line;
    int r;

    g_env.ptr = mlx_init();
    r = 1;
    if (argc != 2 && argc != 3)
    {
        ft_putstr_fd("Error\nusag: ./Cub3d MAPFILE.cub [--save]", 1);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) < 0)
    {
        perror("Error\n");
        exit(1);
    }
    ft_init_config(&line);
    while(r > 0)
    {
        r = get_next_line(fd, &line);
        if (g_conf.count != 8)
            ft_read_conf(line);
        else
			ft_read_map(line);
    }
    ft_handle_map();
}