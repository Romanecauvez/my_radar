# Generate 50 additional aircraft lines with random X and Y coordinates
from random import *

additional_aircrafts = []

for _ in range(50):

    X = random.randint(0, 1920)

    Y = random.randint(0, 1080)

    other_values = [random.randint(1000, 1600), random.randint(200, 700), random.randint(75, 95), random.randint(20, 50)]

    aircraft_line = f"A {X} {Y} {' '.join(map(str, other_values))}"

    additional_aircrafts.append(aircraft_line)

# Join the results into a formatted text block

output_50 = "\n".join(additional_aircrafts)

output_50