def binarysearch(key: int, array: list[int], start: int, end: int): # 'start' and 'end' are inclusive
    if end < start: # if window bounds have crossed, array has already been searched, and thus, does not contain key
        return -1

    extraction = (start + end) // 2

    if key == array[extraction]:
        return extraction

    if key < array[extraction]:
        return binarysearch(key, array, start, extraction - 1)

    if key > array[extraction]:
        return binarysearch(key, array, extraction + 1, end)

import unittest

class TestSuite(unittest.TestCase):

    def test_binarysearch(self):    
        result = binarysearch(10, [2, 5, 10, 17], 0, 3)
        self.assertEqual(result, 2)

        result = binarysearch(174, [2, 5, 7, 10, 17, 20, 80, 90, 174], 0, 9)
        self.assertEqual(result, 8)

        result = binarysearch(174, [3, 12, 70, 100, 116, 198, 214], 0, 6)
        self.assertEqual(result, -1)

if __name__ == '__main__':
    unittest.main()