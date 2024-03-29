#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main()
{
    int card1_player, card2_player, card1_dealer, card2_dealer, player_cards = 0, dealer_cards = 0, card_aux_player, card_aux_dealer, decision;
    bool player_busted = false;
    bool dealer_busted = false;
    bool ace;
    bool sw_player = false;
    bool sw_dealer = false;

    srand(time(NULL));

    card1_player = 1 + rand()%11;
    card2_player = 1 + rand()%11;
    card1_dealer = 1 + rand()%11;
    card2_dealer = 1 + rand()%11;

    printf("Let's start the BlackJack GAME!!!\n\n");
    if((card1_player==card2_player) && (card1_player == 11))
        player_cards = 12; //because ace is 11 or 1, and in this case, we can't have from the beggining 22
    else player_cards = card1_player + card2_player;
    printf("You are the player and you have %d and %d, your total is: %d! \n\n", card1_player, card2_player, player_cards);
    while(sw_player == false)
    {
        if(player_cards == 21)
        {
            printf("Your total is %d and it's a BLACKJACK!!!\n", player_cards);
            sw_player = true;
            break;
        }

        printf("Do you want to draw another card? Type 1 for YES or 0 for NO! ");
        scanf("%d", &decision);
        if(decision==1)
        {
            ace = false;
            card_aux_player = 1 + rand()%11;
            if(card_aux_player == 11)
                ace = true;
            else player_cards += card_aux_player;
            if ((player_cards < 21) && (ace == true))
            {
                if(player_cards < 11)
                {
                    player_cards += 11;
                    card_aux_player = 11;
                }
                else {
                        player_cards += 1;
                        card_aux_player = 1;
                }

                if(player_cards == 21)
                    {
                        printf("You draw a %d, your total is %d! It's a BLACKJACK!\n\n", card_aux_player, player_cards);
                        sw_player == true;
                        break;
                    }
                else {
                        printf("You draw a %d, your total is: %d! \n\n", card_aux_player, player_cards);
                }
            }
            else if ((player_cards < 21) && (ace == false))
                {
                    printf("You draw a %d, your total is: %d! \n\n", card_aux_player, player_cards);
                }
            else if (player_cards > 21){
                    printf("You draw a %d! Your total is %d! You are over 21, you are ELIMINATED!\n\n",card_aux_player, player_cards);
                    player_busted = true;
                    break;
            }
            else if (player_cards == 21)
            {
                printf("You draw a %d! Your total is %d and it's a BLACKJACK!!!\n\n", card_aux_player, player_cards);
                sw_player = true;
            }
        }
        else if(decision==0)
        {
            sw_player = true;
            printf("Your total cards is %d!\n\n", player_cards);
            break;
        }
    }

    if((card1_dealer==card2_dealer) && (card1_dealer == 11))
        dealer_cards = 12;
    else dealer_cards = card1_dealer + card2_dealer;
    while(sw_dealer == false)
    {
        if(player_busted == true)
            {
                printf("The dealer has %d and %d and his total is: %d! The dealer WON because you are BUSTED", card1_dealer, card2_dealer, dealer_cards);
                sw_dealer == true;
                break;
            }
        else printf("The dealer has %d and %d and his total is: %d!\n", card1_dealer, card2_dealer, dealer_cards);
        while(dealer_cards < 17)
        {
            card_aux_dealer = 1 + rand()%11;
            ace = false;
            if(card_aux_dealer == 11)
                ace = true;
            if(ace == true)
            {
                if(dealer_cards < 11)
                    {
                        dealer_cards += 11;
                        card_aux_dealer = 11;
                    }
                else {
                        dealer_cards += 1;
                        card_aux_dealer = 1;
                }
                printf("The dealer drew a %d and his total is %d! \n", card_aux_dealer, dealer_cards);

            }
            else dealer_cards += card_aux_dealer;
            printf("The dealer drew a %d and his total is %d! \n", card_aux_dealer, dealer_cards);
            if(dealer_cards >= 17)
            {
                sw_dealer = true;
                break;
            }
        }
        if(dealer_cards > 21)
            dealer_busted = true;
    }
    if(dealer_busted == true)
        printf("Dealer is busted and the player WON the game with a total of %d!!!", player_cards);
    if((dealer_busted != true) && (player_busted != true) )
    {
        if((player_cards <= 21) && (dealer_cards <=21))
        {
        if(player_cards > dealer_cards)
            printf("The player win this BLACKJACK game against the dealer!!!");
        else if(player_cards < dealer_cards)
            printf("The dealer win this BLACKJACK game against the player!!!");
        else if(player_cards == dealer_cards)
            printf("It's a draw!!!");
        }
    }
    return 0;

}

