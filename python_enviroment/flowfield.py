import pygame as pg

WIDTH = 1280
HEIGHT = 1280

GRID_COLS = 25
GRID_ROWS = 25
MAX_COST = 10000


class TileWorld:
    def __init__(self, row, col) -> None:
        self.row, self.col = row, col
        self.is_walkable = True

class TileFlowField:
    def __init__(self, row, col) -> None:
        self.row, self.col = row, col
        self.is_walkable = True
        self.cost= MAX_COST

    def __str__(self) -> str:
        return f"walkable: {self.is_walkable}, cost: {self.cost}"


def draw_grid(screen) -> None:
    for i in range(GRID_COLS):
            pg.draw.line(screen, "white", (i*WIDTH/GRID_COLS, 0), (i*WIDTH/GRID_COLS, WIDTH))
    for i in range(GRID_ROWS):
            pg.draw.line(screen, "white", (0, i*HEIGHT/GRID_ROWS), (WIDTH, i*HEIGHT/GRID_ROWS))

def init_world_tiles() -> list[list[TileWorld]]:
    world_tiles = [[TileWorld(row, col) for col in range(GRID_COLS)] for row in range(GRID_ROWS)]
    return world_tiles

def init_flowfield_tiles(world_tiles) -> list[list[TileFlowField]]:
    flowfield_tiles = [[TileFlowField(row, col) for col in range(GRID_COLS)] for row in range(GRID_ROWS)]
    for col in range(GRID_COLS):
        for row in range(GRID_ROWS):
            flowfield_tiles[row][col].is_walkable = world_tiles[row][col].is_walkable
    return flowfield_tiles

def click_return(event, world_tiles):
    x, y = event.pos
    cell_col = x * GRID_COLS // WIDTH
    cell_row = y * GRID_ROWS // HEIGHT
    cell_col = max(0, min(cell_col, GRID_COLS - 1))
    cell_row = max(0, min(cell_row, GRID_ROWS - 1))
    target = world_tiles[cell_row][cell_col]
    return target

def generate_flow_field(target, flowfield_tiles):
    # Reset all costs
    for row in range(GRID_ROWS):
        for col in range(GRID_COLS):
            flowfield_tiles[row][col].cost = MAX_COST
    target.cost = 0

    queue = [target]

    cardinal_dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # up, down, left, right
    diagonal_dirs = [(-1, -1), (-1, 1), (1, -1), (1, 1)]  # diagonals

    while queue:
        current = queue.pop(0)

        for dr, dc in cardinal_dirs:
            new_row = current.row + dr
            new_col = current.col + dc


            if 0 <= new_row < GRID_ROWS and 0 <= new_col < GRID_COLS:
                neighbor = flowfield_tiles[new_row][new_col]

                if neighbor.is_walkable:
                    new_cost = current.cost + 10
                    if new_cost < neighbor.cost:
                        neighbor.cost = new_cost
                        queue.append(neighbor)

        for dr, dc in diagonal_dirs:
            new_row = current.row + dr
            new_col = current.col + dc

            if 0 <= new_row < GRID_ROWS and 0 <= new_col < GRID_COLS:
                neighbor = flowfield_tiles[new_row][new_col]

                if neighbor.is_walkable:
                    new_cost = current.cost + 14
                    if new_cost < neighbor.cost:
                        neighbor.cost = new_cost
                        queue.append(neighbor)

def find_lowest_cost_neighbor(current_tile, flowfield_tiles):
    dir = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1, 1), (1, -1), (1, 1)]
    best_neighbor = None
    lowest_cost = current_tile.cost 

    for dr, dc in dir:
        new_row = current_tile.row + dr
        new_col = current_tile.col + dc
        if 0 <= new_row < GRID_ROWS and 0 <= new_col < GRID_COLS:
            neighbor = flowfield_tiles[new_row][new_col]
            if neighbor.cost < lowest_cost:
                lowest_cost = neighbor.cost
                best_neighbor = neighbor

    return best_neighbor


def draw_costs(screen, flowfield_tiles):
    font = pg.font.Font(None, 36)
    cell_width = WIDTH // GRID_COLS
    cell_height = HEIGHT // GRID_ROWS

    for row in range(GRID_ROWS):
        for col in range(GRID_COLS):
            tile = flowfield_tiles[row][col]
            if tile.cost < MAX_COST:
                text = font.render(str(tile.cost), True, "yellow")
                x = col * cell_width + cell_width // 2 - text.get_width() // 2
                y = row * cell_height + cell_height // 2 - text.get_height() // 2
                screen.blit(text, (x, y))


def draw_flow(screen, flowfield_tiles):
    for row in range(GRID_ROWS):
        for col in range(GRID_COLS):
            current_tile = flowfield_tiles[row][col]
            best_neighbor = find_lowest_cost_neighbor(current_tile, flowfield_tiles)
            if best_neighbor:
                dx = best_neighbor.col - current_tile.col
                dy = best_neighbor.row - current_tile.row
                
                # Use exact pixel mapping to fill entire screen
                start_x = col * WIDTH // GRID_COLS + (WIDTH // GRID_COLS) // 2
                start_y = row * HEIGHT // GRID_ROWS + (HEIGHT // GRID_ROWS) // 2
                end_x = start_x + dx * (WIDTH // GRID_COLS) * 0.3
                end_y = start_y + dy * (HEIGHT // GRID_ROWS) * 0.3
                
                pg.draw.line(screen, "yellow", (start_x, start_y), (end_x, end_y), 2)



def main() -> None:
    pg.init()
    screen = pg.display.set_mode((WIDTH, HEIGHT))
    clock = pg.time.Clock()
    running = True
    target = None

    world_tiles = init_world_tiles()
    flowfield1 = init_flowfield_tiles(world_tiles)

    while running:
        for event in pg.event.get():
            if event.type == pg.QUIT:
                running = False
            if event.type == pg.MOUSEBUTTONDOWN:
                target = click_return(event, world_tiles)

        screen.fill("black")

        if target != None:
            generate_flow_field(target, flowfield1)
            # draw_costs(screen, flowfiled_tile1)
            draw_flow(screen, flowfield1)
        draw_grid(screen)

        pg.display.flip()

        clock.tick(60)  # limits FPS to 60

    pg.quit()


if __name__ == "__main__":
    main()
