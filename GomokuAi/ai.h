#include <vector>
#include <set>
#include <string.h>
#include "constants.h"

using namespace std;

struct Point
{
    int X;
    int Y;
    Point(const int& x, const int& y): X(x), Y(y){}
    bool operator < (const Point& p) const {
        if (this->Y * 15 + this->X < p.Y * 15 + p.X)
            return true;
        return false;
    }
    bool operator == (const Point& p) const {
        if (this->X == p.X && this->Y == p.Y)
            return true;
        return false;
    }
};

class Node
{
public:
    Node(int g_map[15][15], const Point& ope, const int& depth, const int& alpha, const int& beta, const bool& force_score, const bool& player_first): Depth(depth), Alpha(alpha), Beta(beta), Ope(ope), ForceScore(force_score), PlayerFirst(player_first){
        memcpy(GameMap, g_map, sizeof(int) * 15 * 15);
    }

    int CalcScore();  //计算这个节点的分数。对AI越有利则分数越高，反之分数越低
    set<Point> GetOpeList(); //获取可以操作的点的列表
    int Score;

    int GameMap[15][15]; //游戏内容。
    int Depth;
    int Alpha;
    int Beta;
    Point Ope;

private:
    int ForceScore;
    int PlayerFirst;
    int JudgeRes(); //判断游戏胜负
    void Judge4(uint64_t& ai_4_num, uint64_t& player_4_num); //判断玩家和电脑的四子的数目
    void Judge3D(uint64_t& ai_3d_num, uint64_t& player_3d_num); //判断玩家和电脑的活三的数目
};


class AI1Step
{
public:
    AI1Step(int init_map[15][15], int init_depth, bool player_first): PlayerFirst(player_first){
        Node node_init = Node(init_map, Point(-1, -1), init_depth, -INF, INF, false, PlayerFirst);
        MethodTree = {node_init}; // 策略树
        NextNodeList = {-1}; //每个节点的下一步节点列表。-1表示这个节点为最终节点
    }

    void Search(const uint64_t cur_node_dx, const uint64_t max_depth);
    Point GetFinalRes();

    uint64_t res;
    vector<Node> MethodTree;
private:
    const int PlayerFirst;
    vector<int> NextNodeList;
};
