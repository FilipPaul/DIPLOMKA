import pyodbc
connection = pyodbc.connect('Driver={MySQL ODBC 8.0 Unicode Driver};'
                            'SERVER = 127.0.0.1;'
                            'DATABASE = test;'
                            'UID = root;'
                            'PASSWORD = 445a2dB912!;'
                            'PORT = 3306;'
)   

cursor = connection.cursor()

query = """CREATE TABLE IF NOT EXISTS test.AllConnections(
            ConnectionID INT NOT NULL AUTO_INCREMENT,
            RefConnectionFrom INT NULL,
            RefConnectionTo INT NULL,
            WireLength FLOAT NULL,
            WireAWG FLOAT NULL,
            WireColor VARCHAR(45) NULL,
            PRIMARY KEY (ConnectionID));
            """
cursor.execute(query)

query = """CREATE TABLE IF NOT EXISTS test.NetTable(
            NetID INT NOT NULL AUTO_INCREMENT,
            NetName VARCHAR(45) NULL,
            NumberOfConnectionsInNet INT NULL,
            PRIMARY KEY (NetID));
            """
cursor.execute(query)

query = """CREATE TABLE IF NOT EXISTS test.PinInfoTable(
            PinID INT NOT NULL AUTO_INCREMENT,
            ShouldBePinState1TO40 TINYINT NULL,
            MeasuredPinState1to40 TINYINT NULL,
            ShouldBePinState41to80 TINYINT NULL,
            MeasuredPinState41to80 TINYINT NULL,
            PinType VARCHAR(45) NULL,
            PinXPosition FLOAT NULL,
            PinYPosition FLOAT NULL,
            PinRow FLOAT NULL,
            PinColumn FLOAT NULL,
            PinB FLOAT NULL,
            TotalNumberOfWiresAttachedToPin INT NULL,
            RefToNetIDInNetTable INT NULL,
            PRIMARY KEY (PinID));
            """
cursor.execute(query)
query = """CREATE TABLE IF NOT EXISTS test.testTable (
            PinNumber INT NOT NULL AUTO_INCREMENT,"""

for i in range(1, 51):
    query += f"Row{i}ShouldBePinState1TO40 TINYINT NULL,"
    query += f"Row{i}MeasuredPinState1to40 TINYINT NULL,"
    query += f"Row{i}ShouldBePinState41to80 TINYINT NULL,"
    query += f"Row{i}MeasuredPinState41to80 TINYINT NULL,"
    query += f"Row{i}pinVoltage1TO40 FLOAT NULL,"
    query += f"Row{i}pinVoltage1TO80 FLOAT NULL,"

query +=    """
            RefToPinIDInInfoTable INT NULL,
            PRIMARY KEY (PinNumber));"""

cursor.execute(query)

cursor.execute("SHOW TABLES")
print(cursor.fetchall())
cursor.commit()

