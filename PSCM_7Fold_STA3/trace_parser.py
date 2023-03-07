from dataclasses import replace
from AutomateSuperPackage.AutomateSuperModule import DatabaseClass
import yaml

config_file_path = "config.yaml"
with open(config_file_path, 'r') as f:
    YAML = yaml.safe_load(f)
ACCES = DatabaseClass().AccesDatabase
ACCES.multipleCursors([YAML["DATABASE"]]),

def getResult(Query):
    ACCES.MultipleWriteQuery(Query,[0])
    return ACCES.MultipleResultFromQuery([0])


def tableAlreadyExists(ACDB,table,cursor_index):
    for rows in ACDB.cursors[cursor_index].tables():
        if rows[2] == table:
            return 1 #table already exists
    return 0 #Table doesnt exists

if tableAlreadyExists(ACCES,"trace",0):
    SQL_query = "DROP TABLE trace"
    ACCES.MultipleWriteQuery(SQL_query,[0])

SQL_query = """
CREATE TABLE trace (
    ID AUTOINCREMENT PRIMARY KEY,  
    length FLOAT,  
    Gauge FLOAT,  
    Color varchar(255),  
    b_from FLOAT,  
    r_from FLOAT,  
    c_from FLOAT,  
    trace_from_net varchar(255),  
    type_from varchar(255),  
    b_to FLOAT,  
    r_to FLOAT,  
    c_to FLOAT,  
    trace_to_net varchar(255),  
    type_to varchar(255),    
    Node_name varchar(255),  
    OnDevice varchar(255),
    total_number_of_wires FLOAT,  
    current_number_of_wires FLOAT,  
    Use varchar(255)
);
"""

ACCES.MultipleWriteQuery(SQL_query,[0])
ACCES.MultipleUpdateDatabase([0])

with open("original_files/trace", "r") as f:
    lines = f.readlines()
    f.close()

print("OK")
class Trace_pins:
    def __init__(self,trace_length,trace_gauge,trace_color,trace_b_from,trace_r_from,trace_c_from,trace_from_net,trace_type_from,
    trace_b_to,trace_r_to,trace_c_to,trace_to_net,trace_type_to,node_name,OnDevice,curent_number_of_wires,total_number_of_wires,use):
        self.trace_length = trace_length
        self.trace_gauge = trace_gauge
        self.trace_color = trace_color
        self.trace_b_from = trace_b_from
        self.trace_r_from = trace_r_from
        self.trace_c_from = trace_c_from
        self.trace_from_net = trace_from_net
        self.trace_type_from = trace_type_from
        self.trace_b_to = trace_b_to
        self.trace_r_to = trace_r_to
        self.trace_c_to = trace_c_to
        self.trace_to_net = trace_to_net
        self.trace_type_to = trace_type_to
        self.node_name = node_name
        self.OnDevice = OnDevice
        self.total_number_of_wires = total_number_of_wires
        self.curent_number_of_wires = curent_number_of_wires
        self.use = use
    
    def updateDatabese(self):
            ACCES.MultipleWriteQuery("SELECT TOP 1 ID FROM trace ORDER BY ID DESC",[0])
            ID = ACCES.MultipleResultFromQuery([0])
            if ID == []:
                ID = 1
            else:
                ID = ID[0][0] + 1
            SQL = f"INSERT INTO trace VALUES ({ID},{self.trace_length},{self.trace_gauge},'{self.trace_color}',{self.trace_b_from},{self.trace_r_from},{self.trace_c_from},'{self.trace_from_net}','{self.trace_type_from}',{self.trace_b_to},{self.trace_r_to},{self.trace_c_to},'{self.trace_to_net}','{self.trace_type_to}','{self.node_name}','{self.OnDevice}',{self.total_number_of_wires},{self.curent_number_of_wires},'{self.use}')"
            #print(SQL)
            ACCES.MultipleWriteQuery(SQL,[0])
            ACCES.MultipleUpdateDatabase([0])


save_line = ""
number_of_wires = 0
list_of_traces = []
ignore_flag = 1 #ignore header lines
for line_cnt,line in enumerate(lines):
    if "Node Name" in line and '"Node Name"' not in line:
        ignore_flag = 0

    if ignore_flag == 0:
        if "Node Name" in line:
            line = line.replace("-","").replace("Node Name","").replace("\n","").strip()
            while "  " in line:
                line = line.replace("  "," ")
            line = line.split(" ")
            board_name = line[0]
            if len(line) == 2:
                Node_name = line[1]
            else:
                Node_name = line[0]
            OnDevice = ""
        
        elif "Probe" in line:
            if ":" in line:
                OnDevice = line[line.find(":")+1:].strip().replace("\n","")
            else:
                OnDevice = ""
                to_type = line.replace("\n","").strip().split(" ")[-1]
            
            



        elif "Wire" in line:
            line = line[line.find("Color:")+1:].strip().replace("\n"," ")
            while "  " in line:
                line = line.replace("  "," ")
            color = line.split(" ")[1]
            gauge = line.split(" ")[3]
        
        elif "Path" in line:
            save_line = ""
            multiline = 0
            while "Use" not in lines[line_cnt+multiline]:
                save_line += lines[line_cnt+multiline].replace("\n"," ")
                multiline += 1
            
            total_number_of_wires = save_line.count("[") + save_line.count("(") - 1+ save_line.count("<00>")
        
        elif "Use" in line:
            while "  " in line:
                line = line.replace("  "," ")
            line = line.replace("\n","").strip().split(" ")
            if len(line) >= 2:
                Use = " ".join(line[1:])
            else:
                Use = ""

            save_line = save_line.replace("Path","").replace("\n","").strip()
            while "  " in save_line:
                save_line = save_line.replace("  "," ")
            save_line = save_line.replace("<","").replace(">","").split(" ")

            if len(save_line) > 13:
                print(save_line)

            for i in range(total_number_of_wires):
                current_number_of_wires = i+1
                if "(" in save_line[4*i]:
                    from_type = "PIN"
                elif "[" in save_line[4*i]:
                    from_type = "PROBE"
                b_from = save_line[4*i].replace("[","").replace("(","")
                r_from = save_line[4*i+1]
                c_from = save_line[4*i+2].replace("]","").replace(")","")
                length = save_line[4*i+3]
                trace_from_net = ""
                if "(" in save_line[4*i+4]:
                    to_type = "PIN"
                elif "[" in save_line[4*i+4]:
                    to_type = "PROBE"
                if  int(length) != 0:
                    b_to = save_line[4*i+4].replace("[","").replace("(","")
                    r_to = save_line[4*i+5]
                    c_to = save_line[4*i+6].replace("]","").replace(")","")
                    trace_to_net = ""

                else:
                    b_to = "NULL"
                    r_to = "NULL"
                    c_to = "NULL"
                    trace_to_net = save_line[4*i+4]


                trace_pin = Trace_pins(length,gauge,color,b_from,r_from,c_from,trace_from_net,from_type,
                        b_to,r_to,c_to,trace_to_net,to_type,Node_name,OnDevice,current_number_of_wires,total_number_of_wires,Use)

                list_of_traces.append(trace_pin)
    

for traces in list_of_traces:
    traces.updateDatabese()


