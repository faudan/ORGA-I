# -*- coding: utf-8 -*-
# 
# Autor: Matías López mlopez@gmail.com
# Licencia: GPL

import sys
import shlex
import subprocess
import time
from subprocess import Popen, PIPE, STDOUT

import pygame
from pygame.locals import *

#~ Constantes del programa
CANT_PARAMS = 4
LINEAS = ["clk", "req", "ack", "d0", "d1", "d2", "d3"]

#~ Constantes para el dibujo
SCREEN_WIDTH, SCREEN_HEIGHT = 800, 600
DELTA_Y = 60
Y_0 = 70

#~  Verificación del modo de ejecución
if (len(sys.argv)==1):
    print "Corriendo en modo prueba de visualización"
    launchProcess = False
elif(len(sys.argv)==(CANT_PARAMS+1)):
    for i in range(1, CANT_PARAMS+1):
        if(sys.argv[i]!='0' and sys.argv[i]!='1'):
            print "Los parámetros extra deben ser 0 ó 1, y no ocurre con " + str(i),
            print " que es " + sys.argv[i]
            sys.exit()
    print "Corriendo todos los programas"
    launchProcess = True
else:
    print "Para ejecutar este programa corralo:"
    print " - Sin parámetros para visualizar los datos generados por otros procesos"
    print " - Con", CANT_PARAMS ,"parámetros booleanos, para lanzar todos los procesos y al cpu con la dirección pasada como parámetro"
    sys.exit()

#Inicializamos pygame
pygame.init()
from clases import *

# Definimos la pantalla
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
fondo = pygame.image.load("imgs/fondo.png")
screen.blit(fondo, (0,0))

# Titulo
pygame.display.set_caption("Simulador de Buses - OrgaNo")


procesos = []
if(launchProcess):
    devnull = open('/dev/null', 'w')
    procesos.append(subprocess.Popen("./reloj", stdout=devnull))
    time.sleep(1)
    procesos.append(subprocess.Popen("./memoria", stdout=devnull))
    time.sleep(1)
    clien = subprocess.Popen('./cpu', stdin=PIPE, stdout=devnull)
    procesos.append(clien)

    params=""
    for i in range(1,CANT_PARAMS+1):
        params+=sys.argv[i]+"\n"

    clien.stdin.write(params)

# Cargo los Sprites
lineas = []
cont = 0
for i in LINEAS:
    l = Linea(i,Y_0 + DELTA_Y*cont,screen)
    if l.line_exists():
        lineas.append(l)
        cont+=1

for i in lineas:
    i.draw(screen)
#Comienza la simulacion
playing = True

fin_pantalla = pygame.sprite.Sprite()
fin_pantalla.rect = Rect(735, 0, 10, SCREEN_HEIGHT)

clock = pygame.time.Clock()

pause = False

while playing:
    clock.tick(6)
    #~ clock.tick(30)

    for event in pygame.event.get():
        if event.type == QUIT:
            playing = False
        elif event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    playing = False
                if event.key == K_SPACE:
                    pause = not(pause)

    if(pause):
        continue

    # Verifico las colisiones
    for i in lineas:
        pygame.sprite.spritecollide(fin_pantalla,i,True)
        i.clear(screen,fondo)
        i.actualizar()
        i.draw(screen)

    pygame.display.flip()

for i in procesos:
    i.kill()

pygame.time.wait(1000)
pygame.quit()
