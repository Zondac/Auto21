import drawCard
from drawCard import drawCard
import comTest
from comTest import read
from comTest import write
from comTest import wr
import time


def handVal(player_hand):
    player_hand.sort()
    valSum = 0
    for x in range(len(player_hand)):
        
        if int(player_hand[x]) == 14:
            valSum += 11
            if valSum > 21:
                valSum -= 10
        
        elif (int(player_hand[x]) > 10):
            valSum += 10
        else:
            valSum += int(player_hand[x])
    
    if (valSum > 21):
        #bust case
        return 0
    
    return valSum

def selectPlayerAmount():
    write('x')
    amount = read()
    return amount

def playerchoice(playerID, playerhand, drawCardCount, deck, MaskImgList):
    finished = False
    if (handVal(playerhand) == 21):
        time.sleep(0.1)
        write('m'+ str(ord(playerID)-ord('c')))
        time.sleep(0.1)
        finished = True
    else:
        time.sleep(0.1)
        write(playerID)
        time.sleep(0.1)
    while (finished == False):
        
        if (finished == False):
            playerInput = read() # Function to send serial data to arduino
           ### playerInput = GetInpuT() # Function to get output back from arduino
            
           

            if playerInput == 'a':
               
               time.sleep(1)
               cardValue, drawCardCount = drawCard(drawCardCount, deck, MaskImgList)
               time.sleep(1)
               read()
               playerhand.append(cardValue)
               
               #Send serial to arduino to dispense card
               

               if (handVal(playerhand) == 0):
                    #Update score
                    write('m'+ str(ord(playerID)-ord('c')))     
                    while(read() != "v"):
                        time.sleep(0.01)
                    finished = True
                    
               elif(handVal(playerhand) == 21):
                    write('m'+ str(ord(playerID)-ord('c')))     
                    while(read() != "v"):
                        time.sleep(0.01)
                    finished = True
               else:
                   write(playerID)

            elif playerInput == "b":
               #Enter bet
               time.sleep(0.1)
               cardValue, drawCardCount = drawCard(drawCardCount, deck, MaskImgList)
               playerhand.append(cardValue)
               time.sleep(0.1)
               read()
               #Spytt ut kort
               finished = True
               
                
               if (handVal(playerhand) == 0):
                   #Update score
                    time.sleep(0.1)
                    write('m'+ str(ord(playerID)-ord('c')))     
                    while(read() != "v"):
                        time.sleep(0.01)
                    finished = True
               elif (handVal(playerhand) == 21):
                    time.sleep(0.1)
                    write('m'+ str(ord(playerID)-ord('c')))     
                    while(read() != "v"):
                        time.sleep(0.01)
                    finished = True
                   
            elif playerInput == "c":
                time.sleep(0.1)
                write('m'+ str(ord(playerID)-ord('c')))     
                while(read() != "v"):
                    time.sleep(0.01)
                finished = True
               
    return drawCardCount
        


def dealerchoice(dealerhand, drawCardCount, deck, MaskImgList):
    if (handVal(dealerhand) == 0):
        drawCardCount = drawCardCount
        write('m'+ str(0))
        return drawCardCount

    elif(handVal(dealerhand) < 17):
        cardValue, drawCardCount = drawCard(drawCardCount, deck, MaskImgList)
        dealerhand.append(cardValue)
        read()
        #Spytt ut kort
        drawCardCount = dealerchoice(dealerhand, drawCardCount, deck, MaskImgList)
        return drawCardCount
        
    else:
        write('m'+ str(0))
        return drawCardCount

playerscores = [20000,20000,20000,20000,20000]


def scorecompare(playerID, playerHand, dealerhand):
    time.sleep(0.5)
    index = ord(playerID)-100
    global playerscores
    if(handVal(playerHand) > handVal(dealerhand)):
        playerscores[index] += 50
        if(handVal(playerHand) == 21):
            playerscores[index] +=25
        write(chr(ord(playerID)+5)+str(playerscores[index] ))        
        time.sleep(2)
    elif (handVal(playerHand) == handVal(dealerhand)):
        write(chr(ord(playerID)+5)+str(playerscores[index] ))
        time.sleep(2)
    else:
        playerscores[index] -=50
        write(chr(ord(playerID)+5)+str(playerscores[index] ))        
        time.sleep(2)


#     for x in range(rounds):
#         for y in range(len(players)):
#             players[y] = play_deck()
# 
#         for y in range(len(players)-1):
#             playerchoice(y+1,players[y])
# 
#         dealerchoice()
# 
#         printHand("Dealer", players[4])
# 
#         for y in range(len(players)-1):
#             scorecompare(y+1,players[y])
