#include <stdio.h>
#include <math.h>
#include "ai.h"


int Node::JudgeRes()
{
    // 1 判断是否有横向的连续五子
    for(int x = 0; x <= 10; x++){
        for (int y = 0; y <= 14; y++){
            if (GameMap[x][y] == 1 && GameMap[x + 1][y] == 1 && GameMap[x + 2][y] == 1 && GameMap[x + 3][y] == 1 && GameMap[x + 4][y] == 1)
                return 1;
            if (GameMap[x][y] == 2 && GameMap[x + 1][y] == 2 && GameMap[x + 2][y] == 2 && GameMap[x + 3][y] == 2 && GameMap[x + 4][y] == 2)
                return 2;
        }
    }
    // 2 判断是否有纵向的连续五子
    for (int x = 0; x <= 14; x++){
        for (int y = 0; y <= 10; y++){
            if (GameMap[x][y] == 1 && GameMap[x][y + 1] == 1 && GameMap[x][y + 2] == 1 && GameMap[x][y + 3] == 1 && GameMap[x][y + 4] == 1)
                return 1;
            if (GameMap[x][y] == 2 && GameMap[x][y + 1] == 2 && GameMap[x][y + 2] == 2 && GameMap[x][y + 3] == 2 && GameMap[x][y + 4] == 2)
                return 2;
        }
    }
    // 3 判断是否有斜向的连续五子
    for (int x = 0; x <= 10; x++){
        for (int y = 0; y <= 10; y++){
            if (GameMap[x][y] == 1 && GameMap[x + 1][y + 1] == 1 && GameMap[x + 2][y + 2] == 1 && GameMap[x + 3][y + 3] == 1 && GameMap[x + 4][y + 4] == 1)
                return 1;
            if (GameMap[x][y] == 2 && GameMap[x + 1][y + 1] == 2 && GameMap[x + 2][y + 2] == 2 && GameMap[x + 3][y + 3] == 2 && GameMap[x + 4][y + 4] == 2)
                return 2;
        }
    }
    for (int x = 0; x <= 10; x++){
        for (int y = 0; y <= 10; y++){
            if (GameMap[x + 4][y] == 1 && GameMap[x + 3][y + 1] == 1 && GameMap[x + 2][y + 2] == 1 && GameMap[x + 1][y + 3] == 1 && GameMap[x][y + 4] == 1)
                return 1;
            if (GameMap[x + 4][y] == 2 && GameMap[x + 3][y + 1] == 2 && GameMap[x + 2][y + 2] == 2 && GameMap[x + 1][y + 3] == 2 && GameMap[x][y + 4] == 2)
                return 1;
        }
    }
    return 0;
}

