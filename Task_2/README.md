Task 2: Bird Tracking
Avid bird-watchers use an app to keep track of the birds they have seen during a bird-watching (or birding) trip. Every trip, a bird-watcher will see a variety of birds, including some they have seen before, and some they have not seen. Birds previously unseen are referred to as "Lifers", and there is some element of competition amongst bird watching enthusiasts to see the most birds, and thus gather the most lifers, possible. There are certain rules of course, to recording what birds can be recorded:

Only real birds can be recorded - specifically, it has to be a bird that is within the Clement's Checklist of Birds of the World.

Each bird can be recorded multiple times, and it is best practice to keep track of how many times a bird has been seen. This is so that citizens can help to contribute to science and monitoring bird populations. 

Of course, given that birds are usually some distance away and tend not to stay still, it is important to be able to quickly record birds and check if you have seen them. Some examples of Australian birds are given below:

Left and Middle: Little Wattlebirds, Right: Crimsonwing Rosella

Part A (Code)
A regular bird-watching group has invited some tourists to go birding with them. The tourists really wanted to find some new birds the group has not seen but were not confident as it was their first time going birding. Fortunately, there is a list of birds the group has seen available, and the tourists thought to ask online to see if anyone would be willing to put together a system to help with quickly checking if the birds they spot have been seen by the group before or not. 

Part B (Code)
Hooked on birding, the tourists realise that they really want to contribute to citizen science and track how many of each bird they have seen, in a very fast way. They also realise that due to naming differences in different countries, they sometimes input the wrong bird name and would like to delete it so that they can replace it with a more accurate name. Seeing no reason to let the previous work go to waste, the tourists once again reach out online to find someone who can modify the previous system to allow for counting how many birds have been seen, and deleting birds from the list.

Part C (Written)
The tourists realise that there may be some issues with deletion but are unsure and are asking for your thoughts on whether there are any possible issues with deletion. They also wish to know if there has been any significant change in the runtime and size of the system after the modification in Part B compared to Part A. How have the time and space complexity changed from going from a standard system of Part A to the modified system in Part B?

Part D (Code)
The tourists have come upon a fatal flaw in the system from Part B: it seems there is a limit to how many birds they can add. They once again ask online for help in making a system that efficiently allows them to do all of the previous tasks, but also can add as many birds as they like. 

Part E (Written)
Similar to before, the tourists are interested in any significant change in the runtime and size of the system after the modification in Part D compared to Part A. How have the time and space complexity changed from going from the basic system of Part A to the modified system in Part D?

Task 2: Bloom Filters
Background - Bloom Filters
Bloom Filters offer a fast and space-efficient way of checking the existence of an item in a set. Previously we saw that using hash tables, we a best case O(1) look-up, but if you have collisions, you would have an O(n) worse case look-up.  

Bloom Filters are a probabilistic data structure that work by storing hash values, rather than the underlying keys. In addition, we tend to store more than one hash value per key. 

Initially, every entry in the Bloom Filter is set to 0. To insert in a Bloom Filter, we first hash our key with k different functions, and we set the table entry associated with each of those values to 1, irrespective of their previous value. Here, k is a parameter we can tune, and the hash function will be provided.

To check if a key is in our set, we simply need to check if the k positions given by hashing the key are non-zero. If any of them are zero, then the key is "definitely not in the set". Otherwise, the key is "probably in the set". This approach allows us to have an O(k) look-up, at the cost of some uncertainty.

In addition, if we assign individual bits to 0 or 1, we can represent entries in the Bloom filter more efficiently. Recall that a single integer is 32 bits, meaning we significantly reduce the amount of space we use when using a Bloom filter. This is important when we are dealing with large datasets, and want a very fast look-up.

We will use bloom filters to check if we have seen certain birds before.

All three Bloom Filter variants must use a bit array for this task to receive any marks (i.e. A single int length value must contain 32 entries in the initial Bloom filter and should contain 32 BUCKET_SIZE entries for the other tasks).

Part A (Code)
Part A will implement a simple Bloom Filter and relevant functionality in bf.c, such as the functions of:

Adding an element (done in addBF).

