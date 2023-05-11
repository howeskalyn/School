Kalyn Howes
4.11.21
Project2 - README


	Starting in the main, the program takes in two args. This allows the user to open a specific file while they run the program. From here, every word in the file is loaded into an instance of the Dictionary class. The Dictionary class holds an array of linked lists (which is another class) in order to have a hash table structure. A few statistics about the hash table are given prior to the user input.
	Once every word from the file is hashed and in the table, the user is prompted to enter some text. In order to get the best results, the program makes every word of the file uppercase prior to inserting it into the Dictionary. Because of this, the user input is also changed to all caps in order to make the spell checker case insensitive. The user input is also removed of its punctuation. 
	Then, going through each word in the input string, the word is searched for in the dictionary. If it is not found the word is added to the misspelled list and the word is printed in red. 
	The largest section of the program starts when 'edits' is called on the misspelled words. This function, located in the LinkedList class, finds every possible suggestion/correction to the misspelled words and prints them to the user. These suggestions are determined by being within one or two edit distances from the misspelled word. This means any word that has one different character, one added character, one removed character, or two adjacent swapped characters, from the misspelled word will be given as a one edit-distance suggestion. Then, any words with the same characteristics from those already suggested will be given as two edit-distances words. The 'edits' function calls four other functions, one for each characteristic of the edit-distance.
	Once again some statistics are printed to the user about how many misspelled words they had, the total number of suggestions, and the time taken to find the suggestions.



	Specifically looking at the timing of the suggestion creating process, the runtime can increase very quickly as the number of words, number of misspelled words, and the size of the words increase. This is because the program first runs through each misspelled word, so the more mistakes made the longer it will be to generate suggestions. Also, each misspelled word is brought through four different functions for the edit-distances. 
	In these functions, every single possible combination of letters (that fit the characteristic) are created. Then they are searched for in the Dictionary to determine whether or not they are a valid suggestion. This process in itself obviously takes a lot of time, and will increase depending on the length of the word. From here, if there are a lot of one-edit distance suggestions, there will be at least twice as many two edit-distances words. This can significantly increase the time it takes to find all the suggestions. 

	

	For my has function, I used the multiplication method. The multiplication method uses three specific prime numbers that can be differed for any reason. This helps with the uniqueness of the hash itself. The A variable must be between 0 and 1 while w is better to be smaller than the word size of the machine, and p is better to be smaller than w, but not too small. Once these variables are chosen, if the string is w bits long, A will be of form A = s/2^w so s = A*2^w, then the string * A * 2^w gives a 2*w-bit value. This function is very interesting since it only takes p bits from the final hash.



	As for the efficiency of my program, it seems slow. This makes sense based on the way it is structured, but I feel it could be improved a lot. Also, I could not get the Dictionary destructor to work properly so it is commented out at the moment. This is obviously not a good idea however I was not sure how to fix it. Also just something small, but when there are more than 1 misspelled words, it suggests words for the last one first because my LinkedList insert function is a putFront!


	BONUS: I added an option to add the misspelled word to the Dictionary, but I did not do the part that asks if you'd like to replace the misspelled word with a suggestion. 
	