import unittest

def doNotReturn():
    x = 10

class TestSetForOneModule(unittest.TestCase):
    def test_a_test(self):
        self.assertEqual(12,12)
        
    def testa_test(self):
        self.assertTrue(2 == 4)
       
    def testatest(self):
        self.assertFalse(2 == 4)
        
    def test_assertis(self):
        a = 10
        b = a
        b = 12
        self.assertIs(a, b)
        
    def test_assertnote(self):
        self.assertIsNone(doNotReturn())
        
    def test_assertin(self):
        a = [1,2,3,5,6,7]
        self.assertIn(3, a)
        
    def test_isinstance(self):
        a = [1,2,3,5,6,7]
        
        self.assertIsInstance(a, int)
      