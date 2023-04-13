from PyQt6 import QtCore, QtGui, QtWidgets
import numpy as np
from pinInforGUI import Ui_Form as PIN_INFO_UI
from controlGUI import Ui_Form as CONTROL_UI

from typing import List
import pyodbc
connection = pyodbc.connect('Driver={MySQL ODBC 8.0 Unicode Driver};'
                            'SERVER = 127.0.0.1;'
                            'DATABASE = test;'
                            'UID = root;'
                            'PASSWORD = 445a2dB912!;'
                            'PORT = 3306;'
)

dBCursor = connection.cursor()

from wires import Wire, loadWiresFromDb, parseWires,storeWiresInDb
from insertions import Insertion, loadInsertionsFromDatabase, parseInsertion, storeInsertionsInDatabase

class button(QtWidgets.QPushButton):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.setStyleSheet("font-size: 8px; font-weight:bold;")
        #self.setGeometry(QtCore.QRect(0, 0, 10, 10))
        self.row = 0
        self.column = 0
        self.value = 0
        self.VOLTAGE_value = 0
        self.PASS_FAIL_result = "TEST"

class pinInfoWidget(QtWidgets.QWidget):
    def __init__(self, wire : Wire,*args, **kwargs):
        super().__init__(*args,**kwargs)
        self.ui = PIN_INFO_UI()
        self.ui.setupUi(self)     
        self.connection = wire

    def updateLabels(self):
        self.ui.la_type_from.setText(f"{self.connection.from_type}")
        self.ui.la_type_from_to.setText(f"{self.connection.to_type}")
        self.ui.la_brcXY_from.setText(f"b:{self.connection.b_from} r:{self.connection.r_from} c:{self.connection.c_from} || X:{self.connection.x_from} Y:{self.connection.y_from})")
        self.ui.la_brcXY_to.setText(f"b:{self.connection.b_to} r:{self.connection.r_to} c:{self.connection.c_to} || X:{self.connection.x_to} Y:{self.connection.y_to}")
        self.ui.la_color.setText(f"{self.connection.Color}")
        self.ui.la_AWG_LENGTH.setText(f"AWG:{self.connection.Ga} Length:{self.connection.Length}")
        self.ui.la_ID.setText(f"ID:{self.connection.ID}")

class pinTableItem(QtWidgets.QTableWidgetItem):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.my_type = ""
        self.my_ID = 0
        self.my_Spring = ""
        self.my_Net_Name = ""
        self.my_on_device = ""
        self.my_b = 0
        self.my_r = 0
        self.my_c = 0
        self.my_X = 0
        self.my_Y = 0

