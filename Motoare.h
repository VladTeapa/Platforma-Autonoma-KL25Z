#include "MKL25Z4.h"
#include "Defines.h"
void TPM0_IRQHandler(void); // Intrerupere tpm pentru numarare impulsuri
void TPM1_IRQHandler(void); // Intrerupere tpm pentru calculul vitezei
void SetareViteza(double viteza); // Setare viteza, valoarea trebuie sa fie intre 0 si 1
void SetareSens(int sens); // Setare sens, folositi macrodefinitiile
void SetareUnghi(long double unghi); // Setare unghi, valoarea trebuie sa fie intre -1 si 1
void InitializarePiniParteMecanica(void); // Initializare pini pentru motoare si TPM


