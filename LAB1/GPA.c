#include <stdio.h>

int main(int argc, char *argv[])
{
  int num_subj;
  float in_gp, sum_gp = 0.0;
  char in_grade;
  int i, valid = 0;
  num_subj = argc-1;
  

  if(argc <= 1) {printf("There is no valid subject!\n"); return 0; }

  printf("PolyU System:\n");
  for (i = 1; i <= num_subj; i++){
      in_grade = argv[i][0];
      switch (in_grade){
        case 'A': in_gp = 4.0; break;
        case 'B': in_gp = 3.0; break;
        case 'C': in_gp = 2.0; break;
        case 'D': in_gp = 1.0; break;
        case 'F': in_gp = 0.0; break;
        default: printf("Wrong grade %s\n",argv[i]);
      }
      printf("Grade for subject %d is %c", i, argv[i][0]);

      if (argv[i][1] == '+') { in_gp += 0.3; printf("+"); }
      if (argv[i][1] == '-') { in_gp -= 0.3; printf("-"); }
      
      if(in_gp == 0.7F) {printf(", invalid\n");}
      else {printf(", GP %.1f\n", in_gp); valid++; sum_gp += in_gp;}
   }

  if (valid == 0) { printf("No valid subject.\n"); }
  else{ printf("Your GPA for %d subjects is %5.2f\n", valid, sum_gp/valid); }
  
  valid = 0;
  sum_gp = 0;

  printf("Other System:\n");
  for (i = 1; i <= num_subj; i++){
      in_grade = argv[i][0];
      switch (in_grade){
        case 'A': in_gp = 11; break;
        case 'B': in_gp = 8; break;
        case 'C': in_gp = 5; break;
        case 'D': in_gp = 2; break;
        case 'F': in_gp = 0; break;
        default: printf("Wrong grade %s\n", argv[i]);
      }
      printf("Grade for subject %d is %c", i, argv[i][0]);

      if(argv[i][1] == '+') { in_gp += 1; printf("+");}
      if(argv[i][1] == '-') { in_gp -= 1; printf("-");}

      printf(", GP %.0f\n", in_gp);
      valid++;
      sum_gp += in_gp;
   }
  printf("Your GPA for %d subjects is %5.2f\n", valid, sum_gp/valid);
}
