https://leetcode.com/problems/single-number-iii/

XOR of equal items is 0. XOR of two not equal items is XOR of all items (only these two items in array are not equal).
Then we know that some bit (any bit) of that XOR result is set in one item and not set in another.
Hence we can split all array items in two group by that bit. XOR of all items in first group will be res1
and XOR of all items in second group will be res2.