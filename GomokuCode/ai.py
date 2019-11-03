import numpy as np
import copy
import time


class Node:
    """AI搜索时的一个节点"""

    def __init__(self, game, ope, depth, alpha, beta, force_score, player_first):
        """
        创建一个minimax的节点
        :param game: 游戏内容。是Game类的一个对象
        :param ope: 这一步的操作是什么
        :param depth: 当前节点的深度
        :param alpha: 这个节点初始的alpha值
        :param beta: 这个节点初始的beta值
        :param force_score: 是否必须算出一个分数
        :param player_first: 是否玩家先出
        """
        self.game = game
        self.ope = ope
        self.depth = depth
        self.alpha = alpha
        self.beta = beta
        self.force_score = force_score
        self.player_first = player_first
        st = time.time()
        self.score = self.calc_score()
        ed = time.time()
        self.t = ed - st

    def calc_score(self):
        """计算这个节点的分数。对AI越有利则分数越高，反之分数越低"""

        # 1. 如果能够连成五子，则记为100分
        res = self.game.game_result()
        if res == 2:
            return 100
        elif res == 1:
            return -100

        # 2. 判断玩家和电脑的四子的数目（需要保证：不是已经被堵死的四子）
        ai_4_num = 0
        player_4_num = 0
        for x in range(11):
            for y in range(15):
                player_cnt = sum([self.game.g_map[x][y] == 1, self.game.g_map[x + 1][y] == 1, self.game.g_map[x + 2][y] == 1, self.game.g_map[x + 3][y] == 1, self.game.g_map[x + 4][y] == 1])
                ai_cnt = sum([self.game.g_map[x][y] == 2, self.game.g_map[x + 1][y] == 2, self.game.g_map[x + 2][y] == 2, self.game.g_map[x + 3][y] == 2, self.game.g_map[x + 4][y] == 2])
                if player_cnt == 4 and ai_cnt == 0:
                    player_4_num += 1
                if ai_cnt == 4 and player_cnt == 0:
                    ai_4_num += 1
        for x in range(15):
            for y in range(11):
                player_cnt = sum([self.game.g_map[x][y] == 1, self.game.g_map[x][y + 1] == 1, self.game.g_map[x][y + 2] == 1, self.game.g_map[x][y + 3] == 1, self.game.g_map[x][y + 4] == 1])
                ai_cnt = sum([self.game.g_map[x][y] == 2, self.game.g_map[x][y + 1] == 2, self.game.g_map[x][y + 2] == 2, self.game.g_map[x][y + 3] == 2, self.game.g_map[x][y + 4] == 2])
                if player_cnt == 4 and ai_cnt == 0:
                    player_4_num += 1
                if ai_cnt == 4 and player_cnt == 0:
                    ai_4_num += 1
        for x in range(11):
            for y in range(11):
                player_cnt = sum([self.game.g_map[x][y] == 1, self.game.g_map[x + 1][y + 1] == 1, self.game.g_map[x + 2][y + 2] == 1, self.game.g_map[x + 3][y + 3] == 1, self.game.g_map[x + 4][y + 4] == 1])
                ai_cnt = sum([self.game.g_map[x][y] == 2, self.game.g_map[x + 1][y + 1] == 2, self.game.g_map[x + 2][y + 2] == 2, self.game.g_map[x + 3][y + 3] == 2, self.game.g_map[x + 4][y + 4] == 2])
                if player_cnt == 4 and ai_cnt == 0:
                    player_4_num += 1
                if ai_cnt == 4 and player_cnt == 0:
                    ai_4_num += 1
        for x in range(11):
            for y in range(11):
                player_cnt = sum([self.game.g_map[x + 4][y] == 1, self.game.g_map[x + 3][y + 1] == 1, self.game.g_map[x + 2][y + 2] == 1, self.game.g_map[x + 1][y + 3] == 1, self.game.g_map[x][y + 4] == 1])
                ai_cnt = sum([self.game.g_map[x + 4][y] == 2, self.game.g_map[x + 3][y + 1] == 2, self.game.g_map[x + 2][y + 2] == 2, self.game.g_map[x + 1][y + 3] == 2, self.game.g_map[x][y + 4] == 2])
                if player_cnt == 4 and ai_cnt == 0:
                    player_4_num += 1
                if ai_cnt == 4 and player_cnt == 0:
                    ai_4_num += 1

        # 3. 如果能够连成活四，或连成双四，则记为90分
        if self.player_first:
            if self.depth % 2 == 0:  # 该轮到玩家出了
                if player_4_num >= 2:
                    return -90
                elif ai_4_num >= 2 and player_4_num == 0:
                    return 90
            else:  # 该轮到电脑出了
                if ai_4_num >= 2:
                    return 90
                elif player_4_num >= 2 and ai_4_num == 0:
                    return -90
        else:
            if self.depth % 2 == 0:  # 该轮到电脑出了
                if ai_4_num >= 2:
                    return 90
                elif player_4_num >= 2 and ai_4_num == 0:
                    return -90
            else:  # 该轮到玩家出了
                if player_4_num >= 2:
                    return -90
                elif ai_4_num >= 2 and player_4_num == 0:
                    return 90

        # 4.从这里开始，对于force_score为False的情况，分数记为±inf
        if self.force_score is False:
            if self.player_first:
                if self.depth % 2 == 0:  # 该轮到玩家出了
                    return np.inf
                else:  # 该轮到电脑出了
                    return -np.inf
            else:
                if self.depth % 2 == 0:  # 该轮到玩家出了
                    return -np.inf
                else:  # 该轮到电脑出了
                    return np.inf

        # 4. 判断玩家和电脑的活三的数目
        player_3d_num = 0
        ai_3d_num = 0
        # 4.1. xooox的形式
        for x in range(11):
            for y in range(15):
                if self.game.g_map[x][y] == 0 and self.game.g_map[x + 1][y] == 1 and self.game.g_map[x + 2][y] == 1 and self.game.g_map[x + 3][y] == 1 and self.game.g_map[x + 4][y] == 0:
                    player_3d_num += 1
                if self.game.g_map[x][y] == 0 and self.game.g_map[x + 1][y] == 2 and self.game.g_map[x + 2][y] == 2 and self.game.g_map[x + 3][y] == 2 and self.game.g_map[x + 4][y] == 0:
                    ai_3d_num += 1
        for x in range(15):
            for y in range(11):
                if self.game.g_map[x][y] == 0 and self.game.g_map[x][y + 1] == 1 and self.game.g_map[x][y + 2] == 1 and self.game.g_map[x][y + 3] == 1 and self.game.g_map[x][y + 4] == 0:
                    player_3d_num += 1
                if self.game.g_map[x][y] == 0 and self.game.g_map[x][y + 1] == 2 and self.game.g_map[x][y + 2] == 2 and self.game.g_map[x][y + 3] == 2 and self.game.g_map[x][y + 4] == 0:
                    ai_3d_num += 1
        for x in range(11):
            for y in range(11):
                if self.game.g_map[x][y] == 0 and self.game.g_map[x + 1][y + 1] == 1 and self.game.g_map[x + 2][y + 2] == 1 and self.game.g_map[x + 3][y + 3] == 1 and self.game.g_map[x + 4][y + 4] == 0:
                    player_3d_num += 1
                if self.game.g_map[x][y] == 0 and self.game.g_map[x + 1][y + 1] == 2 and self.game.g_map[x + 2][y + 2] == 2 and self.game.g_map[x + 3][y + 3] == 2 and self.game.g_map[x + 4][y + 4] == 0:
                    ai_3d_num += 1
        for x in range(11):
            for y in range(11):
                if self.game.g_map[x + 4][y] == 0 and self.game.g_map[x + 3][y + 1] == 1 and self.game.g_map[x + 2][y + 2] == 1 and self.game.g_map[x + 1][y + 3] == 1 and self.game.g_map[x][y + 4] == 0:
                    player_3d_num += 1
                if self.game.g_map[x + 4][y] == 0 and self.game.g_map[x + 3][y + 1] == 2 and self.game.g_map[x + 2][y + 2] == 2 and self.game.g_map[x + 1][y + 3] == 2 and self.game.g_map[x][y + 4] == 0:
                    ai_3d_num += 1
        # 4.2. xoxoox或xooxox的形式
        for x in range(10):
            for y in range(15):
                if self.game.g_map[x][y] == 0 and self.game.g_map[x + 1][y] == 1 and ((self.game.g_map[x + 2][y] == 1) ^ (self.game.g_map[x + 3][y] == 1)) and self.game.g_map[x + 4][y] == 1 and self.game.g_map[x + 5][y] == 0:
                    player_3d_num += 1
                if self.game.g_map[x][y] == 0 and self.game.g_map[x + 1][y] == 2 and ((self.game.g_map[x + 2][y] == 2) ^ (self.game.g_map[x + 3][y] == 2)) and self.game.g_map[x + 4][y] == 2 and self.game.g_map[x + 5][y] == 0:
                    ai_3d_num += 1
        for x in range(15):
            for y in range(10):
                if self.game.g_map[x][y] == 0 and self.game.g_map[x][y + 1] == 1 and ((self.game.g_map[x][y + 2] == 1) ^ (self.game.g_map[x][y + 3] == 1)) and self.game.g_map[x][y + 4] == 1 and self.game.g_map[x][y + 5] == 0:
                    player_3d_num += 1
                if self.game.g_map[x][y] == 0 and self.game.g_map[x][y + 1] == 2 and ((self.game.g_map[x][y + 2] == 2) ^ (self.game.g_map[x][y + 3] == 2)) and self.game.g_map[x][y + 4] == 2 and self.game.g_map[x][y + 5] == 0:
                    ai_3d_num += 1
        for x in range(10):
            for y in range(10):
                if self.game.g_map[x][y] == 0 and self.game.g_map[x + 1][y + 1] == 1 and ((self.game.g_map[x + 2][y + 2] == 1) ^ (self.game.g_map[x + 3][y + 3] == 1)) and self.game.g_map[x + 4][y + 4] == 1 and self.game.g_map[x + 5][y + 5] == 0:
                    player_3d_num += 1
                if self.game.g_map[x][y] == 0 and self.game.g_map[x + 1][y + 1] == 2 and ((self.game.g_map[x + 2][y + 2] == 2) ^ (self.game.g_map[x + 3][y + 3] == 2)) and self.game.g_map[x + 4][y + 4] == 2 and self.game.g_map[x + 5][y + 5] == 0:
                    ai_3d_num += 1
        for x in range(10):
            for y in range(10):
                if self.game.g_map[x + 5][y] == 0 and self.game.g_map[x + 4][y + 1] == 1 and ((self.game.g_map[x + 3][y + 2] == 1) ^ (self.game.g_map[x + 2][y + 3] == 1)) and self.game.g_map[x + 1][y + 4] == 1 and self.game.g_map[x][y + 5] == 0:
                    player_3d_num += 1
                if self.game.g_map[x + 5][y] == 0 and self.game.g_map[x + 4][y + 1] == 2 and ((self.game.g_map[x + 3][y + 2] == 2) ^ (self.game.g_map[x + 2][y + 3] == 2)) and self.game.g_map[x + 1][y + 4] == 2 and self.game.g_map[x][y + 5] == 0:
                    ai_3d_num += 1

        # 6. 如果能够连成四三，则记为80分
        if self.player_first:
            if self.depth % 2 == 0:  # 该轮到玩家出了
                if player_4_num and player_3d_num >= 1:
                    return -80
                elif ai_4_num and ai_3d_num >= 1:
                    return 80
            else:  # 该轮到电脑出了
                if ai_4_num and ai_3d_num >= 1:
                    return 80
                elif player_4_num and player_3d_num >= 1:
                    return -80
        else:
            if self.depth % 2 == 0:  # 该轮到电脑出了
                if ai_4_num and ai_3d_num >= 1:
                    return 80
                elif player_4_num and player_3d_num >= 1:
                    return -80
            else:  # 该轮到玩家出了
                if player_4_num and player_3d_num >= 1:
                    return -80
                elif ai_4_num and ai_3d_num >= 1:
                    return 80

        # 7. 如果能够连成四子，则记为70分
        if self.player_first:
            if self.depth % 2 == 0:  # 该轮到玩家出了
                if player_4_num:
                    return -70
                elif ai_4_num:
                    return 70
            else:  # 该轮到电脑出了
                if ai_4_num:
                    return 70
                elif player_4_num:
                    return -70
        else:
            if self.depth % 2 == 0:  # 该轮到电脑出了
                if ai_4_num:
                    return 70
                elif player_4_num:
                    return -70
            else:  # 该轮到玩家出了
                if player_4_num:
                    return -70
                elif ai_4_num:
                    return 70

        # 8. 如果能够连成双三，则记为60分
        if self.player_first:
            if self.depth % 2 == 0:  # 该轮到玩家出了
                if player_3d_num >= 2:
                    return -60
                elif ai_3d_num >= 2:
                    return 60
            else:  # 该轮到电脑出了
                if ai_3d_num >= 2:
                    return 60
                elif player_3d_num >= 2:
                    return -60
        else:
            if self.depth % 2 == 0:  # 该轮到电脑出了
                if ai_3d_num >= 2:
                    return 60
                elif player_3d_num >= 2:
                    return -60
            else:  # 该轮到玩家出了
                if player_3d_num >= 2:
                    return -60
                elif ai_3d_num >= 2:
                    return 60

        # 9. 如果能够连成单活三，则记为50分
        if self.player_first:
            if self.depth % 2 == 0:  # 该轮到玩家出了
                if player_3d_num:
                    return -50
                elif ai_3d_num:
                    return 50
            else:  # 该轮到电脑出了
                if ai_3d_num:
                    return 50
                elif player_3d_num:
                    return -50
        else:
            if self.depth % 2 == 0:  # 该轮到电脑出了
                if ai_3d_num:
                    return 50
                elif player_3d_num:
                    return -50
            else:  # 该轮到玩家出了
                if player_3d_num:
                    return -50
                elif ai_3d_num:
                    return 50

        # 10. 其他情况。按照棋子的分布来计分（根据这个棋子距离棋盘中心的距离，以及这个棋子周围8格棋子的个数来评分）
        score_by_num_around = [0, 1, 20, 30, 26, 24, 22, 20, 18, 16, 15]
        player_score_num = 0
        ai_score_num = 0
        player_cnt = 0
        ai_cnt = 0
        for x in range(15):
            for y in range(15):
                if self.game.g_map[x][y] == 1:
                    around_cnt = 0
                    for x0 in range(x - 1, x + 2):
                        for y0 in range(y - 1, y + 2):
                            if 0 <= x0 <= 14 and 0 <= y0 <= 14 and self.game.g_map[x0][y0] != 0:
                                around_cnt += 1
                    player_score_num += score_by_num_around[around_cnt] - abs(x - 7) - abs(y - 7)
                    player_cnt += 1
                if self.game.g_map[x][y] == 2:
                    around_cnt = 0
                    for x0 in range(x - 1, x + 2):
                        for y0 in range(y - 1, y + 2):
                            if 0 <= x0 <= 14 and 0 <= y0 <= 14 and self.game.g_map[x0][y0] != 0:
                                around_cnt += 1
                    ai_score_num += score_by_num_around[around_cnt] - abs(x - 7) - abs(y - 7)
                    ai_cnt += 1
        if ai_cnt == 0 or player_cnt == 0:
            return 0
        score = ai_score_num / ai_cnt - player_score_num / player_cnt
        return score


