Kalyn Howes
3.18.21
Lab6
README.txt

A make clean command is required prior to compiling Lab6.cpp.

(a) 
	I split my main function into two parts, one for the hiring algorithm and one for the timing of the different sorts. Instead of making two separate programs, I just commented out either section of the main to get the output I was focused on. For each part, there is a sum counter that is used to find the average (replacements or number of seconds) the algorithm used. For the second part with the sorting, I reused all of my old functions and the Heap struct I created back in Lab 3.

(b)
	The theoretical time complexity for Quicksort is O(n^2) in its worst case and O(nlogn) in its best. Randomized Quicksort should theoretically be the same since the only difference is randomly choosing the pivot position. Mergesort is O(nlogn) in all cases, as well as Heapsort. Generally, as the input size increases, so do the sorting times for all of the above. 
	The amount of time taken on an input of double the size will be greater than double the time due to exponentiation. Whether the algorithm has a time complexity of n^2 or nlogn, there is still exponential growth. 
	Since I experimented using randomly sorted arrays, the question of which algorithms are most/least impacted by the initial ordering is hard to see from just my data. Looking at the algorithms themselves, Quicksort has the best case when the partitions are evenly balanced, but the initial order of the elements matters less. The same goes for Randomized Quicksort except the pivots are chosen at random. Mergesort has a best case when the largest element of one sorted sub-array is smaller than the first element of its opposing sub-array for every merging step. This relies more on the initial ordering of the elements, but also the way it is split. Looking at past data from Heapsort, it seems arrays that were sorted and sorted backwards took less time than those which contained duplicates and were randomly generated. It seems Heapsort is the most impacted by the initial ordering of the array.
	
(c) 
	Since I had issues with my Quicksort testing, it is hard to tell. The Random Quicksort which theoretically has time complexity of O(n^2) in the worst case and O(nlogn) in its best, seems to follow more of the nlogn trend, but still looks even a bit slower than nlogn. The Merge and Heap sorts seem to be doing better than their theoretical complexities as well. 
	The average number of assistants hired over all of my data was 3.058. This includes data with runs from 10-30 and array sizes from 10-50. 

(d) 
	 Quicksort and Random Quicksort, the worst case running time should be O(n^2), for an array size of n. It seems Quicksort was having a rough time for me, so maybe it was doing close to the worst case? As for Merge and Heap, they did better than the worst case for all my data.

(e)
	Looking at my data, I found the linear trend lines of each sort. Quicksort has the largest slope while Mergesort had the smallest. However, looking at the graph I included in SortingTimes.pdf, we can see none of the times are linear. The Random Quicksort line looks like it would be between a log(n) and n*log(n). The Merge and Heap sorts look much closer to log(n) but is still increasing rather than going towards 0. As for Quicksort, since the data point with array size 110000 took so long to run I didn't find the time, it is hard to determine what trend it is going to follow. Thinking about it, I figure it is increase very very quickly which means it has a function with n^exp, where exp is a large number.

(f) 
	Instead of swapping each index with a random index, I could have swapped a random index with another random index. I also could have done it the other way by using a priority queue.

(g) 
	My main could definitely be more efficient in the way of not needing to comment out sections of code, but it made the most sense to me at the time. Also I probably should've included a class to store some of the functions since the main got full very quickly.