void Node::Judge4(uint64_t& ai_4_num, uint64_t& player_4_num){
    player_4_num = 0;
    ai_4_num = 0;
    int player_cnt, ai_cnt;
    // 1 是否有横向四子
    for(int x = 0; x <= 10; x++){
        for (int y = 0; y <= 14; y++){
            player_cnt = (GameMap[x][y] == 1) + (GameMap[x + 1][y] == 1) + (GameMap[x + 2][y] == 1) + (GameMap[x + 3][y] == 1) + (GameMap[x + 4][y] == 1);
            ai_cnt = (GameMap[x][y] == 2) + (GameMap[x + 1][y] == 2) + (GameMap[x + 2][y] == 2) + (GameMap[x + 3][y] == 2) + (GameMap[x + 4][y] == 2);
            if ((player_cnt == 4) && (ai_cnt == 0))
                player_4_num += 1;
            if ((player_cnt == 0) && (ai_cnt == 4))
                ai_4_num += 1;
        }
    }
    // 2 是否有纵向四子
    for (int x = 0; x <= 14; x++){
        for (int y = 0; y <= 10; y++){
            player_cnt = (GameMap[x][y] == 1) + (GameMap[x][y + 1] == 1) + (GameMap[x][y + 2] == 1) + (GameMap[x][y + 3] == 1) + (GameMap[x][y + 4] == 1);
            ai_cnt = (GameMap[x][y] == 2) + (GameMap[x][y + 1] == 2) + (GameMap[x][y + 2] == 2) + (GameMap[x][y + 3] == 2) + (GameMap[x][y + 4] == 2);
            if ((player_cnt == 4) && (ai_cnt == 0))
                player_4_num += 1;
            if ((player_cnt == 0) && (ai_cnt == 4))
                ai_4_num += 1;
        }
    }
    // 3 是否有斜向四子
    for (int x = 0; x <= 10; x++){
        for (int y = 0; y <= 10; y++){
            player_cnt = (GameMap[x][y] == 1) + (GameMap[x + 1][y + 1] == 1) + (GameMap[x + 2][y + 2] == 1) + (GameMap[x + 3][y + 3] == 1) + (GameMap[x + 4][y + 4] == 1);
            ai_cnt = (GameMap[x][y] == 2) + (GameMap[x + 1][y + 1] == 2) + (GameMap[x + 2][y + 2] == 2) + (GameMap[x + 3][y + 3] == 2) + (GameMap[x + 4][y + 4] == 2);
            if ((player_cnt == 4) && (ai_cnt == 0))
                player_4_num += 1;
            if ((player_cnt == 0) && (ai_cnt == 4))
                ai_4_num += 1;
        }
    }
    for (int x = 0; x <= 10; x++){
        for (int y = 0; y <= 10; y++){
            player_cnt = (GameMap[x + 4][y] == 1) + (GameMap[x + 3][y + 1] == 1) + (GameMap[x + 2][y + 2] == 1) + (GameMap[x + 1][y + 3] == 1) + (GameMap[x][y + 4] == 1);
            ai_cnt = (GameMap[x + 4][y] == 2) + (GameMap[x + 3][y + 1] == 2) + (GameMap[x + 2][y + 2] == 2) + (GameMap[x + 1][y + 3] == 2) + (GameMap[x][y + 4] == 2);
            if ((player_cnt == 4) && (ai_cnt == 0))
                player_4_num += 1;
            if ((player_cnt == 0) && (ai_cnt == 4))
                ai_4_num += 1;
        }
    }
}

