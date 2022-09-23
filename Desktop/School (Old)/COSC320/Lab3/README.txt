Kalyn Howes
Lab 3 - README
2.18.21

	Overloading the [] operator in the Heap struct so that the first index is 1 was difficult to stay with throughout the program. However, it makes more sense logically and I ended up liking it a lot better once I got used to it. Many ways I usually construct for loops, for example, had to be reworked to match the overloaded operator.

	Heap Sort has a O(nlogn) time complexity for every case. Looking more specifically at the subroutines involved in Heap Sort, the Max Heapify function runs in O(logn) time and the Build Max Heap procedure runs in linear time. These contribute to why Heap Sort has the time complexity of O(nlogn).

	As the array sizes increase, so does the number of seconds Heap Sort took to complete. This was the case for the size of the elements in the array as well. Looking at my graph, it seems all of the different array types have linear trends. The arrays that were sorted and sorted backwards have smaller slopes than the arrays thats included duplicates and random numbers.
	
	Looking at my graph, it seems the Heap Sort works the best with the arrays that were already sorted and/or sorted backwards. The arrays that included duplicates and random numbers were very similar and took longer than the other two types. As the array sizes increased, the duplicates and random times became further and further from the sorted and backwards times. 

	Learning from previous labs, instead of coding my random numbers as up to 100, I designated that value to be the same size as the length of the array. This way the array types were more even in terms of big and small elements within the array.
	In my struct, I feel something is wrong with my pointer to my array and the way I use it with the [] operator overload. However, it is working for some reason and to be honest I am afraid to change it! 
	Otherwise, I feel the code is pretty straightforward and the extra functions that are not used are included for any future heap work I might do. 