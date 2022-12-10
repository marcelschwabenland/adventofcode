class Knot:

    def __init__(self) -> None:
        self.x = 0
        self.y = 0

    def __repr__(self) -> str:
        return f"({self.x}, {self.y})"

    def position(self) -> tuple[int]:
        return (self.x, self.y)


class Rope:

    def __init__(self, n_knots: int) -> None:
        if n_knots < 2: raise ValueError('A rope must have at least two knots')
        self.segments = [Knot() for k in range(n_knots)]
        self.head = self.segments[0]
        self.tail = self.segments[-1]

    def __repr__(self) -> str:
        return str(self.segments)

    def move_head(self, x: int, y: int) -> None:
        self.step(self.head, x, y)
        for s in range(1, len(self.segments)):
            self.follow(self.segments[s - 1], self.segments[s])

    def step(self, knot: Knot, x: int, y: int) -> None:
        knot.x += x
        knot.y += y

    def knots_touching(self, x: int, y: int) -> bool:
        return abs(x) <= 1 and abs(y) <= 1

    def follow(self, lead: Knot, knot: Knot) -> None:
        diff_x = lead.x - knot.x
        diff_y = lead.y - knot.y
        if self.knots_touching(diff_x, diff_y):
            pass  # don't move if knots are touching
        elif diff_x == 0:  # vertical move
            self.step(knot, 0, diff_y // abs(diff_y))
        elif diff_y == 0:  # horizontal move
            self.step(knot, diff_x // abs(diff_x), 0)
        else:  # move diagonally
            self.step(knot, diff_x // abs(diff_x), diff_y // abs(diff_y))


with open('C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\09\\input.txt',
          encoding='UTF-8') as f:
    instructions = f.read().splitlines()


def solve(rope: Rope) -> None:
    move = {'R': (1, 0), 'L': (-1, 0), 'U': (0, 1), 'D': (0, -1)}
    unique_tail_pos = set()
    for line in instructions:
        direction, steps = line.split()
        for _ in range(int(steps)):
            rope.move_head(*move[direction])
            unique_tail_pos.add(rope.tail.position())
            #print(rope)
    print(len(unique_tail_pos))


part1 = Rope(2)
solve(part1)

part2 = Rope(10)
solve(part2)