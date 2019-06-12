import serial
import smtplib
from email.message import EmailMessage
import urllib.request
import time

def enviaMail():
	from_mail = 'APCS123456789'
	palavra_chave = 'olaola123456789'
	to_mail = 'nil_silva_12@outlook.com'
	subject = 'ALERTA'
	content = 'Movimento detetado.'
	
	msg = EmailMessage()
	msg['from'] = from_mail
	msg['to'] = to_mail
	msg['subject'] = subject
	msg.set_content(content)

	mail = smtplib.SMTP('smtp.gmail.com', 587)

	mail.ehlo()

	mail.starttls()

	try:
		mail.login(from_mail, palavra_chave)
		print('login successful')
	except:
		print('login failed')

	try:
		mail.sendmail(from_mail, to_mail, msg.as_string())
		print('email sent')
	except:
		print('email not sent')

ser = serial.Serial(port='COM13',baudrate=9600)
pirValue = -1

url = 'http://api.thingspeak.com/update?api_key=18UCXEIIBBDNJDQ5&field1='

print(time.asctime( time.localtime(time.time()) ))

while(True):

	v1 = str(ser.readline())
	v2 = v1.split('\'')
	v3 = v2[1].split('\\')
	
	pirValue = int(v3[0])
	
	print(pirValue)
	
	localtime = time.asctime( time.localtime(time.time()) )
	
	if pirValue == 0:
		#f = urllib.request.urlopen(url +str(localtime))
		print(localtime)
		#f.read()
		#f.close()
	elif pirValue ==1:
		#f = urllib.request.urlopen(url +str(localtime))
		print(localtime)
		#f.read()
		#f.close()
		enviaMail()
