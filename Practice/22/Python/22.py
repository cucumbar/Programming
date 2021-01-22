labyrinth = [
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
located = []
outs = []
def BFS(x_0, y_0):
    if y_0 < 0 or x_0 < 0 or x_0 >= len(labyrinth[0]) or y_0 >= len(labyrinth) or labyrinth[y_0][x_0] == "#":
        return
    if (x_0, y_0) in located:
        return
    located.append((x_0, y_0))
    if labyrinth[y_0][x_0] != " " and labyrinth[y_0][x_0] not in outs:
        outs.append(labyrinth[y_0][x_0])
    BFS(x_0, y_0+1)
    BFS(x_0, y_0-1)
    BFS(x_0+1, y_0)
    BFS(x_0-1, y_0)
x_0, y_0 = map(int, input().split())
BFS(x_0, y_0)
if y_0 < 0 or x_0 < 0 or x_0 >= len(labyrinth[0]) or y_0 >= len(labyrinth) or labyrinth[y_0][x_0] == "#":
    print("Неверные координаты")
else:
    if (len(outs) == 0):
        print("Выходов нет")
    else:
        for i in reversed(outs):
            print(i, end=' ')
        print()