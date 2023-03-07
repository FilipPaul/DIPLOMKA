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


if tableAlreadyExists(ACCES,"fixture_OUTLINE",0):
    SQL_query = "DROP TABLE fixture_OUTLINE"
    ACCES.MultipleWriteQuery(SQL_query,[0])

SQL_query = """
CREATE TABLE fixture_OUTLINE (
    ID AUTOINCREMENT PRIMARY KEY,
    x FLOAT,
    y FLOAT,
    outline_number FLOAT,
    global_outline_number FLOAT,
    PLACEMENT_X FLOAT,
    PLACEMENT_Y FLOAT,
    PLACEMENT_LAST_NUM varchar(255),
    PLACEMENT_INFO varchar(255),
    TYPE_OF_OUTLINE varchar(255),
    section varchar(255)
);
"""
ACCES.MultipleWriteQuery(SQL_query,[0])
ACCES.MultipleUpdateDatabase([0])

if tableAlreadyExists(ACCES,"fixture_KEEPOUTS",0):
    SQL_query = "DROP TABLE fixture_KEEPOUTS"
    ACCES.MultipleWriteQuery(SQL_query,[0])

SQL_query = """
CREATE TABLE fixture_KEEPOUTS (
    ID AUTOINCREMENT PRIMARY KEY,
    x varchar(255),
    y varchar(255),
    global_keepout_number FLOAT,
    keepout_number FLOAT,
    TYPE_OF_KEEPOUT varchar(255),
    section varchar(255)
);
"""

ACCES.MultipleWriteQuery(SQL_query,[0])
ACCES.MultipleUpdateDatabase([0])

if tableAlreadyExists(ACCES,"fixture_TOOLING",0):
    SQL_query = "DROP TABLE fixture_TOOLING"
    ACCES.MultipleWriteQuery(SQL_query,[0])
SQL_query = """
CREATE TABLE fixture_TOOLING (
    ID AUTOINCREMENT PRIMARY KEY,
    NUM1 varchar(255),
    NUM2 varchar(255),
    NUM3 varchar(255),
    section varchar(255)
);
"""

ACCES.MultipleWriteQuery(SQL_query,[0])
ACCES.MultipleUpdateDatabase([0])

if tableAlreadyExists(ACCES,"fixture_Other_PINS_AND_WIRES",0):
    SQL_query = "DROP TABLE fixture_Other_PINS_AND_WIRES"
    ACCES.MultipleWriteQuery(SQL_query,[0])
SQL_query = """
CREATE TABLE fixture_Other_PINS_AND_WIRES (
    ID AUTOINCREMENT PRIMARY KEY,
    TYPE varchar(255),
    PIN_BRC varchar(255),
    PIN_type varchar(255),
    PIN_ADDITIONAL_INFO varchar(255),
    WIRE_FROM varchar(255),
    WIRE_TO varchar(255),
    WIRE_color varchar(255),
    wire_gauge varchar(255),
    wire_last_number varchar(255),
    section varchar(255),
    NODE varchar(255),
    NODE_second_name varchar(255),
    PROBE_name varchar(255),
    PROBE_first_number varchar(255),
    PROBE_second_number varchar(255),
    Probe_description varchar(255)
);
"""
ACCES.MultipleWriteQuery(SQL_query,[0])
ACCES.MultipleUpdateDatabase([0])


def getID(database_name):
    ACCES.MultipleWriteQuery(f"SELECT TOP 1 ID FROM {database_name} ORDER BY ID DESC",[0])
    ID = ACCES.MultipleResultFromQuery([0])
    if ID == []:
        ID = 1
    else:
        ID = ID[0][0] + 1
    return ID

with open(f"{YAML['DATA_FOLDER']}fixture","r") as f:
    lines = f.readlines()
    f.close()


