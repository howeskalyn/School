Kalyn Howes
Lab 2
2.11.21

	The theoretical time complexity of the Quick Sort algorithm is O(nlogn) for the best case and  O(n^2) for the worst case. As for the Merge Sort algorithm, the time complexity for all cases is O(nlogn). 

	For Quick Sort, as the number of elements in the array increased, the number of seconds increased more quickly. As for the Merge Sort, the number of seconds still increased but not by much at all. For the Merge Sort it seems the theoretical time complexity matched the data I found. However for the Quick Sort, the seconds it took to complete the sort was fewer when the array had duplicates and was random rather than when it was in order. This is my own fault since I only programmed to use random numbers up to 100 (in the duplicate and random arrays), while the sorted and backwards sorts included numbers up to the size of the array itself.

	According to my test results, the Quick Sort had an easier time with the arrays that included duplicates and random numbers. However, like I explained before, this is a fault of my programming and not the sort itself. The Merge Sort had the lowest times when the array was sorted, but overall every Merge run took under a second even for arrays of size one million.

Because of my coding fault, my observations for Quick Sort do not confirm the difference in best and worst cases. However, my data does confirm the best and worst cases for Merge Sort.

Both the Quick Sort and the Merge Sort do much much better than the Bubble Sort did in Lab 1. For example, for a random array of 750,000 the Bubble Sort took 1504 seconds (about 25 minutes) to finish while the Quick Sort took 14 seconds and the Merge Sort only 0.193 seconds.

	In order to properly test my code I should change how my random numbers are generated so that my arrays of duplicate and random elements are fair to those that are sorted and sorted backwards. Also, I had issues with segmentation faults for the Quick Sort once the array sizes grew past 500,000. Again, these issues were only had with the arrays that included pre-sorted and backwards sorted elements. I used dynamic memory to create my initial arrays and still had issues. I am not quite sure what went wrong with my Quick Sort since my Merge Sort had no problems at all. Overall my code could definitely be more efficient but I was still able to find trends within my data.