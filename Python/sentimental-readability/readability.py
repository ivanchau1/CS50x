import cs50

# receives text from user
text = cs50.get_string("Text: ")

letters = 0
sentences = 0
words = 0

for x in range(len(text)):
    # determines if character is letter in alphabet
    if text[x].isalpha():
        letters += 1
    # determines if it is end of sentence
    elif text[x] == "." or text[x] == "?" or text[x] == "!":
        sentences += 1
    # determines number of spaces
    elif text[x] == " ":
        words += 1

# adds an extra word as there is always a word after a space
words += 1

# determines average number of letters per 100 words
L = letters / words * 100
# determines average number of sentences per 100 words
S = sentences / words * 100
# determines Coleman-Liau index with the formula
ColemanIndex = 0.0588 * L - 0.296 * S - 15.8
ColemanIndex = round(ColemanIndex)

# determines grade level based on Coleman-Liau index
if ColemanIndex > 1 and ColemanIndex < 16:
    print("Grade", ColemanIndex)
elif ColemanIndex <= 1:
    print("Before Grade 1")
else:
    print("Grade 16+")
