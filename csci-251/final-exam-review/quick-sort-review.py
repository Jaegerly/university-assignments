""" definition for partition. """
def partition(array: list[int], low: int, high: int): # 'low' and 'high' are inclusive bounds.
    pivot = array[high]

    while True:
        while array[low] < pivot:
            low += 1

        while array[high] > pivot:
            high -= 1

        if high < low:
            return high

        else:
            temp = array[high]
            array[high] = array[low]
            array[low] = temp

            low += 1
            high -= 1

""" definition for quicksort. """
def quicksort(array: list[int], low: int, high: int): # 'low' and 'high' are inclusive bounds.
    if low == high:
        return

    divider = partition(array, low, high)
    quicksort(array, low, divider)
    quicksort(array, divider + 1, high)

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