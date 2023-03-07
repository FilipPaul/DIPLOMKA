from typing import List
from AutomateSuperPackage.AutomateSuperModule import DatabaseClass
import yaml
config_file_path = R"C:\Users\Filip\Desktop\diplomka\PSCM_7Fold_STA3\config.yaml"
with open(config_file_path, 'r') as f:
    YAML = yaml.safe_load(f)
ACCES = DatabaseClass().AccesDatabase
ACCES.multipleCursors([YAML["DATABASE"]])
def tableAlreadyExists(ACDB,table,cursor_index):
    for rows in ACDB.cursors[cursor_index].tables():
        if rows[2] == table:
            return 1 #table already exists
    return 0 #Table doesnt exists

class InsertPin:
    def __init__(self,b,row,column,X,Y,Type,Spring,Node,On_device):
        self.b = b
        self.row = row
        self.column = column
        self.X = X
        self.Y = Y
        self.Type = Type
        self.Spring = Spring
        self.Node = Node
        self.On_device = On_device
    
    def updateDatabese(self):
        ACCES.MultipleWriteQuery("SELECT TOP 1 ID FROM inserts ORDER BY ID DESC",[0])
        ID = ACCES.MultipleResultFromQuery([0])
        if ID == []:
            ID = 1
        else:
            ID = ID[0][0] + 1
        SQL = f"INSERT INTO inserts VALUES ({ID},{self.b},{self.row},{self.column},{self.X},{self.Y},'{self.Type}','{self.Spring}','{self.Node}','{self.On_device}')"
        #print(SQL)
        ACCES.MultipleWriteQuery(SQL,[0])
        ACCES.MultipleUpdateDatabase([0])

if tableAlreadyExists(ACCES,"inserts",0):
    SQL_query = "DROP TABLE inserts"
    ACCES.MultipleWriteQuery(SQL_query,[0])

SQL_query = """
CREATE TABLE inserts (
    ID AUTOINCREMENT PRIMARY KEY,
    b FLOAT,
    r FLOAT,
    c FLOAT,
    X FLOAT,
    Y FLOAT,
    type varchar(255),
    Spring varchar(255),
    Node varchar(255),
    onDevice varchar(255)
);
"""
ACCES.MultipleWriteQuery(SQL_query,[0])


ACCES.MultipleUpdateDatabase([0])

def make_patern(line:str):
    separator_positions = []
    i = 0
    for chars in line:
        if chars == "|":
            separator_positions.append(i)
        i += 1
    return separator_positions

def parsebyPattern(line:str,patern:list):
    parsed = []
    parsed.append(line[:patern[0]])
    for i in range(len(patern)-2):
        parsed.append(line[patern[i]+1:patern[i+1]])


    for i in range(len(parsed)):
        while "  " in parsed[i]:
            parsed[i] = parsed[i].replace("  "," ")
        parsed[i] = parsed[i].strip()
    brc = parsed[0].split(" ")
    b = brc[0][1:] #remove bracket
    r = brc[1]
    c = brc[2][:-1] #remove bracket

    xy = parsed[1].split(" ")
    x = xy[0]
    y = xy[1]

    Type = parsed[2]
    Spring = parsed[3]
    node_names_count = line.count("%")
    
    node = ""
    On_device = ""
    cpy_of_line = line
    while "  " in cpy_of_line:
        cpy_of_line = cpy_of_line.replace("  "," ")

    print(pattern)
    print(line[pattern[3]:pattern[4]])
    if node_names_count == 2:
        node = cpy_of_line.strip().split(" ")[-2]
        On_device = cpy_of_line.strip().split(" ")[-1].replace("\n","")
    elif node_names_count == 1:
        node = cpy_of_line.strip().split(" ")[-1].replace("\n","")
    
    else:
        node = line[pattern[3]:pattern[4]].strip()
        print(line[pattern[3]:pattern[4]].strip())

    return b,r,c,x,y,Type,Spring,node,On_device


    

with open(f"{YAML['DATA_FOLDER']}inserts","r") as inserts_file:
    inserts = inserts_file.readlines()
    inserts_file.close()

next_line_is_header_flag = 0
list_of_insert_pins:List[InsertPin] = []
for line in inserts:
    if next_line_is_header_flag == 1:
        pattern = make_patern(line)
        next_line_is_header_flag = 0

    elif line[:2] == "(b": #line is header -> take pattern
        next_line_is_header_flag = 1
       
    elif (line[0] == "(" or line[0] == "["):
        list_of_insert_pins.append(InsertPin(*parsebyPattern(line,pattern)))

    elif (line[0] == "*"):
        list_of_insert_pins.append(InsertPin(*parsebyPattern(line,pattern)))

for pin in list_of_insert_pins:
    pin.updateDatabese()

