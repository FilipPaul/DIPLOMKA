from typing import List
import pprint as pp

with open("original_files/fixture", "r") as f:
    fixture = f.read()

class Node:
    def __init__(self, indented_line):
        self.children = []
        self.level = (len(indented_line) - len(indented_line.lstrip()))/2
        self.text = indented_line.strip()

    def add_children(self, nodes):
        childlevel = nodes[0].level
        while nodes:
            node = nodes.pop(0)
            if node.level == childlevel: # add node as a child
                self.children.append(node)
            elif node.level > childlevel: # add nodes as grandchildren of the last child
                nodes.insert(0,node)
                self.children[-1].add_children(nodes)
            elif node.level <= self.level: # this node is a sibling, no more children
                nodes.insert(0,node)
                return

    def as_dict(self):
        if len(self.children) > 1:
            return {self.text: [node.as_dict() for node in self.children]}
        elif len(self.children) == 1:
            return {self.text: self.children[0].as_dict()}
        else:
            return self.text
        
    
root = Node('root')
root.add_children([Node(line) for line in fixture.splitlines() if line.strip()])
d = root.as_dict()

def findAllDictionariesWithKeyInList(list_of_dicts,str_key):
    list_of_dicts_with_same_key = []
    list_of_exact_key_matches = []
    for d in list_of_dicts:
        #print(d)
        if type(d) == dict:
            for keys in d:
                if str_key in keys:
                    list_of_dicts_with_same_key.append(d[keys])
                    list_of_exact_key_matches.append(keys)
    
    return list_of_dicts_with_same_key, list_of_exact_key_matches
 
options,_= findAllDictionariesWithKeyInList(d['root'],'OPTIONS')
#print(options)
panel,panel_name= findAllDictionariesWithKeyInList(options[0],'PANEL')
print(panel_name)
boards,_= findAllDictionariesWithKeyInList(panel[0],'BOARD')

for board in boards:
    node_info,node_name = findAllDictionariesWithKeyInList(board,'NODE')
    for index,node in enumerate(node_info):
        print(node_name[index])
        print(node)


keepout = findAllDictionariesWithKeyInList(panel[0],'KEEPOUT')
#print(pins)
