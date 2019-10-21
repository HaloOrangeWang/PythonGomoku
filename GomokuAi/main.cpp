#include <stdio.h>
#include <stdlib.h>
#include "ai.h"

void ai_1step(char* p_init_map, char* p_init_depth, char* p_player_first, char* p_max_depth)
{
    // 1 转换参数
    int init_map[15][15];
    int init_depth;
    bool player_first;
    uint32_t max_depth;
    for (int t = 0; t <= 224; t++){
        init_map[t / 15][t % 15] = p_init_map[t] - '0';
    }
    init_depth = atoi(p_init_depth);
    player_first = p_player_first[0] - '0';
    max_depth = static_cast<uint32_t>(atoi(p_max_depth));

    char g[550];
    sprintf(g, "%d %d %d.\n", init_depth, player_first, max_depth);

    // 2 进行运算
    AI1Step* pai = new AI1Step(init_map, init_depth, player_first);
    pai->Search(0, max_depth);

    // 3 输出游戏结果
    Point FinalRes = pai->GetFinalRes();
    printf("%d\n%d\n%d\n", pai->MethodTree.size(), FinalRes.X, FinalRes.Y);
}

void test()
{
    int game_map[15][15] = {
        {1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 1},
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    Node a(game_map, Point(-1, -1), 0, 0, 0, true, 0);
    a.Score = a.CalcScore();
    printf("%d\t", a.Score);
}

int main(int argc, char** argv)
{
#if AI_DEBUG
    test();
    getchar();
#else
    if (argc == 5)
    {
        ai_1step(argv[1], argv[2], argv[3], argv[4]);
    }else{
        printf("参数不正确.\n");
        abort();
    }
#endif
    return 0;
}
