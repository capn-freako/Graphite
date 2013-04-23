#include "carbon_user.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
   double frequency = 0;
   double voltage = 0;
   int rc;

   // invalid tile id
   rc = CarbonGetDVFS(-1, CORE, &frequency, &voltage);
   printf("test 1) Voltage: %g, Frequency: %g, RC: %i\n", voltage, frequency, rc);
   if (rc != -1){
      fprintf(stderr, "Expected RC = -1, got RC = %i", rc) ;
      exit(EXIT_FAILURE);
   }

   // invalid module type
   rc = CarbonGetDVFS(0, TILE, &frequency, &voltage);
   printf("test 2) Voltage: %g, Frequency: %g, RC: %i\n", voltage, frequency, rc);
   if (rc != -2){
      fprintf(stderr, "Expected RC = -2, got RC = %i", rc) ;
      exit(EXIT_FAILURE);
   }

   // invalid frequency
   rc = CarbonSetDVFS(0, 0x2f, &frequency, AUTO);
   printf("test 3) Voltage: %g, Frequency: %g, RC: %i\n", voltage, frequency, rc);
   if (rc != -4){
      fprintf(stderr, "Expected RC = -4, got RC = %i", rc) ;
      exit(EXIT_FAILURE);
   }

   // invalid module type (works only for pr_l1_sh_l2_msi model)
   // frequency = 1.0;
   // rc = CarbonSetDVFS(0, L2_DIRECTORY, &frequency, AUTO);
   // printf("test 4) Voltage: %g, Frequency: %g, RC: %i\n", voltage, frequency, rc);
   // if (rc != -2){
   //    fprintf(stderr, "Expected RC = -2, got RC = %i", rc) ;
   //    exit(EXIT_FAILURE);
   // }

   // invalid voltage option
   rc = CarbonSetDVFS(0, TILE, &frequency, (voltage_option_t) 5);
   printf("test 5) Voltage: %g, Frequency: %g, RC: %i\n", voltage, frequency, rc);
   if (rc != -3){
      fprintf(stderr, "Expected RC = -3, got RC = %i", rc) ;
      exit(EXIT_FAILURE);
   }

   // invalid frequency 
   frequency = 100;
   rc = CarbonSetDVFS(0, TILE, &frequency, AUTO);
   printf("test 6) Voltage: %g, Frequency: %g, RC: %i\n", voltage, frequency, rc);
   if (rc != -4){
      fprintf(stderr, "Expected RC = -4, got RC = %i", rc) ;
      exit(EXIT_FAILURE);
   }

   // above max frequency for current voltage
   frequency = 0.1;
   rc = CarbonSetDVFS(0, TILE, &frequency, AUTO);
   frequency = 2.0;
   rc = CarbonSetDVFS(0, TILE, &frequency, HOLD);
   printf("test 7) Voltage: %g, Frequency: %g, RC: %i\n", voltage, frequency, rc);
   if (rc != -5){
      fprintf(stderr, "Expected RC = -5, got RC = %i", rc) ;
      exit(EXIT_FAILURE);
   }
   

}
