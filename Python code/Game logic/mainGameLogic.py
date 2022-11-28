import drawCard
from drawCard import drawCard
import cv2
import os
import autojack
from autojack import playerchoice
from autojack import dealerchoice
from autojack import scorecompare
import serial
import time
import comTest
from comTest import write
from comTest import read
from comTest import wr

# importing the referance pictures and making a list of the card values taken from the pictures name.
directory = "maskImg"
maskImgList = []
deck = []
pictureFolder = os.listdir(directory)



for picture in pictureFolder:
    imgCur = cv2.imread(f"{directory}/{picture}", cv2.IMREAD_UNCHANGED)
    maskImgList.append(imgCur)
    deck.append(os.path.splitext(picture)[0])

drawCardCount = int
drawCardCount = 0
    

#playerscores = [20000,20000,20000,20000,20000]

#Waits for ready signal
read()
time.sleep(0.1)

#Gets number of players
numberOfPlayers = int(wr('x'))
#send number f player to arduino
tempID = ord('d')
playerID = []
for i in range(numberOfPlayers):
    playerID.append(chr(tempID))
    tempID += 1


dealer = numberOfPlayers
time.sleep(0.3)
gameOn = True
while gameOn:
    gameOn = False

    player1hand = []
    player2hand = []
    player3hand = []
    player4hand = []
    player5hand = []

    players = [player1hand, player2hand, player3hand, player4hand, player5hand]

# Initial deal at start of the round
    for i in range(0, 2):
        for j in range(0, numberOfPlayers + 1):
            
            write('m'+ str(j))
            while(read() != "v"):
                time.sleep(0.01)
            cardValue, drawCardCount = drawCard(drawCardCount, deck, maskImgList)
            players[j].append(cardValue)
            print(comTest.read())


    write('m'+ str(0))
    while(read() != "v"):
        time.sleep(0.01)
        
  # Main game loop
    for i in range(numberOfPlayers):

        drawCardCount = playerchoice(playerID[i], players[i], drawCardCount, deck, maskImgList)
    drawCardCount = dealerchoice(players[dealer], drawCardCount, deck, maskImgList)

    for i in range(numberOfPlayers):
        
        scorecompare(playerID[i], players[i], players[dealer])
        
    # while !Input - some input to restart gameloop. Or turn off to end game/restart
    time.sleep(1)
    write('q')
    time.sleep(0.1)
    while True:
        dec = read()
        if dec == 'a':
            numberOfPlayers = int(wr('x'))
            gameOn = True
            break
        elif dec == 'c':
            gameOn = False
            break


