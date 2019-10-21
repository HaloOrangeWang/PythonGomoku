class Gomoku:

    def __init__(self):
        self.g_map = [[0 for y in range(15)] for x in range(15)]  # 当前的棋盘
        self.cur_step = 0  # 步数

    def move_1step(self, input_by_window=False, pos_x=None, pos_y=None):
        """
        玩家落子
        :param input_by_window: 是否从图形界面输入
        :param pos_x: 从图形界面输入时，输入的x坐标为多少
        :param pos_y: 从图形界面输入时，输入的y坐标为多少
        """
        while True:
            try:
                if not input_by_window:
                    pos_x = int(input('x: '))  # 接受玩家的输入人
                    pos_y = int(input('y: '))
                if 0 <= pos_x <= 14 and 0 <= pos_y <= 14:  # 判断这个格子能否落子
                    if self.g_map[pos_x][pos_y] == 0:
                        self.g_map[pos_x][pos_y] = 1
                        self.cur_step += 1
                        return
            except ValueError:  # 玩家输入不正确的情况（例如输入了‘A’）
                continue

    def game_result(self, show=False):
        """判断游戏的结局。0为游戏进行中，1为玩家获胜，2为电脑获胜，3为平局"""
        # 1. 判断是否横向连续五子
        for x in range(11):
            for y in range(15):
                if self.g_map[x][y] == 1 and self.g_map[x + 1][y] == 1 and self.g_map[x + 2][y] == 1 and self.g_map[x + 3][y] == 1 and self.g_map[x + 4][y] == 1:
                    if show:
                        return 1, [(x0, y) for x0 in range(x, x + 5)]
                    else:
                        return 1
                if self.g_map[x][y] == 2 and self.g_map[x + 1][y] == 2 and self.g_map[x + 2][y] == 2 and self.g_map[x + 3][y] == 2 and self.g_map[x + 4][y] == 2:
                    if show:
                        return 2, [(x0, y) for x0 in range(x, x + 5)]
                    else:
                        return 2

        # 2. 判断是否纵向连续五子
        for x in range(15):
            for y in range(11):
                if self.g_map[x][y] == 1 and self.g_map[x][y + 1] == 1 and self.g_map[x][y + 2] == 1 and self.g_map[x][y + 3] == 1 and self.g_map[x][y + 4] == 1:
                    if show:
                        return 1, [(x, y0) for y0 in range(y, y + 5)]
                    else:
                        return 1
                if self.g_map[x][y] == 2 and self.g_map[x][y + 1] == 2 and self.g_map[x][y + 2] == 2 and self.g_map[x][y + 3] == 2 and self.g_map[x][y + 4] == 2:
                    if show:
                        return 2, [(x, y0) for y0 in range(y, y + 5)]
                    else:
                        return 2

        # 3. 判断是否有左上-右下的连续五子
        for x in range(11):
            for y in range(11):
                if self.g_map[x][y] == 1 and self.g_map[x + 1][y + 1] == 1 and self.g_map[x + 2][y + 2] == 1 and self.g_map[x + 3][y + 3] == 1 and self.g_map[x + 4][y + 4] == 1:
                    if show:
                        return 1, [(x + t, y + t) for t in range(5)]
                    else:
                        return 1
                if self.g_map[x][y] == 2 and self.g_map[x + 1][y + 1] == 2 and self.g_map[x + 2][y + 2] == 2 and self.g_map[x + 3][y + 3] == 2 and self.g_map[x + 4][y + 4] == 2:
                    if show:
                        return 2, [(x + t, y + t) for t in range(5)]
                    else:
                        return 2

        # 4. 判断是否有右上-左下的连续五子
        for x in range(11):
            for y in range(11):
                if self.g_map[x + 4][y] == 1 and self.g_map[x + 3][y + 1] == 1 and self.g_map[x + 2][y + 2] == 1 and self.g_map[x + 1][y + 3] == 1 and self.g_map[x][y + 4] == 1:
                    if show:
                        return 1, [(x + t, y + 4 - t) for t in range(5)]
                    else:
                        return 1
                if self.g_map[x + 4][y] == 2 and self.g_map[x + 3][y + 1] == 2 and self.g_map[x + 2][y + 2] == 2 and self.g_map[x + 1][y + 3] == 2 and self.g_map[x][y + 4] == 2:
                    if show:
                        return 2, [(x + t, y + 4 - t) for t in range(5)]
                    else:
                        return 2

        # 5. 判断是否为平局
        for x in range(15):
            for y in range(15):
                if self.g_map[x][y] == 0:  # 棋盘中还有剩余的格子，不能判断为平局
                    if show:
                        return 0, [(-1, -1)]
                    else:
                        return 0

        if show:
            return 3, [(-1, -1)]
        else:
            return 3

    def ai_move_1step(self):
        """电脑落子"""
        for x in range(15):
            for y in range(15):
                if self.g_map[x][y] == 0:
                    self.g_map[x][y] = 2
                    self.cur_step += 1
                    return

    def show(self, res):
        """显示游戏内容"""
        for y in range(15):
            for x in range(15):
                if self.g_map[x][y] == 0:
                    print('  ', end='')
                elif self.g_map[x][y] == 1:
                    print('〇', end='')
                elif self.g_map[x][y] == 2:
                    print('×', end='')

                if x != 14:
                    print('-', end='')
            print('\n', end='')
            for x in range(15):
                print('|  ', end='')
            print('\n', end='')

        if res == 1:
            print('玩家获胜!')
        elif res == 2:
            print('电脑获胜!')
        elif res == 3:
            print('平局!')

    def play(self):
        while True:
            self.move_1step()  # 玩家下一步
            res = self.game_result()  # 判断游戏结果
            if res != 0:  # 如果游戏结果为“已经结束”，则显示游戏内容，并退出主循环
                self.show(res)
                return
            self.ai_move_1step()  # 电脑下一步
            res = self.game_result()
            if res != 0:
                self.show(res)
                return
            self.show(0)  # 在游戏还没有结束的情况下，显示游戏内容，并继续下一轮循环
