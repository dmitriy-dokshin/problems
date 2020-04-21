https://www.hackerrank.com/challenges/largest-rectangle/problem

### Intuition

The main idea is to have items in ascending order. For that purpose a stack of pairs <width, height> can be used. Going through the array check each item. If its height is greater or equal to height of the stack's top, just push it to the stack. Otherwise pop items from the stack until that condition is satisfied, calculating the largest rectangle that can be constructed using those items. In the end pop all items from the stack following the same procedure.