void Node::Judge3D(uint64_t& ai_3d_num, uint64_t& player_3d_num){
    player_3d_num = 0;
    ai_3d_num = 0;
    // 1 xooox的形式
    // 1.1 横向xooox的形式
    for (int x = 0; x <= 10; x++){
        for (int y = 0; y <= 14; y++){
            if (GameMap[x][y] == 0 && GameMap[x + 1][y] == 1 && GameMap[x + 2][y] == 1 && GameMap[x + 3][y] == 1 && GameMap[x + 4][y] == 0)
                player_3d_num += 1;
            if (GameMap[x][y] == 0 && GameMap[x + 1][y] == 2 && GameMap[x + 2][y] == 2 && GameMap[x + 3][y] == 2 && GameMap[x + 4][y] == 0)
                ai_3d_num += 1;
        }
    }
    // 1.2 纵向xooox的形式
    for (int x = 0; x <= 14; x++){
        for (int y = 0; y <= 10; y++){
            if (GameMap[x][y] == 0 && GameMap[x][y + 1] == 1 && GameMap[x][y + 2] == 1 && GameMap[x][y + 3] == 1 && GameMap[x][y + 4] == 0)
                player_3d_num += 1;
            if (GameMap[x][y] == 0 && GameMap[x][y + 1] == 2 && GameMap[x][y + 2] == 2 && GameMap[x][y + 3] == 2 && GameMap[x][y + 4] == 0)
                ai_3d_num += 1;
        }
    }
    // 1.3 斜向xooox的形式
    for (int x = 0; x <= 10; x++){
        for (int y = 0; y <= 10; y++){
            if (GameMap[x][y] == 0 && GameMap[x + 1][y + 1] == 1 && GameMap[x + 2][y + 2] == 1 && GameMap[x + 3][y + 3] == 1 && GameMap[x + 4][y + 4] == 0)
                player_3d_num += 1;
            if (GameMap[x][y] == 0 && GameMap[x + 1][y + 1] == 2 && GameMap[x + 2][y + 2] == 2 && GameMap[x + 3][y + 3] == 2 && GameMap[x + 4][y + 4] == 0)
                ai_3d_num += 1;
        }
    }
    for (int x = 0; x <= 10; x++){
        for (int y = 0; y <= 10; y++){
            if (GameMap[x + 4][y] == 0 && GameMap[x + 3][y + 1] == 1 && GameMap[x + 2][y + 2] == 1 && GameMap[x + 1][y + 3] == 1 && GameMap[x][y + 4] == 0)
                player_3d_num += 1;
            if (GameMap[x + 4][y] == 0 && GameMap[x + 3][y + 1] == 2 && GameMap[x + 2][y + 2] == 2 && GameMap[x + 1][y + 3] == 2 && GameMap[x][y + 4] == 0)
                ai_3d_num += 1;
        }
    }

    // 2 xoxoox或xooxox的形式
    // 2.1 横向xoxoox或横向xooxox的形式
    for (int x = 0; x <= 9; x++){
        for (int y = 0; y <= 14; y++){
            if (GameMap[x][y] == 0 && GameMap[x + 1][y] == 1 && ((GameMap[x + 2][y] == 1) ^ (GameMap[x + 3][y] == 1)) && GameMap[x + 4][y] == 1 && GameMap[x + 5][y] == 0)
                player_3d_num += 1;
            if (GameMap[x][y] == 0 && GameMap[x + 1][y] == 2 && ((GameMap[x + 2][y] == 2) ^ (GameMap[x + 3][y] == 2)) && GameMap[x + 4][y] == 2 && GameMap[x + 5][y] == 0)
                ai_3d_num += 1;
        }
    }
    // 2.2 纵向xoxoox或纵向xooxox的形式
    for (int x = 0; x <= 14; x++){
        for (int y = 0; y <= 9; y++){
            if (GameMap[x][y] == 0 && GameMap[x][y + 1] == 1 && ((GameMap[x][y + 2] == 1) ^ (GameMap[x][y + 3] == 1)) && GameMap[x][y + 4] == 1 && GameMap[x][y + 5] == 0)
                player_3d_num += 1;
            if (GameMap[x][y] == 0 && GameMap[x][y + 1] == 2 && ((GameMap[x][y + 2] == 2) ^ (GameMap[x][y + 3] == 2)) && GameMap[x][y + 4] == 2 && GameMap[x][y + 5] == 0)
                ai_3d_num += 1;
        }
    }
    // 2.3 斜向xoxoox或斜向xooxox的形式
    for (int x = 0; x <= 9; x++){
        for (int y = 0; y <= 9; y++){
            if (GameMap[x][y] == 0 && GameMap[x + 1][y + 1] == 1 && ((GameMap[x + 2][y + 2] == 1) ^ (GameMap[x + 3][y + 3] == 1)) && GameMap[x + 4][y + 4] == 1 && GameMap[x + 5][y + 5] == 0)
                player_3d_num += 1;
            if (GameMap[x][y] == 0 && GameMap[x + 1][y + 1] == 2 && ((GameMap[x + 2][y + 2] == 2) ^ (GameMap[x + 3][y + 3] == 2)) && GameMap[x + 4][y + 4] == 2 && GameMap[x + 5][y + 5] == 0)
                ai_3d_num += 1;
        }
    }
    for (int x = 0; x <= 9; x++){
        for (int y = 0; y <= 9; y++){
            if (GameMap[x + 5][y] == 0 && GameMap[x + 4][y + 1] == 1 && ((GameMap[x + 3][y + 2] == 1) ^ (GameMap[x + 2][y + 3] == 1)) && GameMap[x + 1][y + 4] == 1 && GameMap[x][y + 5] == 0)
                player_3d_num += 1;
            if (GameMap[x + 5][y] == 0 && GameMap[x + 4][y + 1] == 2 && ((GameMap[x + 3][y + 2] == 2) ^ (GameMap[x + 2][y + 3] == 2)) && GameMap[x + 1][y + 4] == 2 && GameMap[x][y + 5] == 0)
                ai_3d_num += 1;
        }
    }
}

