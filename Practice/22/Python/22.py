#ошибочно
maze = [
    "####B######################",
    "# #       #   #      #    #",
    "# # # ###### #### ####### #",
    "# # # #       #   #       #",
    "#   # # ######### # ##### #",
    "# # # #   #       #     # #",
    "### ### ### ############# #",
    "# #   #     # #           #",
    "# # #   ####### ###########",
    "# # # #       # #         C",
    "# # ##### ### # # ####### #",
    "# # #     ### # #       # #",
    "#   ##### ### # ######### #",
    "######### ### #           #",
    "# ####### ### #############",
    "A           #   ###   #   #",
    "# ############# ### # # # #",
    "# ###       # # ### # # # #",
    "# ######### # # ### # # # F",
    "#       ### # #     # # # #",
    "# ######### # ##### # # # #",
    "# #######   #       #   # #",
    "# ####### ######### #######",
    "#         #########       #",
    "#######E############D######"
]

position = list(map(int, input().split()))

def BFS(maz):
    if maz in "QWERTYUIOPASDFGHJKLZXCVBNM":
        print(maz)
        return
    else:
        for i in range(-1, 2):
            for j in range(-1, 2):
                try:
                    if maze[len(maze) - position[0] - 1 + i][position[1] + j] != '#':
                        BFS(maze[len(maze) - position[0] - 1 + i][position[1] + j])
                    elif maze[len(maze) - position[0] - 1 + i][position[1] + j] == '@':
                        return
                except IndexError:
                    return
try:
    if maze[len(maze) - position[1] - 1][position[0]] == '#':
        print("Неверные координаты")
    else:
        r = len(maze)
        for i in range(r):
            maze.append(list(maze[i]))
            maze.pop(0)
        maze[len(maze) - position[1] - 1][position[0]] = '@'
        for i in range(len(maze)):
            print(''.join(maze[i]))
        # BFS(maze[len(maze) - position[1] - 1][position[0]])
except IndexError:
    print("Неверные координаты")