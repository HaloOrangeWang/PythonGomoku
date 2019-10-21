from PyQt5.QtGui import QPainter, QPen
from PyQt5.QtWidgets import QWidget
from PyQt5.QtCore import Qt


class CornerWidget(QWidget):

    def __init__(self, parent):
        super().__init__(parent=parent)
        self.setFixedSize(30, 30)

    def paintEvent(self, e):
        qp = QPainter()
        qp.begin(self)
        pen = QPen(Qt.red, 3, Qt.SolidLine)
        qp.setPen(pen)
        qp.drawLine(0, 8, 0, 0)
        qp.drawLine(0, 0, 8, 0)
        qp.drawLine(22, 0, 28, 0)
        qp.drawLine(28, 0, 28, 8)
        qp.drawLine(28, 22, 28, 28)
        qp.drawLine(28, 28, 20, 28)
        qp.drawLine(8, 28, 0, 28)
        qp.drawLine(0, 28, 0, 22)
