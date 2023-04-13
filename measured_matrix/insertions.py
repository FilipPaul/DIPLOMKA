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
    
class Insertion():
    def __init__(self, b,r,c,X,Y,Type,Spring,NodeName,OnDevice,ID):
        self.b = b
        self.r = r
        self.c = c
        self.X = X
        self.Y = Y
        self.Type = Type
        self.Spring = Spring
        self.NodeName = NodeName
        self.OnDevice = OnDevice
        self.ID = ID

    def printAll(self):
        print(f"ID: {self.ID};b: {self.b}; r: {self.r}; c: {self.c}; X: {self.X}; Y: {self.Y}; Type: {self.Type}; Spring: {self.Spring}; NodeName: {self.NodeName}; OnDevice: {self.OnDevice}")
    
    def insertInDb(self,cursor:pyodbc.Cursor):
        cursor.execute("CREATE TABLE IF NOT EXISTS Insertions (b TEXT, r TEXT, c TEXT, X TEXT, Y TEXT, Type TEXT, Spring TEXT, NodeName TEXT, OnDevice TEXT, ID INT UNIQUE PRIMARY KEY)")
        cursor.execute(f"INSERT INTO Insertions (b,r,c,X,Y,Type,Spring,NodeName,OnDevice,ID) VALUES ('{self.b}','{self.r}','{self.c}','{self.X}','{self.Y}','{self.Type}','{self.Spring}','{self.NodeName}','{self.OnDevice}',{self.ID})")
        #print(f"INSERT INTO Insertions (b,r,c,X,Y,Type,Spring,NodeName,OnDevice,ID) VALUES ('{self.b}','{self.r}','{self.c}','{self.X}','{self.Y}','{self.Type}','{self.Spring}','{self.NodeName}','{self.OnDevice}',{self.ID})")

    def loadDataFromTable(self,cursor:pyodbc.Cursor, ID):
        cursor.execute("SELECT * FROM Insertions WHERE ID = ?",ID)
        row = cursor.fetchone()
        if row is None:
            return
        print(row)
        self.b = row[0]
        self.r = row[1]
        self.c = row[2]
        self.X = row[3]
        self.Y = row[4]
        self.Type = row[5]
        self.Spring = row[6]
        self.NodeName = row[7]
        self.OnDevice = row[8]
        self.ID = row[9]

def parseInsertion(path_to_file= "original_files/inserts") -> List[Insertion]:

    with open(path_to_file, "r") as f:
        insertions = f.read()

    insertions = insertions.splitlines()
    list_of_insertions: List[str] = []
    for inserts in insertions:
        try:
            if inserts[1].isnumeric():
                list_of_insertions.append(inserts)
        except Exception as e: #line is shorter than 2 characters
            ...

    final_list_of_insertions: List[Insertion] = []

    for ID,inserts in enumerate(list_of_insertions):
        if "Tooling" in inserts and "(" in inserts:
            pin_type = "Tooling"
            spring = None
            while "  " in inserts:
                inserts = inserts.replace("  ", " ")
            inserts = inserts.strip().replace("(", "").replace(")", "").split(" ")
            b = inserts[0]
            r = inserts[1]
            c = inserts[2]
            X = inserts[3]
            Y = inserts[4]
            NodeName = None
            OnDevice = None
            final_list_of_insertions.append(Insertion(b,r,c,X,Y,pin_type,spring,NodeName,OnDevice,ID))


        elif "Pin" in inserts and "(" in inserts:
            pin_type = "Pin"
            spring = None
            while "  " in inserts:
                inserts = inserts.replace("  ", " ")
            inserts = inserts.strip().replace("(", "").replace(")", "").split(" ")
            b = inserts[0]
            r = inserts[1]
            c = inserts[2]
            X = inserts[3]
            Y = inserts[4]
            NodeName = " ".join(inserts[6:])
            OnDevice = None
            final_list_of_insertions.append(Insertion(b,r,c,X,Y,pin_type,spring,NodeName,OnDevice,ID))

        elif "Offset" in inserts and "*" in inserts:
            pin_type = "Offset Pin"
            spring = None
            while "  " in inserts:
                inserts = inserts.replace("  ", " ")
            inserts = inserts.strip().replace("*", "").split(" ")
            b = inserts[0]
            r = inserts[1]
            c = inserts[2]
            X = inserts[3]
            Y = inserts[4]
            NodeName = None
            OnDevice = None
            final_list_of_insertions.append(Insertion(b,r,c,X,Y,pin_type,spring,NodeName,OnDevice,ID))
        
        elif " mil" in inserts and "[" in inserts:
            while "  " in inserts:
                inserts = inserts.replace("  ", " ")
            inserts = inserts.strip().replace("[", "").replace("]", "").split(" ")
            b = inserts[0]
            r = inserts[1]
            c = inserts[2]
            X = inserts[3]
            Y = inserts[4]
            pin_type = " ".join(inserts[5:7])
            spring = " ".join(inserts[7:9])
            NodeName = " ".join(inserts[9:-1])
            OnDevice = inserts[-1]
            final_list_of_insertions.append(Insertion(b,r,c,X,Y,pin_type,spring,NodeName,OnDevice,ID))
        else:
            print(f"ERROR: {inserts}")
            continue

    return final_list_of_insertions

def storeInsertionsInDatabase(cursor:pyodbc.Cursor, final_list_of_insertions:List[Insertion]):
    cursor.execute("DROP TABLE IF EXISTS Insertions")
    for insertion in final_list_of_insertions:
        insertion.insertInDb(cursor)
    connection.commit()
    return final_list_of_insertions

def loadInsertionsFromDatabase(cursor:pyodbc.Cursor, query:str = "SELECT * FROM Insertions") -> List[Insertion]:
    cursor.execute(query)
    rows = cursor.fetchall()
    list_of_insertions = []
    for row in rows:
        new_data = Insertion(row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9])
        list_of_insertions.append(new_data)
    return list_of_insertions

if __name__ == "__main__":
    list_of_insertions = parseInsertion(path_to_file= "1793_1796/inserts")
    storeInsertionsInDatabase(cursor, list_of_insertions)

    insertions = loadInsertionsFromDatabase(cursor)
    for insertion in insertions:
        insertion.printAll()