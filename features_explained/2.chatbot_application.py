import time, datetime
import telepot
from telepot.loop import MessageLoop

now = datetime.datetime.now() 

def action(msg):
    chat_id = msg['chat']['id']
    command = msg['text']
    print 'Received: %s' % command
    if command == 'Hi':
	telegram_bot.sendMessage (chat_id, str("Hi!!! "))
	telegram_bot.sendMessage (chat_id, str("Authentication Required"))
	time.sleep(10) 
    elif command == 'what is the time':
        telegram_bot.sendMessage(chat_id, str("The time is ")+str(now.hour)+str(":")+str(now.minute))
    elif command == 'Could you send me any Quote for me?':
	telegram_bot.sendMessage (chat_id, str("sure"))
	telegram_bot.sendPhoto (chat_id, photo = "https://media4.picsearch.com/is?FlNheu9LPu6Js5kx9zskHORczbl9yinMA_w-HtqFi-0&height=320")
    elif command == 'Thats too motivational!!': 
	telegram_bot.sendMessage (chat_id, str("Yes Just Like You!!!")) 
    elif command == 'Sounds Funny!!':
	telegram_bot.sendMessage (chat_id, str("Just Kidding"))
    elif command == 'Have any file regarding SCR??': 
	telegram_bot.sendMessage (chat_id, str("My Searching Algorithm has started!!"))
	telegram_bot.sendDocument(chat_id, document=open('/home/pi/scr.py'))
    elif command == 'Yes, This is the file Thanks!!!':
	telegram_bot.sendMessage (chat_id, str("Your Welcome"))
    elif command == 'Do You have any Audio in You?':
	telegram_bot.sendMessage (chat_id, str("It must be there!!!"))
	telegram_bot.sendMessage (chat_id, str("Wait a Minute!!!!"))
	telegram_bot.sendAudio(chat_id, audio=open('/home/pi/test.mp3'))

telegram_bot = telepot.Bot('1095990063:AAFrNLJQEBmuNcKhR2bJ5El3hKRAjSJMm_s')
print (telegram_bot.getMe())

MessageLoop(telegram_bot, action).run_as_thread()
print 'Up and Running....'

while 1:
    time.sleep(10)
