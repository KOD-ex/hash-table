import string
import random
from dataclasses import dataclass

class DictClass(object):
    def __init__(self):
        self.size = 10000
        self.storage = [[]] * self.size
    def __setitem__(self, key, value):
        #хэшировани ключей
        if isinstance(key, str): 
            key1 = [ord(x) for x in key ]
            key2 = sum(key1)
        else:
            key1 = [int(x) for x in key ]
            key2 = sum(key1)
        #если длина подмассива == 0
        if len(self.storage[key2]) == 0:
            self.storage[key2] = [[key, value]]
        #если длина подмассива != 0
        if len(self.storage[key2]) > 0:
            for i in range(len(self.storage[key2])):
                if self.storage[key2][i][0] == key:
                    self.storage[key2][i] = [key, value]
                else:
                    self.storage[key2] += [[key, value]]
    def __getitem__(self, key):
        #перевод ключа в хэш
        if isinstance(key, str): 
            key1 = [ord(x) for x in key ]
            key2 = sum(key1)
        else:
            key1 = [int(x) for x in key ]
            key2 = sum(key1)
        #поиск значения по ключу c конца массива
        a = len(self.storage[key2]) - 1
        for i in range(len(self.storage[key2])):
            if key == self.storage[key2][a][0]:
                return self.storage[key2][a][1]
            a -= 1

def random_string(l=10):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for _ in range(l))

def test_dict(DictClass):
    for _ in range(1000):
        baseline = {}
        d = DictClass()

        for _ in range(1000):
            key_len = random.randint(0, 10)
            k = random_string(key_len)
            v = random_string()
            d[k] = v
            baseline[k] = v

        for k, v in baseline.items():
            if d[k] != v:
                print(f"Failed for {k}: {v} != {d[k]}")
                return
            print("All ok!")

test_dict(DictClass)