outline_number = 0
keepout_number = 0
global_keepoint_number = 0
global_outline_number = 0
next_line_type = ""
node = ""
node_second_name = ""
section = ""
probe_name = ""
probe_first_number = ""
probe_second_number = ""
probe_description = ""
for line in lines:
    line = line.replace("\n","").strip()
    while "  " in line:
        line = line.replace("  "," ")
    line = line.split(" ")
    print(line)

    if line[0] == "PLACEMENT":
        ID = getID("fixture_OUTLINE")
        x = "NULL"
        y = "NULL"
        placement_x = line[1].replace(";","").replace(",","")
        placement_y = line[2].replace(";","").replace(",","")
        placement_last_num = line[3]
        placement_info = " ".join(line[4:])
        type_of_outline = "PLACEMENT"
        SQL_query = f"INSERT INTO fixture_OUTLINE VALUES ({ID},{x},{y},NULL,NULL,{placement_x},{placement_y},'{placement_last_num}','{placement_info}','{type_of_outline}','{section}');"
        ACCES.MultipleWriteQuery(SQL_query,[0])

    elif line[0] == "OUTLINE":
        global_outline_number += 1
        outline_number = 0
        next_line_type = "OUTLINE"

    
    elif line[0] == "OTHERS":
        section = "OTHERS"
        next_line_type = ""

    elif line[0] == "TOOLING":
        next_line_type = "TOOLING"

    elif line[0] == "END":
        section = "END"
        next_line_type = "END"

    elif line[0] == "BOARD":
        section = " ".join(line[1:])
        next_line_type = ""

    elif line[0] == "NODE":
        next_line_type = ""
        node = line[1]
        if len(line) > 2:
            node_second_name = line[2]

    elif line[0] == "PROBES":
        next_line_type = "PROBES"


    elif line[0] == "KEEPOUT":
        keepout_number = 0
        global_keepoint_number += 1
        next_line_type = "KEEPOUT"

    elif line[0] == "TESTJET":
        section = "TESTJET"
    
    elif line[0] == "PANEL":
        section = "PANEL"

    elif line[0] == "PINS":
        next_line_type = "PINS"

    elif line[0] == "WIRES":
        next_line_type = "WIRES"

    if next_line_type == "KEEPOUT" and len(line) > 1:
        keepout_number += 1
        ID = getID("fixture_KEEPOUTS")
        x = line[0].replace(";","").replace(",","")
        y = line[1].replace(";","").replace(",","")
        type_of_keepout = "KEEPOUT"
        SQL_query = f"INSERT INTO fixture_KEEPOUTS VALUES ({ID},'{x}','{y}',{global_keepoint_number},{keepout_number},'{type_of_keepout}','{section}');"
        ACCES.MultipleWriteQuery(SQL_query,[0])

    elif next_line_type == "OUTLINE" and len(line) > 1:
        outline_number += 1
        ID = getID("fixture_OUTLINE")
        x = line[0].replace(";","").replace(",","")
        y = line[1].replace(";","").replace(",","")
        type_of_outline = "OUTLINE"
        SQL_query = f"INSERT INTO fixture_OUTLINE VALUES ({ID},'{x}','{y}',{outline_number},{global_outline_number},NULL,NULL,NULL,NULL,'{type_of_outline}','{section}');"
        ACCES.MultipleWriteQuery(SQL_query,[0])

    elif next_line_type == "PINS" and len(line) > 1:
        ID = getID("fixture_Other_PINS_AND_WIRES")
        type = "PIN"
        pin_brc = line[0]
        pin_type = line[1]
        pin_additional_info = " ".join(line[2:])
        SQL_query = f"INSERT INTO fixture_Other_PINS_AND_WIRES VALUES ({ID},'{type}','{pin_brc}','{pin_type}','{pin_additional_info}',NULL,NULL,NULL,NULL,NULL,'{section}','{node}','{node_second_name}',NULL,NULL,NULL,NULL);"
        ACCES.MultipleWriteQuery(SQL_query,[0])
    
    elif next_line_type == "WIRES" and len(line) > 1:
        ID = getID("fixture_Other_PINS_AND_WIRES")
        type = "WIRE"
        wire_from = line[0]
        wire_to = line[2]
        wire_color = line[3]
        wire_gauge = line[4]
        wire_last_number = line[5]
        SQL_query = f"INSERT INTO fixture_Other_PINS_AND_WIRES VALUES ({ID},'{type}',NULL,NULL,NULL,'{wire_from}','{wire_to}','{wire_color}','{wire_gauge}','{wire_last_number}','{section}','{node}','{node_second_name}',NULL,NULL,NULL,NULL);"
        ACCES.MultipleWriteQuery(SQL_query,[0])

    elif next_line_type == "PROBES" and len(line) > 1:
        ID = getID("fixture_Other_PINS_AND_WIRES")
        probe_name = line[0]
        probe_first_number = line[1]
        probe_second_number = line[2]
        probe_description = " ".join(line[3:])
        type_of_probe = "PROBE"
        SQL_query = f"INSERT INTO fixture_Other_PINS_AND_WIRES VALUES ({ID},'{type_of_probe}',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'{section}','{node}','{node_second_name}','{probe_name}','{probe_first_number}','{probe_second_number}','{probe_description}');"
        ACCES.MultipleWriteQuery(SQL_query,[0])

    elif next_line_type == "TOOLING" and len(line) > 1:
        ID = getID("fixture_TOOLING")
        NUM1 = line[0]
        NUM2 = line[1]
        NUM3 = line[2]
        SQL_query = f"INSERT INTO fixture_TOOLING VALUES ({ID},'{NUM1}','{NUM2}','{NUM3}','{section}');"        
        ACCES.MultipleWriteQuery(SQL_query,[0])

#SQL_query = """
#CREATE TABLE fixture_Other_PINS_AND_WIRES (
#    ID AUTOINCREMENT PRIMARY KEY,
#    TYPE varchar(255),
#    PIN_BRC varchar(255),
#    PIN_type varchar(255),
#    PIN_ADDITIONAL_INFO varchar(255),
#    WIRE_FROM varchar(255),
#    WIRE_TO varchar(255),
#    WIRE_color varchar(255),
#    wire_gauge varchar(255),
#    wire_last_number varchar(255),
#    NODE varchar(255),
#    NODE_second_name varchar(255)
#);
#"""

ACCES.MultipleUpdateDatabase([0])
