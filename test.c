# include "./mlx/mlx.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

// WASD
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

// KEYBOARD ESC
# define K_ESC 53

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

// EVENT KEY
#define X_EVENT_KEY_PRESS   2
#define X_EVENT_KEY_EXIT    17



/*
	texture를 입히기 위해서는 verLine() 함수를 이용해 수직선을 그리는 방식은 버려야 한다.
	대신, 픽셀을 하나하나 그려줄 것이다.
	우리가 사용할 방식을 쉽게 설명하면 2차원짜리 '버퍼'를 이용, 
	한번에 (변경된)화면을 출력하는 것이다.

	아래의 texWidth, texHeight는 텍스쳐의 텍셀 너비, 높이 값이다.

*/
#define texWidth 64
#define texHeight 64

// get_img_data_addr 함수에서 쓸 변수를 갖고 있는 구조체.
typedef struct    s_img
{
	void    *img;
	int        *data;

	int        size_l;
	int        bpp;
	int        endian;
}                t_img;

typedef struct    s_info
{
	double playerPositionX;
	double playerPositionY;
	double directionVectorX;
	double directionVectorY;
	double planeX;
	double planeY;
	void    *mlx;
	void    *win;
	double    moveSpeed;
	double    rotSpeed;

// textured에서 아래 세 변수가 추가됨.
	t_img   img;
	int     **buf;
	int     texture[8][texHeight * texWidth];
}                t_info;

int calculateAndSaveToMap(t_info *info);
void imageDraw(t_info *info);