class AI1Step:

    max_node_num = 100000  # 最大允许的节点数量（避免内存占用过多）

    def __init__(self, init_game, init_depth, player_first):
        """
        决定AI这一步走什么地方
        :param init_game: 初始的游戏地图
        :param init_depth: 初始的深度
        :param player_first: 玩家是否先出
        """
        node_init = Node(copy.deepcopy(init_game), None, init_depth, -np.inf, np.inf, False, player_first)  # 根节点
        node_init.score = -np.inf
        self.player_first = player_first
        self.method_tree = [node_init]  # 策略数
        self.next_node_dx_list = [-1]  # 每个节点的下一步节点列表。-1表示这个节点为最终节点
        self.child_node_dx_list = [[]]  # 每个节点的子节点列表
        self.ope_hist_list = []  # 纪录此前遍历过的操作列表
        self.t = 0

    def search(self, cur_node_dx, ope_hist, max_depth):
        """
        按照minimax和alpha-beta剪枝的方法搜索一个根节点下的最优结果。
        :param cur_node_dx: 当前节点的索引值
        :param ope_hist: 假象的历史状态列表
        :param max_depth: 最大允许的深度
        """
        # 1.首先确认什么地方可以落子。落子的条件是：这个格子必须为空，周围8格内必须有至少一个棋子
        ope_list = set()
        for x in range(15):
            for y in range(15):
                if self.method_tree[cur_node_dx].game.g_map[x][y] != 0:
                    for x0 in range(x - 1, x + 2):
                        for y0 in range(y - 1, y + 2):
                            if 0 <= x0 <= 14 and 0 <= y0 <= 14 and (x0, y0) not in ope_list:
                                if self.method_tree[cur_node_dx].game.g_map[x0][y0] == 0:
                                    ope_list.add((x0, y0))
        # 2. 然后对每一个可以落子的格子进行搜索
        for cell in ope_list:
            # 2.1 创建一个子节点，并计算这个子节点的分数
            i_game = copy.deepcopy(self.method_tree[cur_node_dx].game)
            if self.player_first:
                if self.method_tree[cur_node_dx].depth % 2 == 0:  # 轮到玩家出
                    i_game.g_map[cell[0]][cell[1]] = 1
                else:  # 轮到电脑出
                    i_game.g_map[cell[0]][cell[1]] = 2
            else:
                if self.method_tree[cur_node_dx].depth % 2 == 0:  # 轮到电脑出
                    i_game.g_map[cell[0]][cell[1]] = 1
                else:  # 轮到玩家出
                    i_game.g_map[cell[0]][cell[1]] = 2
            if max_depth >= 2 and len(ope_list) >= 2:  # 对于非最终层的节点，不急于立即算出分数
                node_new = Node(i_game, cell, self.method_tree[cur_node_dx].depth + 1, self.method_tree[cur_node_dx].alpha, self.method_tree[cur_node_dx].beta, False, self.player_first)
            else:
                node_new = Node(i_game, cell, self.method_tree[cur_node_dx].depth + 1, self.method_tree[cur_node_dx].alpha, self.method_tree[cur_node_dx].beta, True, self.player_first)
            self.t += node_new.t
            self.method_tree.append(node_new)  # 把这个节点插入到搜索树中
            node_new_dx = len(self.method_tree) - 1
            self.child_node_dx_list.append([])
            self.child_node_dx_list[cur_node_dx].append(node_new_dx)  # 将这个新节点记录为当前节点的子节点
            self.next_node_dx_list.append(-1)  # 记录每个节点下一步的动作
            # ope_hist_new = copy.deepcopy(ope_hist)  # 记录假象的历史状态列表
            # ope_hist_new[0].add(cell[0])
            # ope_hist_new[1].add(cell[1])
            # self.ope_hist_list.append(ope_hist_new)
            if len(self.method_tree) >= self.max_node_num:  # 为保护内存，搜索树的节点数目不能太多
                raise ValueError('Method Tree太大了')

            # 2.2. 根据子节点的情况，进行父节点的后续操作
            if -np.inf < self.method_tree[node_new_dx].score < np.inf:
                # 子节点有具体分数的情况下，就不用再进行更深层的迭代了
                if self.player_first:
                    if self.method_tree[cur_node_dx].depth % 2 == 0:  # 这一步是假想中玩家走的，因此需要让分数尽量小，且应该修改beta值
                        if self.method_tree[node_new_dx].score < self.method_tree[cur_node_dx].score:
                            self.method_tree[cur_node_dx].score = self.method_tree[node_new_dx].score
                            self.method_tree[cur_node_dx].beta = self.method_tree[node_new_dx].score
                            self.next_node_dx_list[cur_node_dx] = node_new_dx
                    else:  # 这一步是假想中电脑走的，因此需要让分数尽量大，且应该修改alpha值
                        if self.method_tree[node_new_dx].score > self.method_tree[cur_node_dx].score:
                            self.method_tree[cur_node_dx].score = self.method_tree[node_new_dx].score
                            self.method_tree[cur_node_dx].alpha = self.method_tree[node_new_dx].score
                            self.next_node_dx_list[cur_node_dx] = node_new_dx
                else:
                    if self.method_tree[cur_node_dx].depth % 2 == 0:  # 这一步是假想中电脑走的，因此需要让分数尽量大，且应该修改alpha值
                        if self.method_tree[node_new_dx].score > self.method_tree[cur_node_dx].score:
                            self.method_tree[cur_node_dx].score = self.method_tree[node_new_dx].score
                            self.method_tree[cur_node_dx].alpha = self.method_tree[node_new_dx].score
                            self.next_node_dx_list[cur_node_dx] = node_new_dx
                    else:  # 这一步是假想中玩家走的，因此需要让分数尽量小，且应该修改beta值
                        if self.method_tree[node_new_dx].score < self.method_tree[cur_node_dx].score:
                            self.method_tree[cur_node_dx].score = self.method_tree[node_new_dx].score
                            self.method_tree[cur_node_dx].beta = self.method_tree[node_new_dx].score
                            self.next_node_dx_list[cur_node_dx] = node_new_dx
            else:
                # 子节点还没有具体分数的情况下，应该以这个子节点为下一层的根节点，进行递归，之后再进行计算
                if max_depth >= 2:
                    self.search(node_new_dx, ope_hist, max_depth - 1)
                # 根据递归后计算的结果，计算这个节点的分数
                if self.player_first:
                    if self.method_tree[cur_node_dx].depth % 2 == 0:  # 这一步是假想中玩家走的，因此需要让分数尽量小，且应该修改beta值
                        if self.method_tree[node_new_dx].score < self.method_tree[cur_node_dx].score:
                            self.method_tree[cur_node_dx].score = self.method_tree[node_new_dx].score
                            self.method_tree[cur_node_dx].beta = self.method_tree[node_new_dx].score
                            self.next_node_dx_list[cur_node_dx] = node_new_dx
                    else:  # 这一步是假想中电脑走的，因此需要让分数尽量大，且应该修改alpha值
                        if self.method_tree[node_new_dx].score > self.method_tree[cur_node_dx].score:
                            self.method_tree[cur_node_dx].score = self.method_tree[node_new_dx].score
                            self.method_tree[cur_node_dx].alpha = self.method_tree[node_new_dx].score
                            self.next_node_dx_list[cur_node_dx] = node_new_dx
                else:
                    if self.method_tree[cur_node_dx].depth % 2 == 0:  # 这一步是假想中电脑走的，因此需要让分数尽量大，且应该修改alpha值
                        if self.method_tree[node_new_dx].score > self.method_tree[cur_node_dx].score:
                            self.method_tree[cur_node_dx].score = self.method_tree[node_new_dx].score
                            self.method_tree[cur_node_dx].alpha = self.method_tree[node_new_dx].score
                            self.next_node_dx_list[cur_node_dx] = node_new_dx
                    else:  # 这一步是假想中玩家走的，因此需要让分数尽量小，且应该修改beta值
                        if self.method_tree[node_new_dx].score < self.method_tree[cur_node_dx].score:
                            self.method_tree[cur_node_dx].score = self.method_tree[node_new_dx].score
                            self.method_tree[cur_node_dx].beta = self.method_tree[node_new_dx].score
                            self.next_node_dx_list[cur_node_dx] = node_new_dx
                if self.method_tree[cur_node_dx].alpha > self.method_tree[cur_node_dx].beta:  # alpha-beta剪枝
                    return
