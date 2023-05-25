#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int get_value(char single_card[3]){  // find a value of a card
    char fancy = single_card[0];
    char num = single_card[1];
    int value = 0;

    switch(fancy){
        case 'D': value+=0; break;
        case 'C': value+=20; break;
        case 'H': value+=40; break;
        case 'S': value+=60; break;
        case 'X': value+=100; break;
        default: printf("error!\n"); break;
    }

    switch(num){
        case '2': value+=2; break;
        case '3': value+=3; break;
        case '4': value+=4; break;
        case '5': value+=5; break;
        case '6': value+=6; break;
        case '7': value+=7; break;
        case '8': value+=8; break;
        case '9': value+=9; break;
        case 'T': value+=10; break;
        case 'J': value+=11; break;
        case 'Q': value+=12; break;
        case 'K': value+=13; break;
        case 'A': value+=14; break;
        case 'X': value+=100; break;
        default: printf("error!\n"); break;
    }
    return value;
}

int get_lead_value(char single_card[3]){
    char num = single_card[1];
    int value = 0;
    switch(num){
        case '2': value+=2; break;
        case '3': value+=3; break;
        case '4': value+=4; break;
        case '5': value+=5; break;
        case '6': value+=6; break;
        case '7': value+=7; break;
        case '8': value+=8; break;
        case '9': value+=9; break;
        case 'T': value+=10; break;
        case 'J': value+=11; break;
        case 'Q': value+=12; break;
        case 'K': value+=13; break;
        case 'A': value+=14; break;
        case 'X': value+=100; break;
        default: printf("error!\n"); break;
    }
    return value;
}

void card_swap(char hand_card[13][3], int n1, int n2){  // card swap
    char temp[3];
    strcpy(temp,hand_card[n1]);
    strcpy(hand_card[n1],hand_card[n2]);
    strcpy(hand_card[n2],temp);
}

void arrange_order(char hand_card[13][3]){        // order the card
    int i, j, k;
    for(i = 1; i < 13; i++)
    {
        for(j = 0; j < 13 - i; j++)
        {
            int value1 = get_value(hand_card[j]);
            int value2 = get_value(hand_card[j+1]);
            if(value1 < value2) { card_swap(hand_card, j, j+1); }
        }
    }
}

int play_card(char hand_card[13][3], char fancy){
    int location, i, min_value = 300, temp;
    if(fancy == 'L') //lead hand
    {
        for(i = 12; i >= 0; i--)
        {
            temp = get_lead_value(hand_card[i]);
            if(temp < min_value)
            {
                min_value = temp;
                location = i;
            }
        }
        return location;
    }
    else    //not the lead hand
    {
        int lower_lim, upper_lim, dis_flag = 0;
        switch(fancy){
            case 'D': lower_lim = 1; upper_lim = 20; break;
            case 'C': lower_lim = 21; upper_lim = 40; break;
            case 'H': lower_lim = 41; upper_lim = 60; break;
            case 'S': lower_lim = 61; upper_lim = 80; break;
        }

        for(i = 0; i < 13; i++){
            temp = get_value(hand_card[i]);
            if(temp > lower_lim && temp < upper_lim){
                if(temp < min_value)
                {
                    min_value = temp;
                    location = i;
                }
                dis_flag++;
            }
        }

        if(dis_flag !=0) { return location; }
        else{  // discard happend
            for(i = 0; i < 13; i++){
                temp = get_value(hand_card[i]);
                if(temp == 72) { return i; }
            }
            for(i = 0; i < 13; i++){
                temp = get_value(hand_card[i]);
                if(temp > 41 && temp < 60) { return i; }
            }
            for(i = 0; i < 13; i++){
                temp = get_value(hand_card[i]);
                if(temp > 61 && temp < 80) { return i; }
            }
            for(i = 0; i < 13; i++){
                temp = get_value(hand_card[i]);
                if(temp > 21 && temp < 40) { return i; }
            }
            for(i = 0; i < 13; i++){
                temp = get_value(hand_card[i]);
                if(temp > 1 && temp < 20) { return i; }
            }
            printf("error happen when choose card\n");
            return -1;
        }
    }
}

