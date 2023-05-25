#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//This fucntion can check if the ele is in a array
bool include(int ele, int* list, int length){
    int i;
    for(i = 0; i < length; i++)
    {
        if(ele == list[i]){ return true; }
    }
    return false;
}

//This funtion will return the location of an element
int find_num(int ele, int*list, int length){
    int i;
    for(i = 0; i < length; i++)
    {
        if(ele == list[i]){ return i; }
    }
    return -1;
}

int generate(int pattern[], int num, float timespan)
{
  int i;
  float u, r;

  for (i = 0; i < num; i++) {
      u = (float)rand() / RAND_MAX; // generate random number in (0,1]
      r = -log(u)*timespan; // exponential random variable for Poisson events
      pattern[i] = (int)r + 1; // round up to integer; avoid 0 for multiple customers
  }
}

int main(int argc, char *argv[]){ 
    if( argv[1][0] == 'D' ) //debug mode
    {
        int i;
        printf("Parent, pid %d: debug mode\n", getpid());
        int cid;
        cid = fork();
        if(cid < 0){ printf("Fork faild\n"); exit(1); }
        else if(cid == 0)
        {
            int num_of_cus = ( argc - 3 ) / 2;                       //find the number of the coming customers
            int* interval = (int*)malloc(num_of_cus * sizeof(int));  //store all the basic information in 5 array
            int* deal = (int*)malloc(num_of_cus * sizeof(int));
            int* reach = (int*)malloc(num_of_cus * sizeof(int));
            int* start = (int*)malloc(num_of_cus * sizeof(int));
            int* leave = (int*)malloc(num_of_cus * sizeof(int));

            int count1 = 0;
            for(i = 2; i < argc; i++)
            {
                if(atoi(argv[i]) == -1){ break; }
                interval[count1] = atoi(argv[i]);
                deal[count1] = atoi(argv[i + num_of_cus + 1]);
                count1++;
            }

            int leave_time = 0;
            int reach_time = 0;
            for(i = 0; i < num_of_cus; i++)
            {
                if(i == 0)
                {
                    reach[i] = 0;
                    start[i] = 0;
                    leave[i] = deal[i];
                }
                else
                {
                    reach_time += interval[i];
                    reach[i] = reach_time;
                    if( reach_time > leave[i - 1]){ start[i] = reach_time; }
                    else{ start[i] = leave[i - 1]; }
                    leave[i] = start[i] + deal[i];
                    leave_time = leave[i];
                }
            }

            int queue_len = 0;
            int max_len = 0;
            int t_queue = 0;
            int t_wait = 0;

            printf("Child 1, pid %d: %d customers arriving at", getpid(), num_of_cus);
            for(i = 0; i < num_of_cus; i++){ printf(" %d", reach[i]); }
            printf("\nChild 1, pid %d: %d customers requiring service for", getpid(), num_of_cus);
            for(i = 0; i < num_of_cus; i++){ printf(" %d", deal[i]); }

            int come_num = 1;
            int leave_num = 1;
            int wait_num = 1;
            for(i = 0; i <= leave_time; i++){
                if(include(i, reach, num_of_cus) || include(i, leave, num_of_cus))
                {
                    printf("\nChild 1, pid %d: time %d ", getpid(), i);
                }

                if(include(i, leave, num_of_cus))
                {
                    printf("customer %d departs, ", leave_num);
                    leave_num++;
                    int number2 = find_num(i, leave, num_of_cus);
                    if(number2 < num_of_cus - 1)
                    {
                        if(leave[number2] == start[number2 + 1] && queue_len != 0) { queue_len--; }
                    }
                }

                if(include(i, reach, num_of_cus))
                {
                    printf("customer %d arrives, ", come_num);
                    come_num++;
                    int number1 = find_num(i, reach, num_of_cus);
                    if(reach[number1] < start[number1]) { queue_len++; }
                }

                if(include(i, start, num_of_cus))
                {
                    int wait_time = start[wait_num - 1] - reach[wait_num - 1];
                    printf("customer %d waits for %d, ", wait_num, wait_time);
                    t_wait += wait_time;
                    wait_num++;
                }

                if(include(i, reach, num_of_cus) || include(i, leave, num_of_cus))
                {
                    printf("queue length %d", queue_len);
                }

                t_queue += queue_len;
                if(queue_len > max_len){ max_len = queue_len; }
            }
            printf("\nChild 1, pid %d: all customers served at time %d", getpid(), leave_time);
            printf("\nChild 1, pid %d: maximum queue length %d", getpid(), max_len);
            printf("\nChild 1, pid %d: average queue length %.3f", getpid(), (float)t_queue/leave_time);
            printf("\nChild 1, pid %d: total waiting time %d", getpid(), t_wait);
            printf("\nChild 1, pid %d: average waiting time %.3f", getpid(), (float)t_wait/num_of_cus);
            printf("\nChild 1, pid %d: child 1 completed execution\n", getpid());
            exit(0);
        }
        else
        {
            wait(NULL);
            printf("Parent, pid %d: chlid 1 completed execution\n", getpid());
            exit(0);
        }
    }
    else
    {
        int i, cid;
        int c_num = atoi(argv[2]);
        int t_num = (argc - 3)/4;
        int cir_time = c_num <= t_num ? c_num : t_num;
        printf("Parent, pid %d: %d children, %d tasks, simulation mode\n", getpid( ), c_num, t_num);
        for(i = 1; i <= cir_time; i++)
        {
            cid = fork();
            if(cid < 0){ printf("Fork faild\n"); exit(1); }
            else if(cid == 0)
            {
                int n;
                for(n = (i - 1)*4 + 3; n + 4 <= argc; n += 4 * c_num)
                {
                    int k;
                    int sim_num = atoi(argv[n]);    //find the number of the coming customers
                    int seed_num = atoi(argv[n+1]);
                    float arr = atof(argv[n+2]);
                    float ser = atof(argv[n+3]);
                    printf("Chlid %d, pid %d: simulating %d costomer, seed %d, arrival %.1f, service %.1f\n", i, getpid(), sim_num, seed_num, arr, ser);

                    int* interval = (int*)malloc(sim_num * sizeof(int));   //store all the basic information in 5 array
                    int* deal = (int*)malloc(sim_num * sizeof(int));
                    int* reach = (int*)malloc(sim_num * sizeof(int));
                    int* start = (int*)malloc(sim_num * sizeof(int));
                    int* leave = (int*)malloc(sim_num * sizeof(int));

                    srand(seed_num);
                    generate(interval, sim_num, arr);
                    interval[0] = 0;
                    generate(deal, sim_num, ser);

                    int leave_time = 0;
                    int reach_time = 0;
                    for(k = 0; k < sim_num; k++)
                    {
                        if(k == 0)
                        {
                            reach[k] = 0;
                            start[k] = 0;
                            leave[k] = deal[k];
                        }
                        else
                        {
                            reach_time += interval[k];
                            reach[k] = reach_time;
                            if( reach_time > leave[k - 1]){ start[k] = reach_time; }
                            else{ start[k] = leave[k - 1]; }
                            leave[k] = start[k] + deal[k];
                            leave_time = leave[k];
                        }
                    }

                    int queue_len = 0;
                    int max_len = 0;
                    int t_queue = 0;
                    int t_wait = 0;

                    int wait_num = 1;
                    for(k = 0; k <= leave_time; k++)
                    {
                        if(include(k, leave, sim_num))
                        {
                            int number2 = find_num(k, leave, sim_num);
                            if(number2 < sim_num - 1)
                            {
                                if(leave[number2] == start[number2 + 1] && queue_len != 0) { queue_len--; }
                            }
                        }

                        if(include(k, reach, sim_num))
                        {
                            int number1 = find_num(k, reach, sim_num);
                            if(reach[number1] < start[number1]) { queue_len++; }
                        }

                        if(include(k, start, sim_num))
                        {
                            int wait_time = start[wait_num - 1] - reach[wait_num - 1];
                            t_wait += wait_time;
                            wait_num++;
                        }

                        t_queue += queue_len;
                        if(queue_len > max_len){ max_len = queue_len; }
                    }

                    printf("Child %d, pid %d: all customers served at time %d", i, getpid(), leave_time);
                    printf("\nChild %d, pid %d: maximum queue length %d", i, getpid(), max_len);
                    printf("\nChild %d, pid %d: average queue length %.3f", i, getpid(), (float)t_queue/leave_time);
                    printf("\nChild %d, pid %d: total waiting time %d", i, getpid(), t_wait);
                    printf("\nChild %d, pid %d: average waiting time %.3f\n", i, getpid(), (float)t_wait/sim_num);
                }
                printf("Child %d, pid %d: child %d completed execution\n", i, getpid(), i);
                exit(0);
            }
        }

        for(i = 1; i <= cir_time; i++)
        {
            wait(NULL);
            printf("Parent, pid %d: child %d completed execution\n", getpid(), i);
        }

        if(i == cir_time + 1) {exit(0);}
    }
}