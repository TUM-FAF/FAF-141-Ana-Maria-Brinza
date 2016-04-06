import sys
from PyQt4 import QtCore, QtGui, uic
from PyQt4.QtGui import QSound
from math import sqrt
from PyQt4.phonon import Phonon
number = 0.0
new = 0.0 #the new number
op = False #operation var
operator = ""
sumIt = 0
sumall = 0.0
 
qtCreatorFile = "calculator.ui" 
 
Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)
 
class MyApp(QtGui.QMainWindow, Ui_MainWindow):
    
    def __init__(self):
        
        QtGui.QMainWindow.__init__(self)
        #song to play
        self.mediaObject = Phonon.MediaObject(self)
        self.audioOutput = Phonon.AudioOutput(Phonon.MusicCategory, self)
        Phonon.createPath(self.mediaObject, self.audioOutput)
        path = "D:\UTM\Anul 2\Semestrul 2\MIDPS\Lab2\Pink.mp3"
        self.mediaObject.setCurrentSource(Phonon.MediaSource(path))
        self.mediaObject.play()
        
        Ui_MainWindow.__init__(self)
        self.setWindowTitle("Calculator")
        self.setWindowIcon(QtGui.QIcon('Pink.png'))
        self.setupUi(self)
       
        
        
        numbers = [self.button0, self.button1, self.button2, self.button3, self.button4, self.button5, self.button6, self.button7,self.button8,self.button9]
        operations = [self.plus, self.minus, self.mul, self.div, self.equal]
        
        for i in numbers:
            i.clicked.connect(self.Nums)
        for i in operations:
            i.clicked.connect(self.Operations)
        self.plus_minus.clicked.connect(self.Plus_Minus)
        self.point.clicked.connect(self.Point)
        self.power.clicked.connect(self.Power)
        self.sqrt.clicked.connect(self.Sqrt)
        self.clear.clicked.connect(self.C)
        
    
            
    def Nums(self):
        global number
        global new
        global op

        sender = self.sender() 

        new = int(sender.text())
        setNumber = str(new)

        if op == False:
            self.Result_box.setText(self.Result_box.toPlainText() + setNumber)
        else:
            self.Result_box.setText(setNumber)
            op = False
    def Plus_Minus(self):
        global number
             
        try:
                number = int(self.Result_box.toPlainText())
                 
        except:
                number = float(self.Result_box.toPlainText())
        number = number*(-1)
        numStr = str(number)
             
        self.Result_box.setText(numStr)
        
    def Operations(self):
        global number
        global op
        global operator
        global sumIt

        sumIt += 1

        if sumIt > 1:
                self.Equal()
            
        number = self.Result_box.toPlainText() #.text()
        sender = self.sender()
        operator = sender.text()

        op = True
    def Equal(self):
        global number
        global new
        global sumall
        global operator
        global op
        global sumIt

        sumIt = 0

        new = self.Result_box.toPlainText() #.text()
        print(number)
        print(operator)
        print(new)

        if operator == "+":
            sumall = float(number) + float(new)

        elif operator == "-":
            sumall = float(number) - float(new)
        elif operator == "x":
            sumall = float(number) * float(new)
        elif operator == "/":
            sumall = float(number) / float(new)
        elif operator == "n^m":
            sumall = float(number) ** float(new)

        print(sumall)
        self.Result_box.setText(str(sumall))
        op = True

    def Point(self):
        global op
             
        if "." not in self.Result_box.toPlainText():
            self.Result_box.setText(self.Result_box.toPlainText() + ".")

    def C(self):
        global new
        global sumall
        global operator
        global number
             
        self.Result_box.clear()
     
        num = 0.0
        new = 0.0
        sumall = 0.0
        operator = ""
    def Sqrt(self):
        global number
             
        number = float(self.Result_box.toPlainText())
        if (number<0):
            self.Result_box.setText('ERROR')
        n = sqrt(number)
        number = n
     
        self.Result_box.setText(str(number))
        
    def Power(self):
        global number
        global op
        global operator
        global sumIt
     
        sumIt += 1
     
        if sumIt > 1:
            self.Equal()
     
        number = self.Result_box.toPlainText()
     
        sender = self.sender()
     
        operator = sender.text()
             
        op = True

    
 
if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    window = MyApp()
    
    window.show()
    sys.exit(app.exec_())
