# COSC 482: Homework 1-2: Word Search
# Kalyn Howes
# 2/21/22

import string

if __name__ == '__main__':

    # gather filename from user
    filename = input("Input text filename: ")

    # open file as f
    with open(filename) as f:
        words = []

        # reading each line
        for line in f:
            # reading each word
            for word in line.split():

                # remove punctuation
                newWord = word.translate(str.maketrans('', '', string.punctuation))
                # convert to lower case
                newWord = newWord.lower()

                # append each word to a list
                words.append(newWord)

    # test printing
    # print(words)

    # gather word to search from user
    searchWord = input("Input word to search for: ")
    # remove punctuation & make lowercase
    searchWord = searchWord.translate(str.maketrans('', '', string.punctuation))

    print('The number of total words in the text is:', len(words))
    print('The number of times that ' + searchWord + ' appears is:', words.count(searchWord.lower()))

    f.close()
