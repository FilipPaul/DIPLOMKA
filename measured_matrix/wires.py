from typing import List
import pyodbc
connection = pyodbc.connect('Driver={MySQL ODBC 8.0 Unicode Driver};'
                            'SERVER = 127.0.0.1;'
                            'DATABASE = test;'
                            'UID = root;'
                            'PASSWORD = 445a2dB912!;'
                            'PORT = 3306;'
)
cursor = connection.cursor()

class Wire():
    def __init__(self, Length,Ga,Color,b_from,r_from,c_from,b_to,r_to,c_to,x_from,y_from,x_to,y_to,from_type,to_type,ID):
        self.Length = Length
        self.Ga = Ga
        self.Color = Color
        self.b_from = b_from
        self.r_from = r_from
        self.c_from = c_from
        self.b_to = b_to
        self.r_to = r_to
        self.c_to = c_to
        self.x_from = x_from
        self.y_from = y_from
        self.x_to = x_to
        self.y_to = y_to
        self.from_type = from_type
        self.to_type = to_type
        self.ID = ID
    
    def printAll(self):
        print(f"ID: {self.ID};Length: {self.Length}; Ga: {self.Ga}; Color: {self.Color}; b_from: {self.b_from}; r_from: {self.r_from}; c_from: {self.c_from}; b_to: {self.b_to}; r_to: {self.r_to}; c_to: {self.c_to}; x_from: {self.x_from}; y_from: {self.y_from}; x_to: {self.x_to}; y_to: {self.y_to}; from_type: {self.from_type}; to_type: {self.to_type}")

    def insertInDb(self,cursor:pyodbc.Cursor):
        cursor.execute("CREATE TABLE IF NOT EXISTS Wires (Length TEXT, Ga TEXT, Color TEXT, b_from TEXT, r_from TEXT, c_from TEXT, b_to TEXT, r_to TEXT, c_to TEXT, x_from TEXT, y_from TEXT, x_to TEXT, y_to TEXT, from_type TEXT, to_type TEXT, ID INT UNIQUE PRIMARY KEY)")
        cursor.execute(f"INSERT INTO Wires (Length,Ga,Color,b_from,r_from,c_from,b_to,r_to,c_to,x_from,y_from,x_to,y_to,from_type,to_type, ID) VALUES ('{self.Length}','{self.Ga}','{self.Color}','{self.b_from}','{self.r_from}','{self.c_from}','{self.b_to}','{self.r_to}','{self.c_to}','{self.x_from}','{self.y_from}','{self.x_to}','{self.y_to}','{self.from_type}','{self.to_type}',{self.ID})")
        #print(f"INSERT INTO Wires (Length,Ga,Color,b_from,r_from,c_from,b_to,r_to,c_to,x_from,y_from,x_to,y_to,from_type,to_type, ID) VALUES ('{self.Length}','{self.Ga}','{self.Color}','{self.b_from}','{self.r_from}','{self.c_from}','{self.b_to}','{self.r_to}','{self.c_to}','{self.x_from}','{self.y_from}','{self.x_to}','{self.y_to}','{self.from_type}','{self.to_type}',{self.ID})")
    def loadDataFromDb(self,cursor:pyodbc.Cursor, ID:int):
        cursor.execute("SELECT * FROM Wires WHERE ID = ?",ID)
        row = cursor.fetchone()
        if row is None:
            return
        
        self.Length = row[0]
        self.Ga = row[1]
        self.Color = row[2]
        self.b_from = row[3]
        self.r_from = row[4]
        self.c_from = row[5]
        self.b_to = row[6]
        self.r_to = row[7]
        self.c_to = row[8]
        self.x_from = row[9]
        self.y_from = row[10]
        self.x_to = row[11]
        self.y_to = row[12]
        self.from_type = row[13]
        self.to_type = row[14]
        self.ID = row[15]

def parseWires(path_to_file= "original_files/wires") -> List[Wire]:

    with open(path_to_file, "r") as f:
        wires = f.read()

    while("  " in wires):
        wires = wires.replace("  ", " ")

    list_of_wires: List[str] = []
    lines = wires.splitlines()
    for index,line in enumerate(lines):
        line = line.strip()
        try:
            if line[0].isnumeric():
                list_of_wires.append(line)
        except Exception as e: # if line is empty
            ...


    final_list_of_wires: List[Wire] = []
    for ID,wire in enumerate(list_of_wires):
        length = wire.split(" ")[0]
        ga = wire.split(" ")[1]
        color = wire.split(" ")[2]
        if "(" in wire.split(" ")[3]:
            from_type = "pin"
            b_from = wire.replace("(", "").replace(")", "").split(" ")[3]
            r_from = wire.replace("(", "").replace(")", "").split(" ")[4]
            c_from = wire.replace("(", "").replace(")", "").split(" ")[5]

        elif "[" in wire.split(" ")[3]:
            from_type = "probe"
            b_from = wire.replace("[", "").replace("]", "").split(" ")[3]
            r_from = wire.replace("[", "").replace("]", "").split(" ")[4]
            c_from = wire.replace("[", "").replace("]", "").split(" ")[5]
        else:
            from_type = "unknown"
            print("ERROR: unknown from_type", wire)
            continue

        if "(" in wire.split(" ")[6]:
            to_type = "pin"
            b_to = wire.replace("(", "").replace(")", "").split(" ")[6]
            r_to = wire.replace("(", "").replace(")", "").split(" ")[7]
            c_to = wire.replace("(", "").replace(")", "").split(" ")[8]

        elif "[" in wire.split(" ")[6]:
            to_type = "probe"
            b_to = wire.replace("[", "").replace("]", "").split(" ")[6]
            r_to = wire.replace("[", "").replace("]", "").split(" ")[7]
            c_to = wire.replace("[", "").replace("]", "").split(" ")[8]    
        else:
            from_type = "unknown"
            print("ERROR: unknown to_type", wire)
            continue

        x_from = wire.split(" ")[9]
        y_from = wire.split(" ")[10]
        x_to = wire.split(" ")[11]
        y_to = wire.split(" ")[12]

        final_list_of_wires.append(Wire(length,ga,color,b_from,r_from,c_from,b_to,r_to,c_to,x_from,y_from,x_to,y_to,from_type,to_type,ID))
    return final_list_of_wires
    
def storeWiresInDb(cursor:pyodbc.Cursor, final_list_of_wires:List[Wire]):
    cursor.execute("DROP TABLE IF EXISTS Wires")
    for wire in final_list_of_wires:
        #wire.printAll()
        wire.insertInDb(cursor)
    cursor.commit()

def loadWiresFromDb(cursor:pyodbc.Cursor,query:str = "SELECT * FROM Wires") -> List[Wire]:
    cursor.execute(query)
    rows = cursor.fetchall()
    list_of_wires = []
    for row in rows:
        new_data = Wire(row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10],row[11],row[12],row[13],row[14],row[15])
        list_of_wires.append(new_data)
    return list_of_wires


if __name__ == "__main__":
    
    storeWiresInDb(cursor, parseWires(path_to_file="1793_1796/wires"))
    wires = loadWiresFromDb(cursor)
    for wire in wires:
        wire.printAll()