import random
import drawCard
from drawCard import drawCard

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

def playerchoice(playerID, playerhand, drawCardCount, deck, MaskImgList):
    finished = False
    while (finished == False):
        if (handVal(playerhand) == 21):
            print("Blackjack!")
            finished = True

        if (finished == False):
            print(handVal(playerhand))
            playerInput = input("Player " + playerID + " input: " )

            if playerInput == 'a':
                print("Hit")
                cardValue, drawCardCount = drawCard(drawCardCount, deck, MaskImgList)
                playerhand.append(cardValue)
                #spytt ut kort : send piss til serial

                if (handVal(playerhand) == 0):
                    #Update score
                    print(playerID, " Busted")
                    finished = True
                    
                elif(handVal(playerhand) == 21):
                    finished = True

            elif playerInput == "b":
                #Enter bet
                print(playerID, " Double down")
                cardValue, drawCardCount = drawCard(drawCardCount, deck, MaskImgList)
                playerhand.append(cardValue)
                #Spytt ut kort
                finished = True
                
                if (handVal(playerhand) == 0):
                    #Update score
                    print("Busted")
                    finished = True
                elif (handVal(playerhand) == 21):
                    finished = True

            elif playerInput == "c":
                print("Stand")
                finished = True
    return drawCardCount
        


def dealerchoice(dealerhand, drawCardCount, deck, MaskImgList):
    if (handVal(dealerhand) == 0):
        print("Dealer busted!")
        return drawCardCount

    elif(handVal(dealerhand) < 16):
        print("Hit - Dealer")
        cardvalue, drawCardCount = drawCard(drawCardCount, deck, MaskImgList)
        dealerhand.append(cardValue)
        #Spytt ut kort
        dealerchoice()
        
    else:
        print("Dealer stand")
        print("Dealer hand: ", handVal(dealerhand))
        return drawCardCount


def scorecompare(playerID, playerHand, dealerhand):
    if(handVal(playerHand) > handVal(dealerhand)):
        print("Player ",playerID , "has a score of ", handVal(playerHand)," and beat the dealer")
    elif (handVal(playerHand) == handVal(dealerhand)):
        print("Player ",playerID ," drew")
    else:
        print("Dealer beat player ", playerID)



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
