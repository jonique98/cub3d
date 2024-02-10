
#include "cub.h"
void init_map(t_map *map) {
    // 맵 크기 설정
    map->map_width = mapWidth;
    map->map_height = mapHeight;

    // 맵 동적 할당
    map->map = (int **)malloc(sizeof(int *) * map->map_width);
    for (int i = 0; i < map->map_width; i++)
        map->map[i] = (int *)malloc(sizeof(int) * map->map_height);

    // 맵 채우기
    for (int i = 0; i < map->map_width; i++) {
        for (int j = 0; j < map->map_height; j++) {
            if (i == 0 || i == map->map_width - 1 || j == 0 || j == map->map_height - 1)
                map->map[i][j] = 1; // 테두리는 1로 초기화
            else
                map->map[i][j] = 0; // 내부는 0으로 초기화
        }
    }

    // 2, 3, 4의 개수를 세기 위한 변수 초기화
    int count_2 = 0, count_3 = 0, count_4 = 0;

    // 내부에 2, 3, 4를 총 10개 이하로 채우기
    while (count_2 + count_3 + count_4 < 10) {
        int x = rand() % (mapWidth - 2) + 1;
        int y = rand() % (mapHeight - 2) + 1;

        // 이미 값이 있는 경우 건너뜀
        if (map->map[x][y] != 0)
            continue;

        // 2, 3, 4 중 하나를 랜덤으로 선택하여 할당
        int value = rand() % 3 + 2;
        map->map[x][y] = value;

        // 개수 카운트 증가
        if (value == 2)
            count_2++;
        else if (value == 3)
            count_3++;
        else if (value == 4)
            count_4++;
    }
}