// textured 에서 변경된 map. 요소가 추가됐다.
int    worldMap[mapWidth][mapHeight] =
						{
							{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
							{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
							{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
							{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
							{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
							{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
							{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
							{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
							{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
							{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
							{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
							{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
							{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
							{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
							{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
							{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
							{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
							{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
							{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
							{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
						};

int main_loop(t_info *info)
{
	calculateAndSaveToMap(info);
	imageDraw(info);

	// warning 방지용.
	return (0);
}

void imageDraw(t_info *info)
{
	for (int y = 0; y < screenHeight; y++)
		for (int x = 0; x < screenWidth; x++)
			info->img.data[y * screenWidth + x] = info->buf[y][x];

	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int calculateAndSaveToMap(t_info *info)
{

	// 화면 생성 후 게임 루프 시작.
	// while문은 전체 프레임을 그려내고 입력을 읽는 역할을 함.
	int x;

	for (int x = 0; x < screenWidth; x++)
	{
		for (int y = 0; y < screenHeight; y++)
		{
			info->buf[y][x] = 0xFFFFFF; 
			info->buf[screenHeight - y - 1][x] = 0x000000;
			// buf[screenHeight - 1 ~ screenHeight - screenHeight][x] 를 칠해줌.
		}
	}

	x = 0;
	while (x < screenWidth)
	{
		double cameraX = (2 * x / (double)(screenWidth)) - 1;

		double rayDirectionX = info->directionVectorX + info->planeX * cameraX;
		double rayDirectionY = info->directionVectorY + info->planeY * cameraX;

		int mapX = (int)(info->playerPositionX);
		int mapY = (int)(info->playerPositionY);

		double sideDistX;
		double sideDistY;

		double deltaDistX = fabs(1 / rayDirectionX);
		double deltaDistY = fabs(1 / rayDirectionY);

		// 광선의 이동거리를 계산할 때 사용할 변수.
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirectionX < 0)
		{
			stepX = -1;
			sideDistX = (info->playerPositionX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->playerPositionX) * deltaDistX;
		}
		if (rayDirectionY < 0)
		{
			stepY = -1;
			sideDistY = (info->playerPositionY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->playerPositionY) * deltaDistY;
		}

		while (hit == 0)
		{
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
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - info->playerPositionX + (1 - stepX) / 2) / rayDirectionX;
		else
			perpWallDist = (mapY - info->playerPositionY + (1 - stepY) / 2) / rayDirectionY;

		int lineHeight = (int)(screenHeight / perpWallDist);

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
		int texNum = worldMap[mapX][mapY] - 1;
		// int textNum = worldMap[mapX][mapY];

		// wallX의 값은 벽의 x면과 부딪힌 경우(side == 0)
		// 벽의 Y좌표가 된다.
		// wallX의 값은 텍스처의 x좌표에 대해서만 사용한다.
		double wallX;
		if (side == 0)
			wallX = info->playerPositionY + perpWallDist * rayDirectionY;
		else
			wallX = info->playerPositionX + perpWallDist * rayDirectionX;
		wallX -= floor(wallX);

		// texX는 texture의 x좌표를 나타낸다.
		// x coordinate on the texture
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
			int color = info->texture[texNum][texHeight * texY + texX];
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

int key_press(int key, t_info *info)
{
	// WS
	if (key == KEY_W)
	{
		if (!worldMap[(int)(info->playerPositionX + info->directionVectorX * info->moveSpeed)][(int)(info->playerPositionY)])
			info->playerPositionX += info->directionVectorX * info->moveSpeed;
		if (!worldMap[(int)(info->playerPositionX)][(int)(info->playerPositionY + info->directionVectorY * info->moveSpeed)])
			info->playerPositionY += info->directionVectorY * info->moveSpeed;
	}

	if (key == KEY_S)
	{
		if (!worldMap[(int)(info->playerPositionX - info->directionVectorX * info->moveSpeed)][(int)(info->playerPositionY)])
			info->playerPositionX -= info->directionVectorX * info->moveSpeed;
		if (!worldMap[(int)(info->playerPositionX)][(int)(info->playerPositionY - info->directionVectorY * info->moveSpeed)])
			info->playerPositionY -= info->directionVectorY * info->moveSpeed;
	}

   // AD
	if (key == KEY_A)
	{
		double oldDirectionX = info->directionVectorX;
		info->directionVectorX = info->directionVectorX * cos(info->rotSpeed) - info->directionVectorY * sin(info->rotSpeed);
		info->directionVectorY = oldDirectionX * sin(info->rotSpeed) + info->directionVectorY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}

	if (key == KEY_D)
	{
		double oldDirectionX = info->directionVectorX;
		info->directionVectorX = info->directionVectorX * cos(-info->rotSpeed) - info->directionVectorY * sin(-info->rotSpeed);
		info->directionVectorY = oldDirectionX * sin(-info->rotSpeed) + info->directionVectorY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	if (key == K_ESC)
		exit(0);
	return (0);
}

int main()
{
	t_info info;
	info.mlx = mlx_init();

	// info는 아래 필드 모두를 가지고 있다.
	info.playerPositionX = 12;
	info.playerPositionY = 5;
	info.directionVectorX = -1;
	info.directionVectorY = 0;
	info.planeX = 0;
	info.planeY = 0.66;
	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;

/* 
		버퍼를 초기화해준다.
		버퍼는 우리가 띄운 창의 크기와 같다.
		x->screenWidth 로 가면서 화면을 그려내기 때문에
		y값이 버퍼의 앞에 온다.(info.buf는 [y][x] 형태)
	*/
	info.buf = (int **)malloc(sizeof(int *) * screenHeight);
	for (int i = 0; i < screenHeight; i++)
		info.buf[i] = (int *)malloc(sizeof(int) * screenWidth);

	for (int i = 0; i < screenHeight; i++)
		for (int j = 0; j < screenWidth; j++)
			info.buf[i][j] = 0;

	/*
		info.texture 변수는 다음과 같이 선언돼 있는데,
			int        texture[8][texHeight * texWidth];
		이것이 의미하는 바는 총 8가지 종류의 텍스쳐를 저장할 수 있고,
		그 크기가 texHeight * texWidth 라는 뜻이다.
	*/
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < texHeight * texWidth; j++)
			info.texture[i][j] = 0;

	/*
		텍스쳐를 생성한다. 
		(비트 연산자인) xor 컬러 및 x, xy 컬러를 지정한다.
		세 가지 값은 각각 xor패턴, 그라데이션, 벽돌스타일의 패턴을 나타낸다.
		각각의 텍스쳐 값 뒤에 그것이 무엇을 의미하는지에 대한 주석이 달려 있습니다.
	*/        
	for (int x = 0; x < texWidth; x++)
	{
		for (int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			info.texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
			info.texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			info.texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			info.texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			info.texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
			info.texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			info.texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			info.texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}
	// textured에서 추가된 코드 세 줄.
	info.win = mlx_new_window(info.mlx, screenWidth, screenHeight, "mlx");
	info.img.img = mlx_new_image(info.mlx, screenWidth, screenHeight);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);

	// 아래 코드들이 무슨 역할을 하는 지 궁금하다면 아래 링크에서 정리해둔 내용을 보자.
	// https://42kchoi.tistory.com/229
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_loop(info.mlx);    
}