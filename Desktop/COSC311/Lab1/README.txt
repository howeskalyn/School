README
Kalyn Howes
COSC311 - Lab1
9.10.21

_____________________________________________________________________________________

My code is very C++-esque with the use of nested for loops, but it works! I used the 
ideas from class for my who_covered subroutine, but used my own ideas for the shared_songs subroutine. Each cell must be run for the ones under to work because I have globally defined variables and 1 globally defined subroutine, the tuple sort. I should have created subroutines for finding the id of a song or artist from their name and voice-versa since I ended up using it more than once. I also should have included more overlap between artists & songs so the output was more interesting but I couldn't bring myself to connect Drake to a Greta Van Fleet song.
_____________________________________________________________________________________

What style of song is “Simple Twist of Fate”? Does it have a style or does it
“defy genre”?
	You could answer this question by taking into account whether the artist is male or female, the instruments used, the genre etc. All of these could be included in the keywords section. It could be visualized by using the methods below.

Each song genre could have a color, but that is somewhat restricting if the song can be described by more than one genre. Say we have a scatterplot with the x-axis as the artist/song and the y-axis as the genre. If we were looking for pop artists, for example, we could find them all very easily this way. You could use a bar graph for this data and separate the x-axis by genre, but it would only leave the viewer with the frequency of each genre, not an explanation of songs/artists in that genre. Same goes for a pie chart, but you could see which genre is most popular of the data set.

I included an image of a possible scatterplot of this data, however I don't feel it better visualizes the data than just a chart with genres at the top and artists/songs in the columns. This way an artist or song could be placed in more than one column as well. On the same page is an image of this chart as well as a typical bar and pie graph. 

Python could easily automate my ideas with the use of matplotlibs various plotting methods like bar, pie, line, scatter, etc. Pandas could also put the genres and artists/songs in a nice chart like the image I have included.

You could easily quantify the data by assigning each genre to a number. There could even be some sort of scale that gives the artist/song a certain number depending on how much its influenced by rock, pop, both, neither, etc. 