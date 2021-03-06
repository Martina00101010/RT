/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_sdl2_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:11:38 by jwisozk           #+#    #+#             */
/*   Updated: 2019/12/06 14:11:38 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_sdl2_quit(t_sdl *sdl)
{
    SDL_DestroyTexture(sdl->tex);
    SDL_DestroyRenderer(sdl->ren);
    SDL_DestroyWindow(sdl->win);
    SDL_Quit();
}

void    ft_sdl2_render(t_sdl *sdl)
{
    SDL_UpdateTexture(sdl->tex, NULL, sdl->pixels, sdl->pitch);
    SDL_RenderCopy(sdl->ren, sdl->tex, NULL, NULL);
    SDL_RenderPresent(sdl->ren);
}

void    ft_sdl2_events(SDL_Event e, int *running)
{
    while(SDL_PollEvent(&e))
    {
        ft_sdl2_key_quit(e, running);
    }
}

void    ft_sdl2_loop(t_sdl *sdl)
{
    int     running;

    running = 1;
    while (running)
    {
        ft_sdl2_events(sdl->e, &running);
    }
}

void    ft_sdl2_init(t_sdl *sdl)
{
	sdl->pitch = DW * 4;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		ft_print((char*)SDL_GetError());
	if (!(sdl->win = SDL_CreateWindow(TITLE_WINDOW, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DW, DH, SDL_WINDOW_ALLOW_HIGHDPI)))
		ft_print((char*)SDL_GetError());
	if (!(sdl->ren = SDL_CreateRenderer(sdl->win, -1, 0)))
		ft_print((char*)SDL_GetError());
	if (!(sdl->tex = SDL_CreateTexture(sdl->ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, DW, DH)))
		ft_print((char*)SDL_GetError());
}

void    ft_sdl2_main(t_sdl   *sdl)
{
    ft_sdl2_init(sdl);
    ft_sdl2_render(sdl);
    ft_sdl2_loop(sdl);
    ft_sdl2_quit(sdl);
}