int compute_point(char inturn_card[4][3]){
    int point = 0, i;
    char fancy;
    for(i = 0; i < 4; i++)
    {
        fancy = inturn_card[i][0];
        if(fancy == 'H') { point++; }
        else if(fancy == 'S')
        {
            if(inturn_card[i][1] == 'Q') { point += 13; }
        }
    }
    return point;
}

int inturn_winner(char inturn_card[4][3], int lead){
    int location, lower_lim, upper_lim, i, temp, max_point = 0;
    char lead_fancy = inturn_card[lead][0];
    switch(lead_fancy){
        case 'D': lower_lim = 1; upper_lim = 20; break;
        case 'C': lower_lim = 21; upper_lim = 40; break;
        case 'H': lower_lim = 41; upper_lim = 60; break;
        case 'S': lower_lim = 61; upper_lim = 80; break;
    }

    for(i = 0; i < 4; i++)
    {
        temp = get_value(inturn_card[i]);
        if(temp > lower_lim && temp < upper_lim)
        {
            if(max_point < temp)
            { 
                max_point = temp;
                location = i; 
            }
        }
    }
    return location;
}

int main(int argc, char *argv[]){
    int i, pid, ID, n, k;
    int result[4] = {0};
    int P2C[4][2], C2P[4][2], cid[4];
    char cards[52][3], inbuf[156];
    while((n = read(STDIN_FILENO, inbuf, 156)) > 0) {   // read in from the txt file
        i = 0, k = 0;
        inbuf[n] = '\0';
        while(i < n && inbuf[i] == ' ') i++;
        while (i < n) {
            cards[k][2] = '\0';
            cards[k][0] = inbuf[i++];
            cards[k][1] = inbuf[i++];
            k++;
            while(i < n && (inbuf[i] == ' ' || inbuf[i] == '\n')) i++;
        }
    }

    for(i = 0; i < 4; i++)
    {
        if(pipe(&P2C[i][0]) < 0) { printf("Pipe creation for P2C error\n"); exit(1); }
        if(pipe(&C2P[i][0]) < 0) { printf("Pipe creation for C2P error\n"); exit(1); }
    }

    for(i = 0; i < 4; i++)
    {
        pid = fork();
        if(pid < 0){ printf("Fork faild\n"); exit(1); }
        else if(pid == 0)
        {
            close(P2C[i][1]);
            close(C2P[i][0]);
            char hand_card[13][3];
            char single_card[3];
            int counter = 0;
            while((n = read(P2C[i][0], single_card, 80)) > 0)
            {
                strcpy(hand_card[counter++], single_card);
                if(counter == 13) break;
            }

            //display the hand cards
            printf("Child %d pid %d: received ", i+1, getpid());
            for(k = 0; k < 13; k++) { printf("%s ", hand_card[k]); }
            printf("\n");
            arrange_order(hand_card);
            printf("Child %d pid %d: arranged ", i+1, getpid());
            for(k = 0; k < 13; k++) { printf("%s ", hand_card[k]); }
            printf("\n");

            char ready[2];
            strcpy(ready, "OK");
            write(C2P[i][1], ready, 80);

            int round_count, location;
            // the game start
            for(round_count = 0; round_count < 13; round_count++)
            {
                char request[5], p_card[3];
                read(P2C[i][0], request, 80);
                if(strcmp(request, "lead") == 0)
                {
                    location = play_card(hand_card, 'L');
                    strcpy(p_card, hand_card[location]);
                    hand_card[location][0] = 'X';
                    hand_card[location][1] = 'X';
                    write(C2P[i][1], p_card, 80); 
                    printf("Child %d pid %d: play %s\n", i+1, getpid(), p_card);
                }
                else
                {
                    //printf("Child %d pid %d: i am wait\n", i+1, getpid());
                }

                read(P2C[i][0], request, 80);
                if(strcmp(request, "wait") == 0)
                {
                    //printf("Child %d pid %d: i am wait\n", i+1, getpid());
                }
                else
                {
                    char fancy = request[0];
                    location = play_card(hand_card, fancy);
                    strcpy(p_card, hand_card[location]);
                    hand_card[location][0] = 'X';
                    hand_card[location][1] = 'X';
                    write(C2P[i][1], p_card, 80); 
                    printf("Child %d pid %d: play %s\n", i+1, getpid(), p_card);
                }
            }
            close(P2C[i][0]);
            close(C2P[i][1]);
            exit(0);
        }
        else
        {
            close(P2C[i][0]);
            close(C2P[i][1]);
            cid[i] = pid;
        }
    }
    
    if(pid > 0){
        
        printf("Parent pid %d: child players are %d %d %d %d\n", getpid(), cid[0], cid[1], cid[2], cid[3]);
        int counter1 = 0;
        for(i = 0; i < 13; i++)     //give the card to child
        {
            int m;
            for(m = 0; m < 4; m++)
            {
                write(P2C[m][1], cards[counter1++], 80);
            }
        }

        char Start[4][2]; char sig[2];    //Start game
        int lead_hand = 1, round = 1;
        for(i = 0; i < 4; i++){
            read(C2P[i][0], sig, 80);
            strcpy(Start[i],sig);
        }

        if(strcmp(Start[0],Start[1]) == strcmp(Start[1],Start[2]) == strcmp(Start[2],Start[3]) == strcmp(Start[3],"OK")) 
        { 
            // the game start
            for(round = 1; round <= 13; round++)
            {
                int inturn_point, winner;
                printf("Parent pid %d: round %d child %d to lead\n", getpid(), round, lead_hand);
                for(i = 0; i < 4; i++)
                {
                    if(i == lead_hand - 1)
                    {
                        char sig_l[5] = {"lead"};
                        write(P2C[i][1], sig_l, 80);
                    }
                    else
                    {
                        char sig_l[5] = {"wait"};
                        write(P2C[i][1], sig_l, 80);   
                    }
                }

                char lead_card[3], rest_card[3];
                char inturn_card[4][3];
                read(C2P[lead_hand-1][0], lead_card, 80);
                printf("Parent pid %d: child %d plays %s\n", getpid(), lead_hand, lead_card);
                strcpy(inturn_card[lead_hand-1], lead_card);

                for(i = 0; i < 4; i++)
                {
                    if(i == lead_hand -1)
                    {
                        char sig_l[5] = {"wait"};
                        write(P2C[i][1], sig_l, 80);
                    }
                    else
                    {
                        write(P2C[i][1], lead_card, 80); 
                    }
                }

                for(i = 0; i < 4; i++)
                {
                    if(i != lead_hand - 1)
                    {
                        read(C2P[i][0], rest_card, 80);
                        strcpy(inturn_card[i], rest_card);
                        printf("Parent pid %d: child %d plays %s\n", getpid(), i+1, rest_card);
                    }
                }

                //compute the result in this round
                inturn_point = compute_point(inturn_card);
                winner = inturn_winner(inturn_card, lead_hand-1);
                result[winner] += inturn_point;
                lead_hand = winner+1;
                printf("Parent pid %d: child %d wins the trick\n", getpid(), lead_hand);
            }
            
            //final result
            int big_winner = -1;
            for(i = 0; i < 4; i++)
            {
                if(result[i] == 26) { big_winner = i; }
            }
            if(big_winner != -1){
                for(i = 0; i < 4; i++)
                {
                    if(i != big_winner) { result[i] = 26; }
                    else { result[i] = 0; }
                }
            }
            printf("Parent pid %d: score = <%d %d %d %d>\n", getpid(), result[0], result[1], result[2], result[3]);
        }
        close(P2C[i][1]);
        close(C2P[i][0]);
    }
    for(i = 0; i < 4; i++) {
        wait(NULL);
    }
    return 0;
}