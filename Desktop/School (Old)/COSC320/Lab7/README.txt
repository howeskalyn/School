Kalyn Howes
3.25.21
Lab 7
README

From task 2: "Why does this hash function make sense? What does it do, logically? Add an explanation in your README."
The multiplcation method function makes sense because it uses three specific prime numbers that can be differed for any reason. This helps
with the uniqueness of the hash itself. The A variable must be between 0 and 1 while w is better to be smaller than the word size of the machine, 
and p is better to be smaller than w, but not too small. Once these variables are chosen, if the string is w bits long, A will be of form
A = s/2^w so s = A*2^w, then the string * A * 2^w gives a 2*w-bit value. This function is very interesting since it only takes p bits from
the final hash.

First, I included the multiplication method hash function we learned in class. This is the main hash function included in this program,
and is under the name 'hashin'. I wanted to just name it hash but I was worried about any overlap with C++ words. As for the two 'helper' functions, 
I have one to convert a string to 128-bit number in order to hash it more easily. There is also a convert function which displays a size_t
variable in hexidecimal form. 

As for the functions I have created, they are not very creative. 'Hashin2' takes in a string and stores it in a new string backwards. Once
this is complete, I use the multiplcation method and call the 'hashin' function from above. The hashed form of the string in 'hashin2' is the same
as the hexidecimal form of the 'hashin' method which I thought was a cool disovery. My other function, 'hashin3' separates the odd and
even indices of the input string and puts all of the even indices first, in order of index. Then, it is shifted down (bit-wise) by n - m.
In this case n is 2^197 and m is 11. This function is not case-sensitive however, meaning if there was an input of DOG and dog they would produce the same hash. 
I tried to limit the input by taking only the first 50 charatcers of the input string to be hashed. This is not efficient and doesn't really make sense
but I wasnt sure what else to do. This method would obviously cause many many collisions. 

Overall I dont think I am familiar enough with the idea of hashing to be super creative with my hash functions, but that will come with practice.
I need to address the collisions and figure out a way to deal with extremely long strings. 