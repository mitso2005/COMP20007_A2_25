# COMP20007 Assignment 2 Task 1C: Written Analysis

## Part A: Dynamic Programming Solution

### 1. State Representation

Each state in the dynamic programming (DP) solution is represented by a tuple `(lake, time)`, where:
- `lake` is the current lake the eel is at (an integer from 0 to N-1).
- `time` is the number of days remaining until the breeding season (an integer from 0 to C).

The DP table `dp[lake][time]` stores the **maximum fat** the eel can have at lake `lake` with `time` days remaining.  
Auxiliary tables `parent[lake][time]` and `parentTime[lake][time]` are used to reconstruct the optimal path.

**Fat Management:**  
- When transitioning between states, fat is updated by subtracting the river traversal cost and adding the fat gain/loss of the destination lake.
- Fat is capped at the maximum allowed (`F`) and transitions that would result in fat ≤ 0 are not allowed.
- Transitions are only allowed if the eel has enough fat to survive the river and does not exceed the time limit.

### 2. Recurrence

Let `dp[lake][time]` be the maximum fat achievable at `lake` with `time` days remaining.

**Base Case:**  
- At the start: `dp[S][C] = K` (if `K > 0`), where `S` is the starting lake, `C` is the time limit, and `K` is the initial fat.

**Recurrence:**  
For each lake `u`, time `t`, and for each outgoing river from `u` to `v` with cost `w`:
- If `dp[u][t] != -1` and `t >= 1` and `dp[u][t] > w`:
    - `fatAfterTravel = dp[u][t] - w`
    - `fatAfterEating = fatAfterTravel + gain[v]`
    - If `fatAfterEating > 0`, set `fatAfterEating = min(fatAfterEating, F)`
    - If `dp[v][t-1] < fatAfterEating`, then:
        - `dp[v][t-1] = fatAfterEating`
        - Update parent pointers for backtrace

**Justification:**  
- The recurrence ensures that at each step, the eel only transitions to valid states (enough fat, within time).
- The DP table always stores the best (maximum) fat for each state.

### 3. Time Complexity

Let:
- `N` = number of lakes
- `C` = time limit
- `M` = number of rivers (edges)
- `D` = maximum out-degree (rivers per lake)

**Time Complexity:**  
- For each time step (C), each lake (N), and each outgoing river (D):  
  O(N * C * D)
- Since D ≤ N in the worst case,  
  **O(N * C * N) = O(N^2 * C)**

**Space Complexity:**  
- The DP and parent tables are O(N * C) each.

### 4. Backtrace

**Location of Final Answer:**  
- The optimal solution is found by checking all `dp[O][t]` for the destination lake `O` and all valid times `t` (0 ≤ t ≤ C).
- The best fat and earliest arrival time are selected.

**Reconstruction:**  
- Starting from the best `(O, t)`, use the `parent` and `parentTime` tables to trace back through the states until reaching the origin.
- The path is then reversed to produce the correct order.

---

## Part B: Differences from Part A

### State Representation

- The state is still `(lake, time)`, but **time now decreases by the river cost** (not always 1).
- When traversing a river with cost `w`, the time decreases by `w` instead of 1.

### Recurrence

- The recurrence is modified so that for each river with cost `w`, the transition is only allowed if `t >= w`, and the next state is at `timeAfter = t - w`.

### Time Complexity

- The time complexity remains **O(N^2 * C)**, as the number of possible states and transitions is unchanged, but the time decrement per transition is variable.

### Backtrace

- The backtrace process is unchanged, except that time steps may decrease by more than 1 per transition.

---

## Summary

- The DP solution efficiently finds the optimal path and fat reserves for the eel, respecting all constraints.
- Part B only changes the time decrement per river, but the overall structure and complexity remain the same.
