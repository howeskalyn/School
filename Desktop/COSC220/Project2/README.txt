Kalyn Howes
12.8.2020

This project was created to simulate two Casino games: Poker and BlackJack. 
My main program is titled 'Casino', while every other file consists of classes to supplement my main. 

To start, I created a Card class which holds the number value, 'Num', on a Card and an array of characters called 'Pic' to hold the Card's suit in a Unicode picture format. This class also includes a Card constructor that sets the 'Num' and 'Pic' to 0, and a displayCard function that displays the Card in a neat form. The Card class also includes the Unicode for each suit's picture format.

The next class I created is the Deck. The Deck class includes a vector of Cards called 'deckOfCards' that hold the entire deck. I also have a variable for the top of the Deck to keep track of what Card should be drawn next. In this class, there is a constructor that creates a typical Deck of 52 Cards, a shuffleDeck function that randomly shuffles the Cards in the Deck, a printDeck function that will print the entire Deck in the proper format, and a GetCard function that returns the next Card in the Deck. 

Getting to actual gameplay, I created a Poker Class. This Poker class has one main function called 'playPoker' that runs through an entire game of Casino Poker. I also included a few functions in this class to support the playPoker function. The first is a sortHand function which sorts each Card in the Hand by numerical value from lowest to highest. This is used prior to finding the type of Hand the player has in the function 'handType'. The handType function tells the user what type of Poker Hand they ended up with and how much money they get based off their bet. This function starts by figuring out if the Hand is a Royal Straight Flush since it has the most conditions. Then, it sees if the Hand is a Straight Flush, a Four of a Kind, a Full House, a Flush, a Straight, a Three of a Kind, a Two Pair, or a High Card. This order id dependent on the number of conditions it takes to get the specific Hand (Royal Straight Flush is the highest, and the High Card is the lowest). I also included one more supplemental function called 'linearSearch' that searches a Hand for a specific numerical value Card and if it is found, the index is returned.

Finally, I created the BlackJack Class. This has the same format as the Poker Class, it just plays BlackJack instead. I have one variable in the BlackJack class called 'winningMoney' that keeps track of the Player's winnings. Other than that, I only have functions. The main function is the 'playBlackJack' function that runs through an entire game of Casino BlackJack. To support the main function, I also included a few supplemental functions including the cardSum and winnings functions. The 'cardSum' function adds up the numerical values of all the Cards in a Hand. Also, if the Hand includes an Ace, it asks the player/dealer if they would like the Ace to be worth 1 or 11 points towards the Hand sum. The last function called 'winnings' determines the amount of money the Player wins based on a few things: 
-if the player has BlackJack, they win 1.5x their bet
-if the player's sum is higher than the dealers but not a bust(over 21), they win their bet
-if the player's sum is less than the dealer's sum OR the player busts, they lose their money
-if player gets same as dealer has, player does not lose any money
-if dealer busts, every player wins twice their bet
This function tells the user what happened and how much reward money they get.

To run my program in a Linux terminal, all you must do is compile the makefile and run it. To do this you use the command 'make makefile' and then to run it you use './makefile' and it should run smoothly.

Thank you!