int Node::CalcScore(){
    // 1.如果能够连成五子，则记为100分
    const int res = JudgeRes();
    if (res == 2)
        return 100;
    else if (res == 1)
        return -100;

    // 2.判断玩家和电脑的四子的数目（需要保证：不是已经被堵死的四子）
    uint64_t ai_4_num;
    uint64_t player_4_num;
    Judge4(ai_4_num, player_4_num);

    // 3.如果能够连成活四，或连成双四，则记为90分
    if (PlayerFirst){
        if (Depth % 2 == 0){ //该轮到玩家出了
            if (player_4_num >= 2)
                return -90;
            else if (ai_4_num >= 2 && player_4_num == 0)
                return 90;
        }else{
            if (ai_4_num >= 2)
                return 90;
            else if (player_4_num >= 2 && ai_4_num == 0)
                return -90;
        }
    }else{
        if (Depth % 2 == 0){ //该轮到玩家出了
            if (ai_4_num >= 2)
                return 90;
            else if (player_4_num >= 2 && ai_4_num == 0)
                return -90;
        }else{
            if (player_4_num >= 2)
                return -90;
            else if (ai_4_num >= 2 && player_4_num == 0)
                return 90;
        }
    }

    // 4.从这里开始，对于force_score为False的情况，分数记为±inf
    if (ForceScore == false){
        if (PlayerFirst){
            if (Depth % 2 == 0) //该轮到玩家出了
                return INF;
            else //该轮到电脑出了
                return -INF;
        }else{
            if (Depth % 2 == 0) //该轮到电脑出了
                return -INF;
            else //该轮到玩家出了
                return INF;
        }
    }

    // 5.判断玩家和电脑的活三的数目
    uint64_t ai_3d_num;
    uint64_t player_3d_num;
    Judge3D(ai_3d_num, player_3d_num);

    // 6.如果能够连成四三，则记为80分
    if (PlayerFirst){
        if (Depth % 2 == 0){ //该轮到玩家出了
            if (player_4_num && player_3d_num)
                return -80;
            if (ai_4_num && ai_3d_num)
                return 80;
        }else{  //该轮到电脑出了
            if (ai_4_num && ai_3d_num)
                return 80;
            if (player_4_num && player_3d_num)
                return -80;
        }
    }else{
        if (Depth % 2 == 0){ //该轮到电脑出了
            if (ai_4_num && ai_3d_num)
                return 80;
            if (player_4_num && player_3d_num)
                return -80;
        }else{ //该轮到玩家出了
            if (ai_4_num && ai_3d_num)
                return 80;
            if (player_4_num && player_3d_num)
                return -80;
        }
    }

    // 7.如果能够连成四子，则记为70分
    if (PlayerFirst){
        if (Depth % 2 == 0){ //该轮到玩家出了
            if (player_4_num)
                return -70;
            if (ai_4_num)
                return 70;
        }else{  //该轮到电脑出了
            if (ai_4_num)
                return 70;
            if (player_4_num)
                return -70;
        }
    }else{
        if (Depth % 2 == 0){ //该轮到电脑出了
            if (ai_4_num)
                return 70;
            if (player_4_num)
                return -70;
        }else{ //该轮到玩家出了
            if (ai_4_num)
                return 70;
            if (player_4_num)
                return -70;
        }
    }

    // 8.如果能够连成双三，则记为60分
    if (PlayerFirst){
        if (Depth % 2 == 0){ //该轮到玩家出了
            if (player_3d_num >= 2)
                return -60;
            if (ai_3d_num >= 2)
                return 60;
        }else{  //该轮到电脑出了
            if (ai_3d_num >= 2)
                return 60;
            if (player_3d_num >= 2)
                return -60;
        }
    }else{
        if (Depth % 2 == 0){ //该轮到电脑出了
            if (ai_3d_num >= 2)
                return 60;
            if (player_3d_num >= 2)
                return -60;
        }else{ //该轮到玩家出了
            if (ai_3d_num >= 2)
                return 60;
            if (player_3d_num >= 2)
                return -60;
        }
    }

    // 9. 如果能够连成单活三，则记为50分
    if (PlayerFirst){
        if (Depth % 2 == 0){ //该轮到玩家出了
            if (player_3d_num)
                return -50;
            if (ai_3d_num)
                return 50;
        }else{  //该轮到电脑出了
            if (ai_3d_num)
                return 50;
            if (player_3d_num)
                return -50;
        }
    }else{
        if (Depth % 2 == 0){ //该轮到电脑出了
            if (ai_3d_num)
                return 50;
            if (player_3d_num)
                return -50;
        }else{ //该轮到玩家出了
            if (ai_3d_num)
                return 50;
            if (player_3d_num)
                return -50;
        }
    }
    // 10. 其他情况。按照棋子的分布来计分（根据这个棋子距离棋盘中心的距离，以及这个棋子周围8格棋子的个数来评分）
    int player_score_num = 0; //玩家和电脑所有棋子的得分总和
    int ai_score_num = 0;
    int player_piece_cnt = 0; //玩家和电脑的棋子数量
    int ai_piece_cnt = 0;
    for (int x = 0; x <= 14; x++){
        for (int y = 0; y <= 14; y++){
            if (GameMap[x][y] == 1){
                int around_cnt = 0;
                for (int x0 = x - 1; x0 <= x + 1; x0++){
                    for (int y0 = y - 1; y0 <= y + 1; y0++){
                        if (x0 >= 0 && x0 <= 14 && y0 >= 0 && y0 <= 14 && GameMap[x0][y0] != 0)
                            around_cnt += 1;
                    }
                }
                player_score_num += ScoreByNumArount[around_cnt] - abs(x - 7) - abs(y - 7);
                player_piece_cnt += 1;
            }
            if (GameMap[x][y] == 2){
                int around_cnt = 0;
                for (int x0 = x - 1; x0 <= x + 1; x0++){
                    for (int y0 = y - 1; y0 <= y + 1; y0++){
                        if (x0 >= 0 && x0 <= 14 && y0 >= 0 && y0 <= 14 && GameMap[x0][y0] != 0)
                            around_cnt += 1;
                    }
                }
                ai_score_num += ScoreByNumArount[around_cnt] - abs(x - 7) - abs(y - 7);
                ai_piece_cnt += 1;
            }
        }
    }
    if (ai_piece_cnt == 0 || player_piece_cnt == 0)
        return 0;
    return ai_score_num / ai_piece_cnt - player_score_num / player_piece_cnt;
}