Searching for membership in the set (done in checkBF and birdCheckBF).

To support checking, you will search your Bloom Filter and perform necessary bit operations. For each query, you must return the query (i.e. the bird's name) followed by whether or not it is within the filter.

The first argument for each part will be the type of Bloom filter implemented (B for Part A, C for Part B and D for Part D).

Part A will take two filenames from the command line:

The first filename is the name of the list of birds seen by the group.

The second filename is the name of the birds to be queried.

The format of the file with the first given filename will be similar to this example:

10 0.01
Abbott's Babbler
Abbott's Booby
Abbott's Starling
Abd al Kuri Sparrow
Abdim's Stork
Aberdare Cisticola
Aberrant Bush Warbler
Abert's Towhee
Abyssinian Catbird
Abyssinian Crimsonwing

Where all files follow the format:

The first line specifies the number of birds that have previously been seen (10 in this example), and the desired false positive rate (0.01).

All following lines specify names of birds that have been previously seen.

The format of the file with the second given file name will be similar to this example:

Abbott's Booby
Abyssinian Catbird
Abyssinian Crimsonwing
Blyth's Frogmouth
Emerald-chinned Hummingbird
Lemon Dove

Where each line is simply the name of the bird, seen on the current bird-watching trip. 

The output must be the list of words ordered by input of birds, and whether or not they are in the list. For the given example this would be:

     ...Reading... 
     ...Checking... 
Abbott's Booby              : Possibly in the list
Abyssinian Catbird          : Possibly in the list
Abyssinian Crimsonwing      : Possibly in the list
Blyth's Frogmouth           : Definitely not in the list
Emerald-chinned Hummingbird : Definitely not in the list
Lemon Dove                  : Definitely not in the list

Hint: For the spacing, use the %-30s format specifier

Part B (Code)
Though Bloom filters can be quite efficient, they prevent us from knowing characteristics about the data such as "how many items do we have in our filter?". They also do not allow us to delete items, which can be something we desire. 

In Part B, the first argument will be C, the first two file inputs which follow are the same as in the prior part, but there will be additional third file input specified by an additional argument given on the command line. This input will be the name of the file storing a list of birds to remove from the Bloom Filter (as they were mistakenly recorded by the bird watcher). For example, if Wompoo Fruit Dove was in the list of birds to delete, we would want to remove it from the Bloom Filter. 

To do this, Part B will implement a counting Bloom filter. The new counting Bloom filter is almost identical to the standard filter used in part A, except that instead of each entry in the Bloom filter being a single bit, it is now 4 bits. Instead of changing a 0 to 1 at each hash value, we instead have the relevant buckets incremented each time something is added. That is to say, we have buckets ranging from 0000 to 1111 in binary representation (0 to 15 in decimal), and we assume that the maximal number of birds in any single bucket must be capped at 15. Deleting an item involves decrementing the associated entries. 

You will need to implement in cbf.c:

Adding elements to counting Bloom filters.

Reading in elements.

Finding how many times an item has (probably) been seen (via a minimum selection algorithm).

Deleting an element.

The output must be a list of the birds, presented in the same order they appeared in the input, along with a value indicating how many times each bird has probably been seen. For the given example this would be:

     ...Reading... 
     ...Checking... 
Abbott's Booby                : Probably 1 in the list
Abyssinian Catbird            : Probably 1 in the list
Abyssinian Crimsonwing        : Probably 1 in the list
Blyth's Frogmouth             : Definitely not in the list
Emerald-chinned Hummingbird   : Definitely not in the list
Lemon Dove                    : Definitely not in the list
     ...Deleting... 
Abbott's Babbler              : Deleted, and now definitely not in the list
Abbott's Booby                : Deleted, and now definitely not in the list

Part B Notes
If adding an item will exceed your limit for each binary counter, then you must output "Overflow occurred." and immediately terminate the function (but not the program) - see the following slides for more details. 

See the diagrams in the following two slides for what to output upon deletion.

Part C (Written)
In Part C, you must create a PDF format document called written-tasks2.pdf, which explains potential issues with item deletion in counting Bloom filters. Your answer must state an upper-bound on the time and space complexity reflecting the impact of having counters over a basic Bloom Filter, with each term used explained clearly.

In order to avoid trivial answers, you must assume that the number of bits dedicated to counting is variable, which we will call c. Include all relevant parameters. 

A paragraph or two is sufficient for a response to this part.

Part D (Code)
The Bloom filters above are limited in scalability as we must know the number of items we read in, in advance. In Part D, you must implement a dynamic counting bloom filter. This variant of the bloom filter effectively layers counting bloom filters like layers of a cake. When one gets full (or an overflow occurs in a bucket), a new one is made and further data is stored there. 

The first argument for Part D, is D. The following input files will be the same as in Part B, except there is no longer the number of birds listed at the start, and instead a desired capacity of each Bloom filter. In addition, for Part D, you can assume that the input will always be alphabetically ordered, and that birds will only be inserted during the initial input (i.e. there will be no ad hoc insertions). 

Insertion involves inserting an item at the current active (latest created) filter. Thus, there will also be the need to track the current utilization alongside the maximum capacity of each filter. 
Look-up involves checking all k positions of the relevant s counting Bloom filters, so long as we keep track of where items are inserted. A Bloom filter is considered relevant where a bird could possibly have been inserted in that Bloom filter, given that you have tracked insertions, it is possible to more precisely determine relevant Bloom filters. You must implement an O(s) space complexity method of tracking item insertions. Deletion also requires you to keep track of where each item was inserted, and then deleting from that filter. Your deletion operation should be O(k+s) worst case, and lookup should be O(ks)  worst case, with average case O(k+s) assuming uniform distribution of all possible bird sightings (and assuming non-limited bird varieties to avoid saturation). You should also assume that the bucket size is a constant.

The above functions should be implemented in dbf.c. The output will be similar to Part B as well.

Part E (Written)
In Part E, discuss the change in complexity in having a dynamic Bloom filter as opposed to a basic Bloom filter. Briefly describe how you implemented an O(k+s) deletion. Note assumptions around what factors can reasonably be held constant (these are similar to the assumptions we would need to make for a hash table). Add this discussion to your report named written-tasks2.pdf.

A paragraph or two is sufficient for a response to this part.

Task 2: Assignment Submission
All three Bloom Filter variants must use a bit array for this task to receive any marks (i.e. A single int length value must contain 32 entries in the initial bloom filter and should contain 32 BUCKET_SIZE entries for the other tasks).

To compile: make -B

A list of commands used for the test cases is provided (in order) in run.txt

To run Part A (standard Bloom Filter): 
./birds B datafiles/t2a_data_1.txt test_cases/t2_1.txt

To run Part B (counting Bloom Filter):
./birds C datafiles/t2b_data_1.txt test_cases/t2_1.txt delete_cases/t2_delete_1.txt

To run Part D (dynamic Bloom Filter): 
./birds D datafiles/t2d_data_50.txt test_cases/t2_1.txt delete_cases/t2_delete_10.txt

The feedback for test cases is given in the standard unified diff format, you can see info on this format online (such as at here). A minus means you have a line that is not in the expected output, a plus means you are missing a line. The diff does not show all output you have produced, only the relevant snippet.

Output Example (Part A):

     ...Reading... 
     ...Checking... 
Abbott's Booby              : Possibly in the list
Abyssinian Catbird          : Possibly in the list
Abyssinian Crimsonwing      : Possibly in the list
Blyth's Frogmouth           : Definitely not in the list
Emerald-chinned Hummingbird : Definitely not in the list
Lemon Dove                  : Definitely not in the list

Hint: For the spacing, use the %-30s format specifier

Output Example (Part B and D):

     ...Reading... 
     ...Checking... 
Abbott's Booby                : Probably 1 in the list
Abyssinian Catbird            : Probably 1 in the list
Abyssinian Crimsonwing        : Probably 1 in the list
Blyth's Frogmouth             : Definitely not in the list
Emerald-chinned Hummingbird   : Definitely not in the list
Lemon Dove                    : Definitely not in the list
     ...Deleting... 
Abbott's Babbler              : Deleted, and now definitely not in the list
Abbott's Booby                : Deleted, and now definitely not in the list

