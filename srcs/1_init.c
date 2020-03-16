/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:10:22 by jwisozk           #+#    #+#             */
/*   Updated: 2019/12/06 15:19:19 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				ft_check_argv(char *str)
{
    char *ext;
    int  len;
    int  i;

    i = 0;
    ext = EXTENSION;
    len = ft_strlen(str);
    str += len - 3;
    while (i < 3 && *ext++ == *str++)
        i++;
    if (i != 3)
        ft_print(ft_msg(ERROR_1));
}

void				ft_open_file(char *name, int *fd)
{
    if ((*fd = open(name, O_RDONLY)) == -1)
        ft_print(ft_msg(ERROR_6));
}

void				ft_close_file(const int fd)
{
    if (close(fd) == -1)
        ft_print(ft_msg(ERROR_28));
}