set<Point> Node::GetOpeList()
{
    // 1 找到所有可以落子的点
    set<Point> ope_list = set<Point>();
    for (int x = 0; x <= 14; x++){
        for (int y = 0; y <= 14; y++){
            if (GameMap[x][y] != 0){
                for (int x0 = x - 1; x0 <= x + 1; x0++){
                    for (int y0 = y - 1; y0 <= y + 1; y0++){
                        Point temp_point(x0, y0);
                        if (x0 >= 0 && x0 <= 14 && y0 >= 0 && y0 <= 14 && ope_list.find(temp_point) == ope_list.end() && GameMap[x0][y0] == 0)
                            ope_list.insert(temp_point);
                    }
                }
            }
        }
    }
    return ope_list;
}

void AI1Step::Search(const uint64_t cur_node_dx, const uint64_t max_depth){
    // 1.首先确认什么地方可以落子。落子的条件是：这个格子必须为空，周围8格内必须有至少一个棋子
    set<Point> ope_list = MethodTree[cur_node_dx].GetOpeList();
    // 2. 然后对每一个可以落子的格子进行搜索
    for (set<Point>::iterator cell_it = ope_list.begin(); cell_it != ope_list.end(); cell_it++)
    {
        // 2.1 创建一个子节点，并计算这个子节点的分数
        int i_map[15][15];
        memcpy(i_map, MethodTree[cur_node_dx].GameMap, sizeof(int) * 15 * 15);
        if (PlayerFirst){
            if (MethodTree[cur_node_dx].Depth % 2 == 0) //轮到玩家出
                i_map[cell_it->X][cell_it->Y] = 1;
            else //轮到电脑出
                i_map[cell_it->X][cell_it->Y] = 2;
        }else{
            //这里和Python的code不一致
            if (MethodTree[cur_node_dx].Depth % 2 == 0) //轮到电脑出
                i_map[cell_it->X][cell_it->Y] = 2;
            else //轮到玩家出
                i_map[cell_it->X][cell_it->Y] = 1;
        }

        if (max_depth >= 2 && ope_list.size() >= 2) //对于非最终层的节点，不急于立即算出分数
        {
            Node node_new(i_map, *cell_it, MethodTree[cur_node_dx].Depth + 1, MethodTree[cur_node_dx].Alpha, MethodTree[cur_node_dx].Beta, false, PlayerFirst);
            node_new.Score = node_new.CalcScore();
            MethodTree.push_back(node_new);
        }else{
            Node node_new(i_map, *cell_it, MethodTree[cur_node_dx].Depth + 1, MethodTree[cur_node_dx].Alpha, MethodTree[cur_node_dx].Beta, true, PlayerFirst);
            node_new.Score = node_new.CalcScore();
            MethodTree.push_back(node_new);
        }
        unsigned long node_new_dx;
        node_new_dx = MethodTree.size() - 1;
        NextNodeList.push_back(-1); //记录每个节点下一步的动作
        if (MethodTree.size() >= MaxNodeNum)
        {
            printf("Method Tree is too big.\n");
            abort();
        }

        // 2.2 根据子节点的情况，进行父节点的后续操作
        if (MethodTree[node_new_dx].Score > -INF && MethodTree[node_new_dx].Score < INF){
            // 子节点有具体分数的情况下，就不用再进行更深层的迭代了
            if (PlayerFirst){
                if (MethodTree[cur_node_dx].Depth % 2 == 0){ //这一步是假想中玩家走的，因此需要让分数尽量小，且应该修改beta值
                    if (MethodTree[node_new_dx].Score < MethodTree[cur_node_dx].Score){
                        MethodTree[cur_node_dx].Score = MethodTree[node_new_dx].Score;
                        MethodTree[cur_node_dx].Beta = MethodTree[node_new_dx].Score;
                        NextNodeList[cur_node_dx] = static_cast<int>(node_new_dx);
                    }
                }else{ //这一步是假想中电脑走的，因此需要让分数尽量大，且应该修改alpha值
                    if (MethodTree[node_new_dx].Score > MethodTree[cur_node_dx].Score){
                        MethodTree[cur_node_dx].Score = MethodTree[node_new_dx].Score;
                        MethodTree[cur_node_dx].Alpha = MethodTree[node_new_dx].Score;
                        NextNodeList[cur_node_dx] = static_cast<int>(node_new_dx);
                    }
                }
            }
            
            else{
                if (MethodTree[cur_node_dx].Depth % 2 == 0){ //这一步是假想中电脑走的，因此需要让分数尽量大，且应该修改alpha值
                    if (MethodTree[node_new_dx].Score > MethodTree[cur_node_dx].Score){
                        MethodTree[cur_node_dx].Score = MethodTree[node_new_dx].Score;
                        MethodTree[cur_node_dx].Alpha = MethodTree[node_new_dx].Score;
                        NextNodeList[cur_node_dx] = static_cast<int>(node_new_dx);
                    }
                }else{  //这一步是假想中玩家走的，因此需要让分数尽量小，且应该修改beta值
                    if (MethodTree[cur_node_dx].Depth % 2 == 0){ //这一步是假想中玩家走的，因此需要让分数尽量小，且应该修改beta值
                        if (MethodTree[node_new_dx].Score < MethodTree[cur_node_dx].Score){
                            MethodTree[cur_node_dx].Score = MethodTree[node_new_dx].Score;
                            MethodTree[cur_node_dx].Beta = MethodTree[node_new_dx].Score;
                            NextNodeList[cur_node_dx] = static_cast<int>(node_new_dx);
                        }
                    }
                }
            }
        }else{
            //子节点还没有具体分数的情况下，应该以这个子节点为下一层的根节点，进行递归，之后再进行计算
            if (max_depth >= 2)
                Search(static_cast<uint64_t>(node_new_dx), max_depth - 1);
            //根据递归后计算的结果，计算这个节点的分数
            if (PlayerFirst){
                if (MethodTree[cur_node_dx].Depth % 2 == 0){ //这一步是假想中玩家走的，因此需要让分数尽量小，且应该修改beta值
                    if (MethodTree[node_new_dx].Score < MethodTree[cur_node_dx].Score){
                        MethodTree[cur_node_dx].Score = MethodTree[node_new_dx].Score;
                        MethodTree[cur_node_dx].Beta = MethodTree[node_new_dx].Score;
                        NextNodeList[cur_node_dx] = static_cast<int>(node_new_dx);
                    }
                }else{ //这一步是假想中电脑走的，因此需要让分数尽量大，且应该修改alpha值
                    if (MethodTree[node_new_dx].Score > MethodTree[cur_node_dx].Score){
                        MethodTree[cur_node_dx].Score = MethodTree[node_new_dx].Score;
                        MethodTree[cur_node_dx].Alpha = MethodTree[node_new_dx].Score;
                        NextNodeList[cur_node_dx] = static_cast<int>(node_new_dx);
                    }
                }
            }else{
                if (MethodTree[cur_node_dx].Depth % 2 == 0){ //这一步是假想中电脑走的，因此需要让分数尽量大，且应该修改alpha值
                    if (MethodTree[node_new_dx].Score > MethodTree[cur_node_dx].Score){
                        MethodTree[cur_node_dx].Score = MethodTree[node_new_dx].Score;
                        MethodTree[cur_node_dx].Alpha = MethodTree[node_new_dx].Score;
                        NextNodeList[cur_node_dx] = static_cast<int>(node_new_dx);
                    }
                }else{ //这一步是假想中玩家走的，因此需要让分数尽量小，且应该修改beta值
                    if (MethodTree[node_new_dx].Score < MethodTree[cur_node_dx].Score){
                        MethodTree[cur_node_dx].Score = MethodTree[node_new_dx].Score;
                        MethodTree[cur_node_dx].Beta = MethodTree[node_new_dx].Score;
                        NextNodeList[cur_node_dx] = static_cast<int>(node_new_dx);
                    }
                }
            }
            //alpha-beta剪枝
            if (MethodTree[cur_node_dx].Alpha > MethodTree[cur_node_dx].Beta)
                return;
            if (MethodTree.size() >= MaxNodeNum / 2)
                return;
        }
    }
}

Point AI1Step::GetFinalRes(){
    if (NextNodeList[0] == -1){
        printf("NextNodeList[0] = -1.\n");
        return Point(-1, -1);
    }
    return MethodTree[NextNodeList[0]].Ope;
}
