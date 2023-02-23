#include "../include/cub3D.h"
#include <math.h>

void imageDraw(t_game *info)
{
    for (int y = 0; y < RESOLUTION_H; y++)
        for (int x = 0; x < RESOLUTION_W; x++)
            info->data[y * RESOLUTION_W + x] = info->buf[y][x];

    mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
}

void calculateAndSaveToMap(t_game *info)
{
	for (int x = 0; x < RESOLUTION_W; x++)
    {
        for (int y = 0; y < RESOLUTION_H; y++)
        {
            info->buf[y][x] = 0xFFFFFF; 
            info->buf[RESOLUTION_H - y - 1][x] = 0x000000;
            // buf[screenHeight - 1 ~ screenHeight - screenHeight][x] 를 칠해줌.
        }
    }
	int screenHeight = 1080;
	int screenWidth = 1920;

	int x =0;
	while (x < screenWidth)
    {
        // cameraX 는 for문의 x값이 카메라 평면 상에 있을 때의 x좌표.
        double cameraX = (2 * x / (double)(screenWidth)) - 1;
        // cameraPlaneX == 0; cameraPlaneY == 0.66; dirVecX = -1; dirVecY = 0;
        // 광선의 방향은 방향벡터 + 카메라평면 * 배수.
        double rayDirectionX = info->play_info.dir_x + info->planeX * cameraX;
        double rayDirectionY = info->play_info.dir_y + info->planeY * cameraX;
        /*
            DDAgorithm
        */
        // 현재 player가 위치한 맵 내 위치.(which box of the map)
        int mapX = (int)(info->play_info.x);
        int mapY = (int)(info->play_info.y);
        
		// 현재 위치에서 다음 x사이드 또는 y사이드까지의 거리.
        // 이를 이하 '첫 번째 x면 및 y면'이라고 부를 것.
        double sideDistX;
        double sideDistY;

        // 아래 두 변수가 왜 저렇게 구해지는지에 대해서는 ii2r github #6 참고. 
        // deltaDistX는 첫 번째 x면에서 그 다음 x면까지의 광선의 이동거리.
        // 이 경우 x는 1만큼 이동.
        // abs함수는 정수 절대값
        // fabs함수는 실수 절대값
        double deltaDistX = fabs(1 / rayDirectionX);
        // deltaDistY는 첫 번째 y면에서 그 다음 y면까지의 광선의 이동거리.
        // 이 경우 y는 1만큼 이동.
        double deltaDistY = fabs(1 / rayDirectionY);

        // 광선의 이동거리를 계산할 때 사용할 변수.
        double perpWallDist;

        // DDAgorithm은 반복문을 실행할 때마다 x, y방향으로 딱 한 칸씩 점프.
        // 광선의 방향에 따라 어느 방향으로 건너뛰는지 달라짐.
        // 그 정보는 stepX, Y에 +1, -1 둘 중 하나로 저장됨.
        int stepX;
        int stepY;

        /*
            hit은 벽과 부딪혔는지 판별하기 위한 변수임.
            부딪힌다는 것은 루프를 종료하기 위한 조건이 됨.
            만약 벽에 부딪혔는데 그게 x면에 부딪힌 거라면 side = 0임.
            y면에 부딪혔다면 1이 됨.
            한편 x면, y면은 어떤 칸의 경계가 되는 선을 의미함.
        */
        int hit = 0;
        int side;

        /*
            DDAgorithm을 시작하기 전에 
            stepX, Y 그리고 sideDistX, Y에 값을 넣어주는 부분이다.
            rayDirectionX가 음수라는 말은 player기준 왼각이라는 뜻이고,
            양수라는 말은 player기준 오른각이라는 뜻이다.
            sideDistX의 값은 rayDirectionX 값이 양수인 경우
            광선의 오른쪽으로 이동하다 처음 만나는 x면까지의 거리가 된다.
            sideDistY의 값은 rayDirectionY 값이 양수인 경우
            광선의 위쪽으로 이동하다 처음 만나는 y면까지의 거리가 된다.
            rayDirectionX가 양수일 경우 sideDistX는 
            mapX + 1에서 실제 위치 playerPositionX를 빼주고 deltaDistX를 곱한 결과다.
            반대의 경우 playerPositionX에서 mapX를 빼주고 deltaDistX를 곱한 결과다.
        */
        if (rayDirectionX < 0)
        {
            stepX = -1;
            sideDistX = (info->play_info.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - info->play_info.x) * deltaDistX;
        }
        if (rayDirectionY < 0)
        {
            stepY = -1;
            sideDistY = (info->play_info.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - info->play_info.y) * deltaDistY;
        }

        /*
            DDAgorithm 세팅을 완료했고, 이제 그것을 시작하는 부분.
            아래 while문은 `벽에 부딪힐 때까지` 매번 한 칸씩 광선 이동.
            반복할 때마다 x방향으로 한 칸 또는 y방향으로 한 칸 점프.
            만약 광선의 방향이 x축 방향과 완전히 일치한다면, x방향으로만 한 칸 점프하면 됨.
            광선이 점프할 때마다 <sideDistX, Y>에는 <deltaDistX, Y>가 더해지면서 업데이트됨.
        */
        while (hit == 0)
        {
            // 다음 map 박스로 이동하거나 x, y 방향 둘 중 하나로 이동한다.
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX; // stepX 는 1, -1 중 하나.
                side = 0; // x면에 부딪혔다면 side = 0
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY; // stepY는 1, -1 중 하나.
                side = 1; // y면에 부딪혔다면 side = 1
            }
            // ray가 벽을 만났는지 확인하는 작업
            if (info->map_info.map[mapX][mapY] == '1')
                hit = 1;
        }
        /*
            벽을 만나 DDAgorithm이 완료됨.
            이제 광선의 시작점에서 벽까지의 이동거리를 계산할 차례임.
            광선의 시작점에서 벽까지의 이동거리는 벽의 높이를 계산하는 데 쓰임.
            H------------ :wall
            | \          \: 실제거리
            |  \         |: 벽에서 camera plane까지의 거리.
            -----P------- :camera plane
            P를 기준으로 벽까지의 실제거리를 사용한다면 fisheye 부작용이 나타남.
            따라서 벽으로부터 cameraPlane까지의 거리를 사용해야.
            이에 대한 자세한 설명은 로데브 설명 참고.
            따라서 아래 if-else문은 fisheye (side)effect를 방지하는 코드.
            (1 - stepX) / 2는 stepX가 -1이면 1이되고 1이면 0이 된다.(-1 or 0)
            해당 연산은 mapX - playerPositionX가 < 0 일 때, 즉 벽 밖으로 갈 때
            길이에 1을 더해주기 위한 코드이다.
            수직거리를 계산하는 방법은 이렇다. 
            만약 광선이 처음으로 부딪힌 면이 x면이면 
                mapX - playerPositionX + (1 - stepX / 2)는
                광선이 x방향으로 몇 칸이나 갔는지를 나타낸다.(정수 아니어도 됨.)
                rayDirectionX로 나눠주는 이유는 구해진 값이 수직거리보다 크기 때문.
            y면에 처음 부딪혔을 때도 같은 원리로 동작.
            mapX - playerPostionX가 음수더라도 음수인 rayDirectionX로 나누기 때문에
            계산된 값은 항상 양수임.
        */
        if (side == 0)
            perpWallDist = (mapX - info->play_info.x + (1 - stepX) / 2) / rayDirectionX;
        else
            perpWallDist = (mapY - info->play_info.y + (1 - stepY) / 2) / rayDirectionY;

        // 스크린에 그릴 line의 높이를 계산.
        int lineHeight = (int)(screenHeight / perpWallDist);

		/*
            이제 계산한 거리를 가지고 화면에 그려야 하는 선의 높이를 구할 수 있다.
            벽을 더 높게 그리거나 낮게 그리고 싶으면 2 * lineHeight 같은 값을 넣을 수도 있다.
            위에서 구한 lineHeight로부터 우리는 선을 그릴 위치의 시작점과 끝점을 구해낼 수 있다.
            만약에 벽의 범위 (0 ~ screenHeight)를 벗어나는 경우 
            각각 0과 screenHeight - 1을 대입한다.
                +) drawStart와 End에 2로 나눈 값들을 더하는 이유는
                   screenHeight보다 drawEnd가 커지면 될까 안될까를 생각해보면 알 수 있다.
        */
        int drawStart = (-lineHeight / 2) + (screenHeight / 2);
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = (lineHeight / 2) + (screenHeight / 2);
        if (drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;
        // texturing calculations
        // 1을 빼주는 이유는 0번째 텍스쳐도 0, 벽이 없어도 0이기 때문.
        // 1을 빼지 않는다면 어떻게 될까?
        // 아마 시작하자마자 뒷방향을 보고 앞으로 걸어나가려고 하면 
        // segmentation fault가 뜰 것이다.
        // int texNum = info->map_info.map[mapX][mapY] - 1;
        // int textNum = worldMap[mapX][mapY];

        // wallX의 값은 벽의 x면과 부딪힌 경우(side == 0)
        // 벽의 Y좌표가 된다.
        // wallX의 값은 텍스처의 x좌표에 대해서만 사용한다.
        double wallX;
        if (side == 0)
            wallX = info->play_info.y + perpWallDist * rayDirectionY;
        else
            wallX = info->play_info.x + perpWallDist * rayDirectionX;
        wallX -= floor(wallX);

        // texX는 texture의 x좌표를 나타낸다.
        // x coordinate on the texture
		int texWidth = 64;
		int texHeight = 64;
        int texX = (int)(wallX * (double)texWidth);
        if (side == 0 && rayDirectionX > 0)
            texX = texWidth - texX - 1;
        if (side == 1 && rayDirectionY < 0)
            texX = texWidth - texX - 1;

        /*
            texY를 지정하는 반복문.
            step은 스크린 픽셀당 texture 좌표를 얼마나 증가시켜줄 건지를 결정.
            buffer[y][x]에 넣을 color는 texture 배열에서 가져온다.
        */
        // How much to increase the texture coordinate perscreen pixel
        double step = 1.0 * texHeight / lineHeight;
        // Starting texture coordinate
        double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            int color = info->imgs.wall_no.addr[64 * texY + texX];
            // 광선이 벽의 y면에 부딪힌 경우(side == 1).
            // 조명표현을 위해 색상을 더 검게 만든다.
            // 이진수를 2로 나눔으로써 RGB값을 반감시킨다.
            // 시프트 연산을 하고 01111111 01111111 01111111(835711)을 & 연산하면
            // 어두운 값을 줄 수 있다는데 그냥 외워야 쓰것다.
            if (side == 1)
                color = (color >> 1) & 8355711;
            info->buf[y][x] = color;
        }
        x++;
    }
}

