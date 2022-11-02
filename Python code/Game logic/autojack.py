import random

def main():
    deck = ["2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14"]
    #Initiate hand arrays
    dealerhand = []
    player1hand = []
    player2hand = []
    player3hand = []
    player4hand = []
    players = [player1hand, player2hand, player3hand, player4hand, dealerhand]
    rounds = 1

    def draw_card():
       draw = random.choice(deck)
       return draw
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

    def printHand(playerID, pHand):
        print("Player ", playerID, " has: ", pHand, " to a total value of: ", handVal(pHand))

    def playerchoice(playerID, playerhand):
        finished = False
        while (finished == False):
            printHand(playerID, playerhand)
            if (handVal(playerhand) == 21):
                print("Blackjack!")
                finished = True

            if (finished == False):
                pinput = input ("H to hit, S to stand, D to Double Down\n")

                if pinput == "h":
                    playerhand.append(draw_card()) 

                    if (handVal(playerhand) == 0):
                        printHand(playerID, playerhand)
                        print("You busted!")

                        finished = True
                    elif(handVal(playerhand) == 21):
                        printHand(playerID, playerhand)
                        print ("You have blacjack!")
                        finished = True

                elif pinput == "d":
                    playerhand.append(draw_card())
                    printHand(playerID, playerhand)
                    finished = True
                    if (handVal(playerhand) == 0):
                        print("You busted!")

                elif pinput == "s":
                    finished = True

    def play_deck():
        drawncards = [draw_card(), draw_card()]
        return drawncards

    def dealerchoice():
        if (handVal(players[4]) == 0):
            print("Dealer busted!")
            return

        elif(handVal(players[4]) < 16):
            players[4].append(draw_card())
            dealerchoice()

        else:
            return

    def scorecompare(playerID, playerHand):
        if(handVal(playerHand) > handVal(players[4])):
            print("Player ",playerID , "has a score of ", handVal(playerHand)," and beat the dealer")
        elif (handVal(playerHand) == handVal(players[4])):
            print("Player ",playerID ," drew")
        else:
            print("Dealer beat player ", playerID)



    for x in range(rounds):
        for y in range(len(players)):
            players[y] = play_deck()

        for y in range(len(players)-1):
            playerchoice(y+1,players[y])

        dealerchoice()

        printHand("Dealer", players[4])

        for y in range(len(players)-1):
            scorecompare(y+1,players[y])

main()
