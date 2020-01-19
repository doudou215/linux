from sys import exit
from random import randint
from textwrap import dedent

class Scene(object):
    def enter(self):
        print("This is not a finished scene.")
        exit(1)

class Apple(Scene):
    pass

class Banana(Scene):
    pass

class Orange(Scene):
    pass

class Peal(Scene):
    pass
class Death(Scene):
    pass
class Map(object):
    my_map={'apple' : Apple(),
           'banana' : Banana(),
           'orange' : Orange(),
            'peal' : Peal(),
            'finish' : Death()}
class Engine(object):
    def __init__(self,map):
        self.map=map
