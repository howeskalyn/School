# COSC 482: Homework 1-1: 3n+1 Sequence
# Kalyn Howes
# 2/21/22

# returns the next number in the '3n + 1' sequence
def nifty(n):
    newnum = 0
    # if even, new number is previous divided by 2
    if(n % 2 == 0):
        newnum = n / 2
    # if odd, new number is the previous times 3 + 1
    else:
        newnum = (3 * n) + 1

    return newnum

# main
if __name__ == '__main__':
    valid = False
    n = 0

    # gather starting number from user
    while(valid == False):
        n = int(input("Enter an integer between 2 and 1000000: "))
        if (n < 2 or n > 1000000):
            print("Invalid Input.")
            valid = False
        else:
            valid = True

    sequence = [] # append each new number to the list
    sequence.append(n) # add starting number first

    # call nifty in a loop until value 1 is reached in the sequence
    newval = n
    while (newval != 1):
        newval = nifty(n)
        #print(newval)
        sequence.append(int(newval))
        n = newval

    # print final sequence
    print("Sequence: ", sequence)
    print("Number of integers in list = ", len(sequence))