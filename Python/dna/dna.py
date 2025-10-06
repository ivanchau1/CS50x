import csv
import sys


def main():
    # Check for command-line usage
    # Checks for required number of inputted files
    if len(sys.argv) != 3:
        print("Usuage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Checks for valid filenames
    if not ("csv" in sys.argv[1] and "txt" in sys.argv[2]):
        print("Usuage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    database = []

    # Stores data from csv file into a variable
    with open(sys.argv[1], "r") as databaseFile:
        reader = csv.DictReader(databaseFile)
        for row in reader:
            database.append(row)

    # Obtains subsequences of DNA from variable
    subsequences = list(database[0])
    subsequences.pop(0)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as DNAFile:
        DNA = DNAFile.read()

    # Find longest match of each STR in DNA sequence
    result = {}

    for subsequence in subsequences:
        result[subsequence] = longest_match(DNA, subsequence)

    # Check database for matching profiles
    for person in database:
        matches = 0
        for subsequence in subsequences:
            if int(person[subsequence]) == result[subsequence]:
                matches += 1

        # Checks if all subsequences matches
        if matches == len(subsequences):
            print(person["name"])
            sys.exit(1)

    print("No Match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