class APP(QtWidgets.QWidget):
    def __init__(self,*args, **kwargs):
        super().__init__(*args,**kwargs)
        self.ui = CONTROL_UI()
        self.ui.setupUi(self)

        self.list_of_wires = loadWiresFromDb(dBCursor)
        self.list_of_insertions = loadInsertionsFromDatabase(dBCursor,query="SELECT * FROM insertions WHERE NodeName != 'Extra' ORDER BY NodeName ASC")
        #self.list_of_insertions = loadInsertionsFromDatabase(dBCursor,query="SELECT * FROM insertions")
        
        self.createPinProbeTable()
        self.createConnectionTable()
        self.max_x_size = 10000000000#is rewriten in query from self.loadGraphics()
        self.loadGraphics()
        self.ui.table_probe_pin.clicked.connect(self.showPinInfo)
        self.ui.table_connection.clicked.connect(self.showConnectionInfo)
        self.list_of_edited_graphics_items = []
        self.ui.pb_delete_lines.clicked.connect(self.restoreGraphicsItems)
        self.ui.pb_load_data.clicked.connect(self.loadDataFolder)

    def loadDataFolder(self):
        file = str(QtWidgets.QFileDialog.getExistingDirectory(self, "Select Directory"))
        print(file)
        storeInsertionsInDatabase(dBCursor,parseInsertion(path_to_file=file+"/inserts"))
        self.list_of_insertions = loadInsertionsFromDatabase(dBCursor)
        
        storeWiresInDb(dBCursor,parseWires(path_to_file=file+"/wires"))
        self.list_of_wires = loadWiresFromDb(dBCursor)

        self.createPinProbeTable()
        self.createConnectionTable()
        self.ui.graphics.scene().clear()
        self.loadGraphics()
        

    def showConnectionInfo(self):
        row = self.ui.table_connection.currentRow()
        widget:pinInfoWidget = self.ui.table_connection.cellWidget(row,0)
        x_from = float(widget.connection.x_from)/self.max_x_size
        y_from = float(widget.connection.y_from)/self.max_x_size
        x_to = float(widget.connection.x_to)/self.max_x_size
        y_to = float(widget.connection.y_to)/self.max_x_size
        print(x_from,y_from,x_to,y_to)
        line = QtWidgets.QGraphicsLineItem(x_from*1000+1.5,y_from*1000+1.5,x_to*1000+1.5,y_to*1000+1.5)
        line.setPen(QtGui.QPen(QtGui.QColor(255,100,50), 1.2))
        self.ui.graphics.scene().addItem(line)
        self.list_of_edited_graphics_items.append(line)

    def restoreGraphicsItems(self):
        for item in self.list_of_edited_graphics_items:
            self.ui.graphics.scene().removeItem(item)


    def wheelEvent(self, event):
            """
            Zoom in or out of the view.
            """

            if event.modifiers() & QtCore.Qt.KeyboardModifier.ControlModifier:
                self.ui.graphics.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
                self.ui.graphics.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
                zoomInFactor = 1.25
                zoomOutFactor = 1 / zoomInFactor

                # Set Anchors
                #self.ui.graphics.setTransformationAnchor(QtWidgets.QGraphicsView.ViewportAnchor.NoAnchor)
                #self.ui.graphics.setResizeAnchor(QtWidgets.QGraphicsView.ViewportAnchor.NoAnchor)

                # Zoom
                if event.angleDelta().y() > 0:
                    zoomFactor = zoomInFactor
                else:
                    zoomFactor = zoomOutFactor
                self.ui.graphics.scale(zoomFactor, zoomFactor)

                self.ui.graphics.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarPolicy.ScrollBarAsNeeded)
                self.ui.graphics.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarPolicy.ScrollBarAsNeeded)
                
    def loadGraphics(self,query:str = "SELECT * FROM INSERTIONS"):
        insertions = loadInsertionsFromDatabase(dBCursor,query=query)
        division = 1 #3e2
        self.max_x_size = float(dBCursor.execute("SELECT MAX(CAST(X AS FLOAT)) FROM INSERTIONS").fetchone()[0])/division
        
        self.ui.graphics.setScene(QtWidgets.QGraphicsScene())
        x_size = 3
        y_size = 3

        for insertion in insertions:
            x = float(insertion.X)/self.max_x_size
            y = float(insertion.Y)/self.max_x_size
            

            y = y*1000
            x = x*1000

            if str(insertion.Type).upper() == "PIN":
                circle = QtWidgets.QGraphicsEllipseItem(x,y,x_size,y_size)
                circle.setBrush(QtGui.QBrush(QtGui.QColor(255,0,0)))
                self.ui.graphics.scene().addItem(circle)
            
            elif "MIL" in str(insertion.Type).upper(): ##PROBE PIN
                square = QtWidgets.QGraphicsRectItem(x,-y,x_size,y_size)
                square.setBrush(QtGui.QBrush(QtGui.QColor(0,255,0)))
                self.ui.graphics.scene().addItem(square)

            elif "TOOLING" in str(insertion.Type).upper():
                square = QtWidgets.QGraphicsRectItem(x,-y,x_size,y_size)
                square.setBrush(QtGui.QBrush(QtGui.QColor(100,100,100)))
                self.ui.graphics.scene().addItem(square)
            
            elif "OFFSET PIN" in str(insertion.Type).upper():
                circle = QtWidgets.QGraphicsEllipseItem(x,y,x_size,y_size)
                circle.setBrush(QtGui.QBrush(QtGui.QColor(0,0,255)))
                self.ui.graphics.scene().addItem(circle)
            
            else:
                print(insertion.Type)
                circle = QtWidgets.QGraphicsEllipseItem(x,y,x_size,y_size)
                circle.setBrush(QtGui.QBrush(QtGui.QColor(255,255,255)))
                self.ui.graphics.scene().addItem(circle)
        
        self.ui.graphics.fitInView(self.ui.graphics.scene().sceneRect(),QtCore.Qt.AspectRatioMode.KeepAspectRatioByExpanding)
        self.ui.graphics.scale(10,10)
    
        

                

    def showPinInfo(self):
        row = self.ui.table_probe_pin.currentRow()
        table_item: pinTableItem
        table_item = self.ui.table_probe_pin.item(row,0)
        self.ui.la_pin_type.setText(table_item.my_type)
        self.ui.la_pin_ID.setText(str(table_item.my_ID))
        self.ui.la_pin_spring.setText(table_item.my_Spring)
        self.ui.la_pin_net_name.setText(table_item.my_Net_Name)
        self.ui.la_pin_on_device.setText(table_item.my_on_device)
        self.ui.la_pin_b.setText(str(table_item.my_b))
        self.ui.la_pin_r.setText(str(table_item.my_r))
        self.ui.la_pin_c.setText(str(table_item.my_c))
        self.ui.la_pin_x.setText(str(table_item.my_X))
        self.ui.la_pin_y.setText(str(table_item.my_Y))

        b = table_item.my_b
        r = table_item.my_r
        c = table_item.my_c
        X = table_item.my_X
        Y = table_item.my_Y

        query = f"SELECT * from WIRES WHERE ((b_from = '{b}' AND r_from = '{r}' AND c_from = '{c}' AND x_from = '{X}'  AND y_from = '{abs(int(Y))}') OR (b_to = '{b}' AND r_to = '{r}' AND c_to = '{c}' AND x_to = '{X}'  AND y_to = '{abs(int(Y))}'))"
        #print(query)
        self.list_of_wires = loadWiresFromDb(dBCursor,query=query)
        self.ui.table_connection.clearContents()
        self.createConnectionTable()
        
    def createConnectionTable(self):
        number_of_wires = len(self.list_of_wires)
        self.ui.table_connection.setRowCount(number_of_wires)
        for table_row,wire in enumerate(self.list_of_wires):
            pin_info = pinInfoWidget(wire)
            pin_info.updateLabels()
            button_widget = QtWidgets.QPushButton("")
            button_widget.setIcon(QtGui.QIcon("icons/TEST.png"))
            self.ui.table_connection.setCellWidget(table_row,0,pin_info)
            self.ui.table_connection.setCellWidget(table_row,1,button_widget)

        self.ui.table_connection.resizeColumnsToContents()
        self.ui.table_connection.resizeRowsToContents()


    def createPinProbeTable(self):
        number_of_pins = len(self.list_of_insertions)
        self.ui.table_probe_pin.setRowCount(number_of_pins)
        for table_row,insertion in enumerate(self.list_of_insertions):
            b = insertion.b
            r = insertion.r
            c = insertion.c
            type = insertion.Type
            table_item = pinTableItem(f"{type}({b},{r},{c})")
            table_item.my_b = b
            table_item.my_r = r
            table_item.my_c = c
            table_item.my_X = insertion.X
            table_item.my_Y = insertion.Y
            table_item.my_type = insertion.Type
            table_item.my_ID = insertion.ID
            table_item.my_Spring = insertion.Spring
            table_item.my_Net_Name = insertion.NodeName
            table_item.my_on_device = insertion.OnDevice

            button_widget = QtWidgets.QPushButton("")
            button_widget.setIcon(QtGui.QIcon("icons/TEST.png"))
            self.ui.table_probe_pin.setItem(table_row,0,table_item)
            self.ui.table_probe_pin.setCellWidget(table_row,1,button_widget)

        self.ui.table_probe_pin.resizeColumnsToContents()

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    window = APP()
    window.show()
    sys.exit(app.exec())