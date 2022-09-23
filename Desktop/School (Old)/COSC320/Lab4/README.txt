Kalyn Howes
2.24.21
Lab 4

README

(a)
	In an attempt to make a priority queue, I used a Heap structure and techniques from the last Lab. This includes old functions like MaxHeapify, BuildMaxHeap, and print methods, but also new functions such as ExtractMax, Peek, Insert, Expand, and IncreaseKey. I also included an overload of the << operator for printing purposes, and with that a few inline "get" functions.
	To generalize my code, templates are included. This allows the user to make a priority queue of any data type, instead of just integers. 
	(Also, in between each make run you must use a "make clean" command.)


(b) 
	IncreaseKey has a theoretical time complexity of theta(logn), MaxHeapify is T(n)=O(n), and BuildMaxHeap has at most T(n)=O(nlogn). ExtractMax is constant within itself, but calls MaxHeapify. Peek is constant since it is simply returning data from an array. Insert is also constant within itself, since it only includes array assignments, but it calls BuildHeap. The Expand function (I don't have confidence in its correctness) is currently O(n) because it includes one for loop from i to n.


(c) 
	As the input sizes get larger, so will the absolute timing of the different algorithms. Obviously each algorithm does not scale with the input in the same way, but they all follow the general rule of more inputs = more time. For example, an algorithm like BuildMaxHeap that has a time complexity of O(nlogn) will grow slower at first, in comparison to an algorithm like MaxHeapify which is linear. However, if you were to graph nlogn and n, you will see the nlogn passes the n and becomes quicker. Around n=10, the functions intersect and the nlogn actually becomes larger. 

(d)
	A priority queue in a real-life situation could be in a hospital. At first, as the patient walks in they are added to the queue. However if a patient enters the hospital who is in need of emergency care, they are higher priority and will be moved up in the queue. If there were a computer check-in system, a priority queue could be used and doctors/nurses could give an inputted value (person) a higher priority. This would ensure there are no deaths while everyone still gets the care they need. 
	Another application could include an operating system using a scheduling process where the next event executed has the highest priority. This could mean it was flagged to be high priority or it could be based on the amount of time it will take to finish the process. If the user would like shorter tasks to be done first, that could be specified, or vice-versa. Other data structures could be used but this would ensure the efficiency of the operating system.


(e) How could the code be improved in terms of usability, efficiency, and robustness?
	Personally, I feel I need to get a better understanding of exactly what each algorithm is doing overall. Other than that, I had issues printing out my queues at first - if it had a size of 5, only 4 nodes would print. After working on that for awhile I found out that in the process of testing my ExtractMax and Peek functions, I was calling them before printing my Heaps which caused the current_size to decrement because the ExtractMax function! That was quite the realization.
	Anyways, the only issue left is using the IncreaseKey in my Insert function. I cheated by using a BuildHeap instead. Using the IncreaseKey works for integer data types but not when I test the strings. When I enter the first name and hit return, the next name prompt doesn't show. 





RE - DO:
	Origninally, there was issues with my extractMax function and memory. Throughout my coding process, the difference between data and key kept confusing me. I think the problem with extractMax is now fixed.
	There was also a memory error with some of my operator= for the heaps. I hope this is fixed...
	I also had an issue with the IncreaseKey function. Taking another look I realized what I was doing wrong and, and realized once again that I had confused .key and .data in my struct.
	Also in that function, I was using the current_size value instead of the i variable in several spots.

