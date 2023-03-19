import logging
from threading import Thread
import time

def update(nome, valor):
  global contador
  logging.info("Thread %s: lendo o contador", nome)
  contador_local = contador
  contador_local += valor
  time.sleep(1)
  contador = contador_local
  logging.info("Thread %s: modificou o contador", nome)
  
format = "%(asctime)s - %(message)s"
logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")
#variável global
contador = 0
t1 = Thread(target=update, args=(1,10,))
t2 = Thread(target=update, args=(2,20,))
t3 = Thread(target=update, args=(3,30,))
t4 = Thread(target=update, args=(4,40,))
t5 = Thread(target=update, args=(5,50,))
t1.start()
t2.start()
t3.start()
t4.start
t5.start()
time.sleep(3)
print("valor do contador", contador)
