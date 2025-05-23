# COMP2007 Assignment 2 (Sem 1, 2025): Dynamic Programming Solutions

## Task 1: Feeding and Breeding Eels - Episode II

You are, once again, an eel in the river systems of the Kulin Nation.

Iuk is fast approaching, and so you need to reach the ocean soon so to begin the journey to the Coral Sea for breeding. You find yourself deep within the river system, and you need to reach the ocean in a certain amount of time or else get left behind. However, you also need to stock up on as much fat as possible so that you are able to survive the journey to the Coral Sea. This time around, you have not found the great feeding grounds of yesteryear, and instead you must source your food from the lakes as you travel back to the ocean.

Travelling down rivers costs fat, but lakes contain food in them which can increase fat supplies.

In this Task, first we will solve a relaxed problem, and then modify the solution to work on a slightly harder problem.

### Part A: Basic River Navigation
As an eel, you are very interested in eating as much tasty seafood as you can, but want to be at the ocean in time for the breeding season. You know that your journey from the ocean onwards will be difficult, and thus it would be in your best interest to have the most possible fat upon reaching the ocean within the time constraints you face. As such, you wish to know what the best path to take to the ocean is.

Assume that for all parts in this task, despite being an eel, you have the ability to write C code and written responses.

Design a dynamic programming algorithm which finds the path to the ocean that gives the largest fat retained in your body upon reaching the ocean, limited by the amount of time you have left until breeding season happens.

Initially, assume that traversing a river always takes exactly 1 day, and as before, you lose some fat as you traverse a river. In addition, as you do not wish to be sick from overeating, there is a maximum amount of fat you can have at any point. Similarly, running out of food will lead to your demise, and so you also always want to have some fat. Of course, you cannot traverse a river if your fat will drop to 0 or below whilst traversing it, even if there is a lot of food in the lake it flows into.

You may have lakes that actually decrease the fat you have stored as well, due to evading invasive bird species in the area.

If there are multiple paths with the same maximal fat retained, choose the one with the earliest arrival to the ocean. Amongst the solutions that have the same fat retained and same arrival day, choose any of them.

#### Input Format
```
N M S O       # Lakes, Rivers, Start ID, Ocean ID
K F C         # Initial fat, Max fat, Time limit
gain[0..N-1]  # Fat gain/loss at each lake (can be negative)
M lines of:   # River connections (directed)
u v w         # From lake u to v, cost w fat units
```

#### Output Format
For successful paths:
```
Max fat: X
Path: lake1, lake2, ..., oceanLake
```
For impossible scenarios:
```
No path :(
```

### Part B: Advanced River Navigation
Though you were initially happy with your plan to get to the ocean, you have realised a fatal error: namely, you cannot traverse every river in only a single day. Now assume you believe that the time it takes to traverse a river is equal to the fat lost in the river.

You wish to develop a new dynamic programming solution (or a modification of the previous) to solve this new problem.

As in Part A, your program will receive two arguments, the first argument will be the part (always B for this task) and the second argument will be the input filename.

The input and output format will be identical to Part A.

### Part C: Written Analysis
Requirements for `written-1C.pdf`:

#### Part A Analysis
1. **State Representation**
   - Define DP states and parameters
   - Explain fat level management (keeping between 0 and F)
   - Detail time limit handling approach

2. **Recurrence**
   - Provide complete formula and rules
   - Define all base cases
   - Justify correctness of recurrence and base cases

3. **Time Complexity**
   - Analyze both time and space complexity
   - Provide Big-O notation with defined terms
   - Note: DP complexity differs from recurrence closed form

4. **Backtrace**
   - Specify location of final answer in DP table
   - Detail solution reconstruction process

#### Part B Analysis
- Document only modifications from Part A
- Reference unchanged elements
- Provide updated explanations where needed

### Implementation Notes
- Solutions must be implemented in C
- Program arguments: part letter (A/B) and input filename
- Recommended length for written analysis: 1-2 pages
- Review Part C before implementing Parts A and B