""" split partition in two, where both slices are <= or >= a pivot. """

def partition(array: list[int], low: int, high: int): # 'low' and 'high' are inclusive bounds.
    total = sum(array[low:(high + 1)]) # sum of elements in partition
    length = (high + 1) - low # to avoid a -1 case.

    pivot = total / length # this way of calculating a pivot ensures a central number.

    while True:
        while array[low] < pivot:
            low += 1

        while array[high] > pivot:
            high -= 1

        if high <= low:
            return high

        else:
            temporary = array[low]
            array[low] = array[high]
            array[high] = temporary

            low += 1
            high -= 1

""" split partition in two and sort both partitions. """

def quicksort(array: list[int], low: int, high: int): # 'low' and 'high' are inclusive bounds.
    if low == high: # base case for quicksort.
        return

    divider = partition(array, low, high)

    quicksort(array, low, divider)
    quicksort(array, divider + 1, high)
     
    return

""" tests for quicksort. """

import unittest

class TestSuite(unittest.TestCase):

    def test_quicksort(self):
        array = [1, 5, 3, 0, 190, 2]
        quicksort(array, 0, 5)
        self.assertEqual(array, sorted(array))

        array = [5, 5, 5, 5, -1, 80, 65]
        quicksort(array, 0, 6)
        self.assertEqual(array, sorted(array))

if __name__ == '__main__':
    unittest.main()