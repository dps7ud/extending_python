from naive import naive
import random
import unittest

"""This file defines a number of tests for the functions
    in naive.py that define a merge sort
"""

class Tests(unittest.TestCase):
    def setUp(self):
        # We're okay picking an arbirary seed here.
        random.seed(0)

    def test_empty(self):
        empty = []
        self.assertEqual(naive(empty), empty)

    def test_one(self):
        one = [1]
        self.assertEqual(naive(one), one)

    def test_two_in_order(self):
        two = [1,9]
        self.assertEqual(naive(two), sorted(two))

    def test_two_out_order(self):
        two = [9,1]
        self.assertEqual(naive(two), sorted(two))

    def test_two_same(self):
        two = [1,1]
        self.assertEqual(naive(two), sorted(two))

    def test_three_abc(self):
        abc = [1,2,3]
        self.assertEqual(naive(abc), sorted(abc))

    def test_three_acb(self):
        abc = [1,3,2]
        self.assertEqual(naive(abc), sorted(abc))
        
    def test_three_bac(self):
        abc = [2,1,3]
        self.assertEqual(naive(abc), sorted(abc))

    def test_three_bca(self):
        abc = [2,3,1]
        self.assertEqual(naive(abc), sorted(abc))

    def test_three_cba(self):
        abc = [3,2,1]
        self.assertEqual(naive(abc), sorted(abc))

    def test_three_cab(self):
        abc = [3,1,2]
        self.assertEqual(naive(abc), sorted(abc))

    def test_three_aba(self):
        abc = [1,3,1]
        self.assertEqual(naive(abc), sorted(abc))

    def test_three_aaa(self):
        abc = [1,1,1]
        self.assertEqual(naive(abc), sorted(abc))

    def test_16(self):
        st = [random.randrange(100) for i in range(16)]
        self.assertEqual(naive(st), sorted(st))

    def test_17(self):
        st = [random.randrange(100) for i in range(17)]
        self.assertEqual(naive(st), sorted(st))

    def test_15(self):
        ft = [random.randrange(100) for i in range(15)]
        self.assertEqual(naive(ft), sorted(ft))

    def test_100(self):
        hunnid = [random.randrange(100) for i in range(100)]
        self.assertEqual(naive(hunnid), sorted(hunnid))

    def test_1024(self):
        ttf = [random.randrange(100) for i in range(1024)]
        self.assertEqual(naive(ttf), sorted(ttf))

    def test_1023(self):
        ttt = [random.randrange(100) for i in range(1023)]
        self.assertEqual(naive(ttt), sorted(ttt))

if __name__ == '__main__':
    unittest.main()