int	main_loop(t_game *game)
{
	calculateAndSaveToMap(game);
    imageDraw(game);
	// (void)game;
	// render_map(game);
	// if (game->flame > 30)
	// 	put_specified_image(game, PLAYER1, game->play_info.player_loc);
	// else
	// 	put_specified_image(game, PLAYER2, game->play_info.player_loc);
	// if (game->flame > 30)
	// 	put_specified_image(game, PATROL1, game->play_info.patrol_loc);
	// else
	// 	put_specified_image(game, PATROL2, game->play_info.patrol_loc);
	// if (game->play_info.player_loc == game->play_info.patrol_loc)
	// 	exit_game(game);
	// game->flame++;
	// if (game->flame > 60)
	// 	game->flame = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		game;

	init_game(&game, argc, argv);
	game.buf = (int **)malloc(sizeof(int *) * RESOLUTION_H);
	for(int i=0; i<RESOLUTION_H; i++)
		game.buf[i] = (int *)malloc(sizeof(int) * RESOLUTION_W);
	
	for (int i=0; i<RESOLUTION_H; i++)
		for (int j=0; j<RESOLUTION_W; j++)
			game.buf[i][j] = 0;
	
	game.planeX = 0.0;
    game.planeY = 0.66;
	
	game.img = mlx_new_image(game.mlx, RESOLUTION_W, RESOLUTION_H);
	int        size_l;
    int        bpp;
    int        endian;
	game.data = (int *)mlx_get_data_addr(game.img, &bpp, &size_l, &endian);

	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &exit_game, &game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
