Kalyn Howes
Lab 1
2.4.21

	Theoretically, the Bubble Sort has a time complexity of O(n) in its best case and O(n^2) in its worst case. The Insertion Sort has a time complexity of O(n) in its best case and O(n^2) in its worst as well. The Selection Sort has a time complexity of O(n^2) all around.

	The timing generally increased as the number of elements in the array increased. However, for the arrays that were already sorted, the Insertion sort had a much smaller increase in time as the sizes grew. The data I collected seems to support the theoretical time complexities for each sort, but of course array size is going to be a factor. Can you use the data collected to rectify this with the theoretical time complexity?

	A word document is included within this Zip that includes two tables and four graphs.  The two tables include my time data from testing and the number of swaps needed in each run to completely sort the arrays.There is a line graph for each sorting algorithm that compares the array types with the amount of time taken to complete the sort. The final graph compares all three sorting algorithms on one chart for an array of random elements.

	According to my own results, the Bubble sort takes the longest no matter the array type. The Selection sort was better than the Insertion sort when the array sizes grew (except for the pre-sorted type), otherwise they were pretty similar. 

	Considering I was making three total copies of each array for each sort, when I got up to testing higher array sizes my computer did not have enough memory to hold all three. A segmentation fault was the result of this. Instead, I had to make only one array and sort it with each algorithm separately. I did not try to do an array size of one million since my bubble sort for a size 750,000 array took 25 minutes to complete. I would be here forever if I continued filling out my chart, but luckily there is an obvious trend without needing to use an array size of one million. Overall my code definitely isn't as efficient as it could be but it was usable for this lab.