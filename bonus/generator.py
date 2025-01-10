from random import *

additional_aircrafts_towers = []

for _ in range(500):
    X = randint(0, 1920)
    Y = randint(0, 1080)
    other_values = [randint(1000, 1600), randint(200, 700), randint(75, 95), randint(0, 20)]
    aircraft_line = f"A {X} {Y} {' '.join(map(str, other_values))}"
    additional_aircrafts_towers.append(aircraft_line)

for _ in range(5):
    X = randint(0, 1920)
    Y = randint(0, 1080)
    RADIUS = randint(1, 500)
    tower_line = f"T {X} {Y} {RADIUS}"
    additional_aircrafts_towers.append(tower_line)

output_50 = "\n".join(additional_aircrafts_towers)

print(output_50)
