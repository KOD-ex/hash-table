import pygame 
import string
import random
from dataclasses import dataclass

pygame.init()
win = pygame.display.set_mode((700,500))
pygame.display.set_caption('График хэш-функции')
#x
pygame.draw.line(win, (255,255,255), (40,480), (640,480), 2)
#черточи для х и цифры
x1 = 40
number = 0
myfont = pygame.font.SysFont(None, 15)
for i in range(26):
	pygame.draw.line(win, (255,255,255), (x1,480), (x1, 484), 1)
	number = str(number)
	text = myfont.render(number, True, (255,255,255))
	win.blit(text, (x1, 490))
	number = int(number)
	number += 4
	x1 += 24
#y
pygame.draw.line(win, (255,255,255), (40,80), (40, 480), 2)
#черточки для y и цифры 
y1 = 480
number2 = 0.5
for i in range(4):
	y1 -= 100
	pygame.draw.line(win, (255,255,255), (40,y1), (36, y1), 1)
	number2 = str(number2)
	text = myfont.render(number2, True, (255,255,255))
	win.blit(text, (10, y1))
	number2 = float(number2)
	number2 += 0.5
#обозначение x, y 
myfont2 = pygame.font.SysFont(None, 20)
text = myfont2.render('по оси x - хэши', True, (255,0,255))
win.blit(text, (500, 10))
text = myfont2.render('по оси y - % коллизий', True, (255,0,255))
win.blit(text, (500, 20))

pygame.display.update()

def hash_funxion_one(key):
    #хэшировани ключей
    if isinstance(key, str): 
        key1 = [ord(x) for x in key ]
        key_hash = sum(key1)
        key_hash %= 100
    else:
        key1 = [int(x) for x in key ]
        key_hash = sum(key1)
        key_hash %= 100
    return key_hash
def random_string(l=10):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for _ in range(l))
a = 0
hashs = []
for i in range(50000):
	if a != 0:
		break
	key_len = random.randint(0, 10)
	k = random_string(key_len)
	#добавление и проверка хэша двух хэш-функций
	if hash_funxion_one(k) != 0:
		hashs.append(hash_funxion_one(k))
for i in range(len(hashs)):
	if a != 0:
		break
	pygame.time.delay(100)
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
	  		a = 1
	x = 43 + hashs[i] * 6
	percentage = (hashs.count(hashs[i]) / 50000) * 100
	print(hashs.count(hashs[i]))
	p_max = 2
	p_min = 0
	y_min = 0
	y_max = 480
	y = y_max - percentage / (p_max - p_min) * (y_max - y_min)
	percentage_line = (hashs.count(hashs[i] + 1) / 50000) * 100
	x_line = x + 6
	y_line = y_max - percentage_line / (p_max - p_min) * (y_max - y_min)
	pygame.draw.line(win, (255, 0, 0), (x,y), (x + 6,y),1)
	pygame.draw.line(win, (255, 0, 0), (x_line,y), (x_line, y_line),1)
	pygame.display.update()
