import pygame
import os

font = pygame.font.Font(None, 26)
X_INICIAL = 100
PATH_LINES = "bus/"

class Linea(pygame.sprite.Group):
    def __init__(self, name, ypos, screen):
        pygame.sprite.Group.__init__(self)
        self.name = name
        self.ypos = ypos

        image = pygame.sprite.Sprite()

        if self.line_exists():
            image = font.render(" "+name+" ",True, (0,0,0), (200, 200, 200))
            screen.blit(image, (X_INICIAL-50, self.ypos+30))
       
    def line_exists(self):
        return os.path.isfile(PATH_LINES + self.name) 

    def actualizar(self):
        f = open(PATH_LINES + self.name)
        val = f.read()
        
        if(len(val)>0):
            self.setValue(val[0])
        else:
            self.setValue("-")
        f.close()
        
    def setValue(self, n):
        self.avanzarTodos()
        if(n=="0"):
            s = SignalZero()
        elif(n=="1"):
            s = SignalOne()
        else:
            s = Empty()
            
        s.rect.topleft = (X_INICIAL, self.ypos)
        self.add(s)
        
    def avanzarTodos(self):
        for i in self:
            i.rect.move_ip(4,0)
        
class Bus(pygame.sprite.Sprite):
    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.rect = self.image.get_rect()
        colisiona = True
        
class SignalOne(Bus):
    image = pygame.image.load("imgs/one_s.png")
    
class SignalZero(Bus):
    image = pygame.image.load("imgs/zero_s.png")

class Empty(Bus):
    image = pygame.image.load("imgs/x_s.png")
