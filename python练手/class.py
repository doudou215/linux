from sys import exit
from random import randint
from textwrap import dedent

class Scene(object):
    def enter(self):
        print("This is not a finished scene.")
        exit(1)

class Apple(Scene):
    def enter(self):
        print("This is apple")
        return 'death'

class Banana(Scene):
    pass

class Orange(Scene):
    pass

class Peal(Scene):
    pass

class Death(Scene):
    def enter(self):
        print("You do a great job\n")
        exit(1)
class Finish(Scene):
    def enter(self):
        print("This is finish\n")
        return 'finish'

class Map(object):
    my_map={'apple' : Apple(),
           'banana' : Banana(),
           'orange' : Orange(),
            'peal' : Peal(),
            'death': Death(),
            'finish' : Finish()}
    def __init__(self,start_scene):
        self.start_scene = start_scene
    def next_scene(self,scene_name):
        val = Map.my_map.get(scene_name)
        return val
    def open_scene(self):
        return self.next_scene(self.start_scene)

class Engine(object):
    def __init__(self,map):
        self.map = map
    def play(self):
        open_scene = self.map.open_scene()
        last_scene = self.map.next_scene('finish')
        while(open_scene != last_scene):
         next_scene_name = open_scene.enter()
         open_scene = self.map.next_scene(next_scene_name)

a_map = Map('apple')
engine = Engine(a_map)
engine.play()
