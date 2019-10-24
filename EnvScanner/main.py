import sys
import os
import threading
from PyQt5.QtGui import QColor, QClipboard, QGuiApplication
from PyQt5.QtCore import Qt #,QRect
from PyQt5.QtWidgets import QApplication,QMainWindow,QTableWidgetItem,QTableWidget,QDialog,QMessageBox,QHeaderView,QDesktopWidget
from PyQt5.uic import loadUi
import ifaddr
import requests

lines = []

def blockPrint():
	sys.stdout = open(os.devnull, 'w')

def enablePrint():
	sys.stdout = sys.__stdout__
	
def check_url(ip):
	global lines
	try:
		url = 'http://' + ip + '/report.html'
		r = requests.get(url, verify=False, timeout=1)
		if r.text == 'OK':
			lines.append('Real_Resault,' + ip + ',Good,' + url)
	except:
		pass

class main(QMainWindow):
	def __init__(self):
		super(main,self).__init__()
		loadUi('resources/main.ui',self)

		#center window
		qtRectangle = self.frameGeometry()
		centerPoint = QDesktopWidget().availableGeometry().center()
		qtRectangle.moveCenter(centerPoint)
		self.move(qtRectangle.topLeft())
		
		self.setWindowTitle('EnvScann')
		self.pushButton.clicked.connect(self.on_pushButtonX_clicked)
		self.tableWidget.doubleClicked.connect(self.on_tableWidget_double_clicked)
		self.tableWidget.horizontalHeader().setDefaultAlignment(Qt.AlignLeft)
		self.tableWidget.setEditTriggers(QTableWidget.NoEditTriggers)

	def resizeEvent(self, event):
		width = self.frameGeometry().width()
		height = self.frameGeometry().height()

		#Tabel geometry and Header width
		self.tableWidget.setGeometry(10, 10, width-35, height-100)
		header = self.tableWidget
		header.setColumnWidth(0, width/4+5)
		header.setColumnWidth(1, width/4-30)
		header.setColumnWidth(2, width/4-30)
		header.setColumnWidth(3, width/4+10)
		self.pushButton.setGeometry(width-105, height-80, 75, 31)
		
	def load_list(self):
		global lines
		self.tableWidget.setRowCount(0)	
		self.tableWidget.setRowCount(len(lines))
		self.tableWidget.setEditTriggers(QTableWidget.NoEditTriggers)
				
		for i in enumerate(lines):
			self.tableWidget.setItem(i[0],0,QTableWidgetItem(str(i[1]).split(',')[0]))
			self.tableWidget.setItem(i[0],1,QTableWidgetItem(str(i[1]).split(',')[1]))
			self.tableWidget.setItem(i[0],2,QTableWidgetItem(str(i[1]).split(',')[2]))
			self.tableWidget.setItem(i[0],3,QTableWidgetItem(str(i[1]).split(',')[3]))
			
			#self.tableWidget.item(i[0],3).setForeground(QColor(245,245,245))
			
		
	def on_pushButtonX_clicked(self):
		global lines
		ip_list = []
		lines.clear()
		ip_list.clear()
		
		#test lines
		lines = ["Fake_1,192.168.1.1,Good,http://192.168.1.1/report", "Fake_2,192.168.1.2,Good,http://192.168.1.2/report", "Fake_3,192.168.1.3,Good,http://192.168.1.3/report"] 
		
		adapters = ifaddr.get_adapters()
		for adapter in adapters:
			#print ('IPs of network adapter ' + adapter.nice_name)
			for ip in adapter.ips:
				if len(ip.ip) > 7: #only IPv4
					ip_split = ip.ip.split('.')
					if ip_split[0] != '127': #exclude 127.0.0.1
						print ('   %s/%s' % (ip.ip, ip.network_prefix))
						if ip.network_prefix == 24: # Control the subnet
							for x in range(254):
								#print (ip_split[0] + '.' + ip_split[1] + '.' + ip_split[2] + '.' + str(x))
								ip_list.append(ip_split[0] + '.' + ip_split[1] + '.' + ip_split[2] + '.' + str(x))
							
		QMessageBox.information(self, 'Notification', 'This operation will take some time!')
		

		threads = []
		for line in ip_list:
			thread = threading.Thread(target=check_url, args=[line])
			thread.start()
			threads.append(thread)
		for t in threads:
			t.join()
		self.load_list()
		QMessageBox.information(self, 'Notification', 'Operation Finished!')
		
	def on_tableWidget_double_clicked(self):
		global test
		try:
			row = self.tableWidget.currentItem().row()
			QMessageBox.warning(self, 'Title!', self.tableWidget.item(row,0).text().strip() + ' will open to browser!')
			os.system('start "" "' + self.tableWidget.item(row,3).text().strip() + '"')
		except:
			pass

app=QApplication(sys.argv)
widget=main()
widget.show()
sys.exit(app.exec_())