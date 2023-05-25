#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[]){
    int i, count1;
    for(i = 1; i < argc; i++){ if(strcmp(argv[i], "Student") == 0) { count1 = i; } }

    char(*class)[20] = (char(*)[20])malloc((count1 - 1) * sizeof(char) * 20);
    char(*student)[20] = (char(*)[20])malloc((argc - count1 - 1) * sizeof(char) * 20);

    int c1 = 0, s1 = 0;
    for(i = 1; i < argc; i++)
    {
        if(i < count1) { strcpy(class[c1++],argv[i]); }
        else if(i > count1) { strcpy(student[s1++],argv[i]); }
    }

    for(i = 1; i < c1; i++)
    {
        int n;
        for(n = 0; n < c1 - i; n++)
        {
            char temp[20];
            if(strcmp(class[n],class[n+1]) > 0)
            {
                strcpy(temp,class[n]);
                strcpy(class[n],class[n+1]);
                strcpy(class[n+1],temp);
            }
        }
    }

    //for(i = 0; i < c1; i++){ printf("%s\n", class[i]); }

    FILE *s_list = fopen("student.dat", "r");
    if(s_list == 0) { printf("error"); exit(1); }

    char c[20];
    char(*student1)[20] = (char(*)[20])malloc((argc - count1 - 1) * sizeof(char) * 20);
    int s2 = 0;
    while(fgets(c,sizeof(c),s_list)!=NULL)
    {
        int len = strlen(c);
        if(c[len-1] == '\n') { c[len-1] = 0; }
        for (i = 0; i < s1; i++)
        {
            if(strstr(c, student[i]) != NULL) { strcpy(student1[s2++],c); }
        }
    }
    fclose(s_list);

    for(i = 0; i < s2; i++)
    {
        printf("------------------------------------\n");
        printf("Transcript for %s\n", student1[i]);
        char number[5];
        strncpy(number, student1[i], 4);
        //printf("%s\n", number);

        int k;
        int valid=0, sum=0, t_num=0;
        for(k = 0; k < c1; k++)
        {
            FILE *c_info = fopen(class[k], "r");
            char output[40], title[40], grade[3], number2[2];
            int count2 = 0;

            while(fgets(output,sizeof(output),c_info)!=NULL)
            {
                int len = strlen(output);
                if(output[len-1] == '\n') { output[len-1] = 0; }
                if(count2 == 0) { count2++; strcpy(title, output); }
                
                if(strstr(output, number) != NULL) 
                {
                    //printf("%d\n", strlen(output));
                    if(strlen(output) < 6)
                    { 
                        printf("%s\n", title); 
                    }
                    else
                    {
                        sscanf(output, "%s %s", number2, grade);
                        printf("%s: %s\n", title, grade); 
                    }
                }
            }
        }
        
    }
    printf("------------------------------------\n");



    //printf("%d\n", c1);
    return 0;
}