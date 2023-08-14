#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    int value;
    char symbol[20];
    char final_win[20];
} card;

typedef struct{
    card cards[5];
} hand;

void card_showing(card CARD){
    printf("Value: %d; Symbol: %s\n", CARD.value, CARD.symbol);
}

void shuffle(card* cards, int nr_card){
    for(int i=nr_card -1; i>0; i--){
        int j=rand()%(i+1);
        card aux = cards[i];
        cards[i]=cards[j];
        cards[j]=aux;
    }
}
void hand_showing(hand HAND){
    for(int i=0;i<5;i++)
    {
        card_showing(HAND.cards[i]);
    }
}

void sort_hand(hand *HAND) {
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = i + 1; j < 5; j++) {
            if (HAND->cards[i].value > HAND->cards[j].value) {
                card temp = HAND->cards[i];
                HAND->cards[i] = HAND->cards[j];
                HAND->cards[j] = temp;
            }
        }
    }
}

// le-am pus in ordine de importanta ca sa se vada clar fiecare pas si ca sa nu se poata repeta valorile
int winner(hand *HAND){
    int i, win, sw=0, sw2=0, big_card;

    win=0;

    //o pereche
    for (int i = 0; i < 4; i++) {
        if (HAND->cards[i].value == HAND->cards[i+1].value) {
            win=2;
        }
    }

    //doua perechi
    if((HAND->cards[0].value == HAND->cards[1].value) && (HAND->cards[2].value == HAND->cards[3].value))
        win=3;
    else if((HAND->cards[1].value == HAND->cards[2].value) && (HAND->cards[3].value == HAND->cards[4].value))
        win=3;
    else if((HAND->cards[0].value == HAND->cards[1].value) && (HAND->cards[3].value == HAND->cards[4].value))
        win=3;

    //trei bucati
    if (((HAND->cards[0].value == (HAND->cards[1].value)) && ((HAND->cards[1].value) == (HAND->cards[2].value))))
        win=4;
    else if (((HAND->cards[1].value == (HAND->cards[2].value)) && ((HAND->cards[2].value) == (HAND->cards[3].value))))
        win=4;
    else if (((HAND->cards[2].value == (HAND->cards[3].value)) && ((HAND->cards[3].value) == (HAND->cards[4].value))))
        win=4;

    // chinta
    sw=0;
    for(int i=0;i<4;i++)
    {
        if((HAND->cards[i].value) != (HAND->cards[i+1].value - 1))
        {
            sw=1;
        }
        if(sw==1)
            i=4; //iesim din for
    }
    if(sw==0)
        win=5;

    //culoare
    sw=0;
    for(int i=0;i<4;i++)
    {
        if((HAND->cards[i].symbol) != (HAND->cards[i+1].symbol))
        {
            sw=1;
        }
        if(sw==1)
            i=4;
    }
    if(sw==0)
        win=6;

    //full house
    if((HAND->cards[0].value) == (HAND->cards[1].value)) /// cazul BBAAA
    {
        if(((HAND->cards[2].value) == (HAND->cards[3].value)) && ((HAND->cards[3].value) == (HAND->cards[4].value)))
            win=7;
    }
    if(((HAND->cards[0].value) == (HAND->cards[1].value)) && ((HAND->cards[1].value) == (HAND->cards[2].value))) //cazul BBBAA
    {
        if((HAND->cards[3].value) == (HAND->cards[4].value))
            win=7;
    }

    //careu
    if (HAND->cards[0].value == HAND->cards[1].value && HAND->cards[1].value == HAND->cards[2].value && HAND->cards[2].value == HAND->cards[3].value) {
        win=8;
    }
    else if (HAND->cards[1].value == HAND->cards[2].value && HAND->cards[2].value == HAND->cards[3].value && HAND->cards[3].value == HAND->cards[4].value) {
        win=8;
    }

    // chinta de culoare sau chinta roiala
    sw=0;
    sw2=0;
    for(int i=0;i<4;i++)
    {
        if((HAND->cards[i].symbol) != (HAND->cards[i+1].symbol))
        {
            sw=1;
        }
        if(sw==1)
            i=4;
    }
    if(sw==0)
    {
        for(int i=0;i<4;i++)
        {
        if((HAND->cards[i].value) != (HAND->cards[i+1].value - 1))
        {
            sw2=1;
        }
        if(sw2==1)
            i=4; //iesim din for
        }
    }
    if((sw==0) && (sw2==0))
    {
        if(HAND->cards[4].value == 14)
            win=10;
        else
            win=9;
    }

    //carte mare -- daca nu are nimic, o sa se ia cartea cea mai mare;
    if(win==0)
        {
            big_card = HAND->cards[4].value;
            win=1;
        }
    return win;
}
int main()
{
    srand(time(NULL)); // ca sa ne afiseze de fiecare data o alta valoare random, sa nu fie la toate rularile aceeasi

    int nr_players;
    printf("How many players play poker?: ");
    scanf("%d", &nr_players);

    card pack[52];
    int index = 0;
    for(int value=2; value<=14; value++){
        for(char symbol = 'A'; symbol <= 'D'; symbol++)
        {
            pack[index].value = value;
            switch(symbol){
            case 'A':
                strcpy(pack[index].symbol, "trefla");
                break;
            case 'B':
                strcpy(pack[index].symbol, "romb");
                break;
            case 'C':
                strcpy(pack[index].symbol, "inima neagra");
                break;
            case 'D':
                strcpy(pack[index].symbol, "inima rosie");
                break;
            default:
                sprintf(pack[index].symbol, "%c", symbol);
                break;
            }
            index++;
        }
    }

    hand* players_hands = malloc(nr_players * sizeof(hand));

    shuffle(pack, 52);

    for(int i=0; i<nr_players; i++)
    {
        for(int j=0; j<5; j++){
            players_hands[i].cards[j] = pack[i*5 +j];
        }
    }

    for(int i=0; i<nr_players; i++)
    {
        printf("\nCards of player %d: \n", i+1);
        hand_showing(players_hands[i]);
    }

    for (int i = 0; i < nr_players; i++) {
        printf("\nSorted cards of player %d: \n", i + 1);
        sort_hand(&players_hands[i]);
        hand_showing(players_hands[i]);
    }

    int aux_win=0, max_win=0;
    int max_win_player;
    for (int i = 0; i < nr_players; i++) {
        int aux_win=winner(&players_hands[i]);
        if(aux_win>=max_win)
        {
            max_win=aux_win;
            max_win_player=i+1;
        }
    }
    // afisare ce fel de combinatie a facut castigatorul
    card winning_hands[10];
    for(int final_win=1;final_win<=10;final_win++)
    {
        switch(final_win){
            case 1:
                strcpy(winning_hands[final_win].final_win, "big card");
                break;
            case 2:
                strcpy(winning_hands[final_win].final_win, "one pair");
                break;
            case 3:
                strcpy(winning_hands[final_win].final_win, "two pair");
                break;
            case 4:
                strcpy(winning_hands[final_win].final_win, "three of a kind");
                break;
            case 5:
                strcpy(winning_hands[final_win].final_win, "flush");
                break;
            case 6:
                strcpy(winning_hands[final_win].final_win, "color");
                break;
            case 7:
                strcpy(winning_hands[final_win].final_win, "full house");
                break;
            case 8:
                strcpy(winning_hands[final_win].final_win, "four of a kind");
                break;
            case 9:
                strcpy(winning_hands[final_win].final_win, "color flush");
                break;
            case 10:
                strcpy(winning_hands[final_win].final_win, "royal flush");
                break;
            default:
                sprintf(winning_hands[final_win].final_win, "%c", final_win);
                break;
            }
    }

    printf("\nThe player %d win the match with %s!!!\n", max_win_player, winning_hands[max_win].final_win);


    free(players_hands);
    return 0;
}
