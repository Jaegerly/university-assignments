def specificorder(array: list[int], ascending: bool) -> bool:
    length = len(array)
    
    if length == 1:
        return True
    
    index = 0

    while (index < length - 1):
        if (ascending and array[index] > array[index + 1]) or ((not ascending) and array[index] < array[index + 1]):
            return False
        index += 1
    
    return True

import unittest

class TestSuite(unittest.TestCase):

    def test_specificorder(self):
        array = [1, 2, 3, 4, 5, 6, 7, 8]
        self.assertTrue(specificorder(array, True))

        array = [100, 98, 65, 21, 1]
        self.assertTrue(specificorder(array, False))

        array = [1, 1, 1, 1, 1, 1, 1]
        self.assertTrue(specificorder(array, False))

        array = [1, 5, 3, 10, 19, 18]
        self.assertFalse(specificorder(array, False))

if __name__ == '__main__':
    unittest.main()