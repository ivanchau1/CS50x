import cs50

height = 0
xAxis = 1
# receives user requested height
while height < 1 or height > 8:
    height = cs50.get_int("Height: ")

while True:
    # prints the space in alignment to the right
    for x in range(height - 1):
        print(" ", end="")
    # decreases the amount of spaces through each line
    height -= 1

    # prints the "#" from the right increasing towards the left
    for y in range(xAxis):
        print("#", end="")
    # increases the number of "#" through each line
    xAxis += 1

    print()

    # stops running the loop once complete
    if height == 0:
        break
