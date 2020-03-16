/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_sdl2_key_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:11:36 by jwisozk           #+#    #+#             */
/*   Updated: 2019/12/06 14:11:36 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void    ft_sdl2_key_quit(SDL_Event e, int *running)
{
    if((SDL_QUIT == e.type) ||
       (SDL_KEYDOWN == e.type &&
        SDL_SCANCODE_ESCAPE == e.key.keysym.scancode))
        *running = 0;
}
