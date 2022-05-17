def aordescend(array: list[int]) -> bool: # returns true if array is ascending or descending
    if len(array) == 1:
        return True

    ascending = True
    descending = True

    index = 0

    while (index < len(array) - 1): # compare array[index] with array[index + 1]
        if (not ascending) and (not descending): # skip uneeded loop iterations
            break
        
        if descending and (array[index] < array[index + 1]):
            descending = False

        if ascending and (array[index] > array[index + 1]):
            ascending = False

        index += 1

    return ascending or descending

import unittest

class TestSuite(unittest.TestCase):

    def test_aordescend(self):
        array = [1, 2, 3, 4, 5, 6, 7, 8]
        self.assertTrue(aordescend(array))

        array = [100, 98, 65, 21, 1]
        self.assertTrue(aordescend(array))

        array = [1, 1, 1, 1, 1, 1, 1]
        self.assertTrue(aordescend(array))

        array = [1, 5, 3, 10, 19, 18]
        self.assertFalse(aordescend(array))

if __name__ == '__main__':
    unittest.main()