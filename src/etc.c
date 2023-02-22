/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghso <seunghso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:38:55 by seunghso          #+#    #+#             */
/*   Updated: 2023/02/16 21:19:22 by seunghso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	clear_game(t_game *game)
{
	int	score;

	score = game->play_info.score - game->play_info.move_cnt;
	printf("\n################\n\n");
	printf("GAME CLEAR!!\n\n");
	printf("Your Score: %d\n", score);
	printf("\n################\n\n");
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int	exit_game(t_game *game)
{
	printf("\n###########\n\n");
	printf("GAME OVER!!\n");
	printf("\n###########\n\n");
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

void	print_err(char *str)
{
	printf("Error: %s", str);
	exit(0);
}
