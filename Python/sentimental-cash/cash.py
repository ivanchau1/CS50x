import cs50

change = -1
# receives user input of change
while change < 0:
    change = cs50.get_float("Change owed: ")

# removes decimal
change = change * 100

# determines number of quarters
quartersNum = change // 25
change = change % 25

# determines number of dimes
dimesNum = change // 10
change = change % 10

# determines number of nickels
nickelsNum = change // 5
change = change % 5

# determines number of pennies
penniesNum = change // 1

# totals all the coins
totalCoins = int(quartersNum + dimesNum + nickelsNum + penniesNum)

# prints number of coins
print(totalCoins)
