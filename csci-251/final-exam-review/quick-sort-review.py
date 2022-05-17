def partition(array: list[int], low: int, high: int): # 'low' and 'high' are inclusive
    total = sum(array[low:(high + 1)])
    length = (high + 1) - low

    pivot = total / length

    while True:

        while array[low] < pivot:
            low += 1            
    
        while array[high] > pivot:
            high -= 1

        if high <= low:
            return high

        else:
            storage = array[low]
            array[low] = array[high]
            array[high] = storage

            low += 1
            high -= 1 

def quicksort(array: list[int], low: int, high: int): # 'low' and 'high' are inclusive
    if low == high:
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