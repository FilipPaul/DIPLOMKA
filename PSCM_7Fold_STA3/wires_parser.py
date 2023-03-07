from typing import List
from AutomateSuperPackage.AutomateSuperModule import DatabaseClass
import yaml
config_file_path = "config.yaml"
with open(config_file_path, 'r') as f:
    YAML = yaml.safe_load(f)
ACCES = DatabaseClass().AccesDatabase
ACCES.multipleCursors([YAML["DATABASE"]])
def tableAlreadyExists(ACDB,table,cursor_index):
    for rows in ACDB.cursors[cursor_index].tables():
        if rows[2] == table:
            return 1 #table already exists
    return 0 #Table doesnt exists

class Wires:
    def __init__(self,length,Ga,Color,b_from,row_from,column_from,type_from,b_to,
    row_to,column_to,type_to,X_from,Y_from,X_to,Y_to,from_net_name = "", to_net_name = ""):
        self.length = length
        self.Ga = Ga
        self.Color = Color
        self.b_from = b_from
        self.row_from = row_from
        self.column_from = column_from
        self.type_from = type_from
        self.b_to = b_to
        self.row_to = row_to
        self.column_to = column_to
        self.type_to = type_to
        self.X_from = X_from
        self.Y_from = Y_from
        self.X_to = X_to
        self.Y_to = Y_to
        self.from_net_name = from_net_name
        self.to_net_name = to_net_name
    
    def updateDatabese(self):
        ACCES.MultipleWriteQuery("SELECT TOP 1 ID FROM wires ORDER BY ID DESC",[0])
        ID = ACCES.MultipleResultFromQuery([0])
        if ID == []:
            ID = 1
        else:
            ID = ID[0][0] + 1
        SQL = f"INSERT INTO wires VALUES ({ID},{self.length},{self.Ga},'{self.Color}',{self.b_from},{self.row_from},{self.column_from},'{self.type_from}',{self.b_to},{self.row_to},{self.column_to},'{self.type_to}',{self.X_from},{self.Y_from},{self.X_to},{self.Y_to},'{self.from_net_name}','{self.to_net_name}')"
        print(SQL)
        ACCES.MultipleWriteQuery(SQL,[0])
        ACCES.MultipleUpdateDatabase([0])

if tableAlreadyExists(ACCES,"wires",0):
    SQL_query = "DROP TABLE wires"
    ACCES.MultipleWriteQuery(SQL_query,[0])

SQL_query = """
CREATE TABLE wires (
    ID AUTOINCREMENT PRIMARY KEY,
    length FLOAT,
    Ga FLOAT,
    Color varchar(255),
    b_from FLOAT,
    r_from FLOAT,
    c_from FLOAT,
    type_from varchar(255),
    b_to FLOAT,
    r_to FLOAT,
    c_to FLOAT,
    type_to varchar(255),
    X_from FLOAT,
    Y_from FLOAT,
    X_to FLOAT,
    Y_to FLOAT,
    net_name_from varchar(255),
    net_name_to varchar(255)
);
"""
ACCES.MultipleWriteQuery(SQL_query,[0])


ACCES.MultipleUpdateDatabase([0])

def parseWires(line):
    from_net_name = ""
    to_net_name = ""
    while "  " in line:
        line = line.replace("  "," ")
    #print(line)
    line = line.split(" ")
    if line[0] == "0": #for debug
        #print(line)
        ...
    length = line[0]
    Ga = line[1]
    Color = line[2]
    subtract_flag = 0
    #print(line[3])
    if "(" in line[3]:
        from_type = "PIN"
        b_from = line[3].replace("(","")
        row_from = line[4]
        column_from = line[5].replace(")","")
    elif "[" in line[3]:
        from_type = "PROBE"
        b_from = line[3].replace("[","")
        row_from = line[4]
        column_from = line[5].replace("]","")
    else:
        from_type = "NODE"
        b_from = "NULL"
        row_from = "NULL"
        column_from = "NULL"
        from_net_name = line[3]
        subtract_flag = 2

    #print(line[5-subtract_flag])
    if "(" in line[6-subtract_flag]:
        to_type = "PIN"
        b_to = line[6-subtract_flag].replace("(","")
        row_to = line[7-subtract_flag]
        column_to = line[8-subtract_flag].replace(")","")
    elif "[" in line[6-subtract_flag]:
        to_type = "PROBE"
        b_to = line[6-subtract_flag].replace("[","")
        row_to = line[7-subtract_flag]
        column_to = line[8-subtract_flag].replace("]","")
    else:
        to_type = "NODE"
        b_to = "NULL"
        row_to = "NULL"
        column_to = "NULL"
        to_net_name = line[6-subtract_flag]
        subtract_flag += 2

    X_from = line[9-subtract_flag]
    Y_from = line[10-subtract_flag]
    X_to = line[11-subtract_flag]
    Y_to = line[12-subtract_flag]
    
    wire = Wires(length,Ga,Color,b_from,row_from,column_from,from_type,b_to,row_to,column_to,to_type,X_from,Y_from,X_to,Y_to)
    wire.to_net_name = to_net_name
    wire.from_net_name = from_net_name
    wire.updateDatabese()
    return wire
    


with open(f"{YAML['DATA_FOLDER']}wires","r") as wires_file:
    wires = wires_file.readlines()
    wires_file.close()

list_of_wires:List[Wires] = []
for line in wires:
    line = line.strip()
    
    if line.split(" ")[0].isdecimal():
        list_of_wires.append(parseWires(line))
