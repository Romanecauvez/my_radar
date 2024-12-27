from random import *

additional_aircrafts = []

for _ in range(500):
    X = randint(0, 1920)
    Y = randint(0, 1080)
    other_values = [randint(1000, 1600), randint(200, 700), randint(75, 95), randint(20, 50)]
    aircraft_line = f"A {X} {Y} {' '.join(map(str, other_values))}"
    additional_aircrafts.append(aircraft_line)

output_50 = "\n".join(additional_aircrafts)

print(output_50)
