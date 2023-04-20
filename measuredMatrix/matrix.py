from PyQt6 import QtCore, QtGui, QtWidgets
import numpy as np
from matrix_testGUI import Ui_Form
from matrix_test_buttonGUI import Ui_Form as Ui_Button
number_of_rows = 1
number_of_pins_in_row = 80


class button(QtWidgets.QPushButton):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.setStyleSheet("font-size: 8px; font-weight:bold;")
        self.setGeometry(QtCore.QRect(0, 0, 10, 10))
        self.row = 0
        self.column = 0
        self.value = 0
        self.VOLTAGE_value = 0
        self.PASS_FAIL_result = "N/A"
    

class APP(QtWidgets.QWidget):
    def __init__(self,*args, **kwargs):
        super().__init__(*args,**kwargs)
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.number_of_rows = 45
        self.number_of_pins_in_row = 80
        self.treshold = self.ui.spin_treshold.value()
        self.initTable()
        self.ui.pb_set.clicked.connect(self.initTable)

    def initTable(self):
        self.treshold = self.ui.spin_treshold.value()
        self.number_of_pins_in_row = self.ui.spin_rows.value()
        self.number_of_rows = self.ui.spin_columns.value()
        self.ui.table.setColumnCount(self.number_of_pins_in_row)
        self.ui.table.setRowCount(self.number_of_rows)
        for rows in range(self.number_of_rows):
            for pins in range(self.number_of_pins_in_row):
                button_widget = button()
                button_widget.setText(f"{rows}x{pins}")
                button_widget.clicked.connect(self.pin_clicked)
                button_widget.row = rows
                button_widget.column = pins
                button_widget.VOLTAGE_value = 0
                button_widget.PASS_FAIL_result = "N/A"

                self.ui.table.setCellWidget(rows , pins, button_widget)

        self.style_table()
            
    def pin_clicked(self):
        button_widget = self.sender()
        button_widget : button
        print(f"row: {button_widget.row} column: {button_widget.column} value: {button_widget.VOLTAGE_value}")

    def style_table(self):
        for rows in range(self.number_of_rows):
            for pins in range(self.number_of_pins_in_row):
                button_widget = self.ui.table.cellWidget(rows, pins)
                button_widget : button
                if button_widget.VOLTAGE_value < self.treshold:
                    button_widget.setStyleSheet("background-color: green")
                else:
                    button_widget.setStyleSheet("background-color: red")

result_matrix = np.zeros((number_of_rows, number_of_pins_in_row), dtype=float)-2
print(result_matrix)

result_matrix[0,0] = 20
print(np.size(result_matrix))

if __name__ == '__main__':
    app = QtWidgets.QApplication([])
    window = APP()
    window.show()
    app.exec()
