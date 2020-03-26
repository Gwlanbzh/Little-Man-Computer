#include <stdio.h>
#include <stdlib.h>
#define RAM_LENGTH 100
#define IO_ERROR 5

int RAM[100];
int PC = 0, INS = 0, ADD = 0, ACC = 0;
char input_temp[4];

void HLT();

void ADD_ins();

void SUB();

void STA();

void ERR();

void LDA();

void BRA();

void BRZ();

void BRP();

void INPOUT();


int main(int argc, char * argv[]){
    switch (argc) {
        case 1:
            fprintf(stderr, "Error: please enter a file to work on.\n");
            exit(5);
        case 2:
            break;    
        default:
            fprintf(stderr, "Error: too many arguments.\n");
            exit(7);
    }

    FILE * prog = fopen(argv[1], "r");
    if(prog == NULL) 
        exit(-1);
    
    char char_RAM[RAM_LENGTH][4];
    int ram_index = 0;
    
    while(!(feof(prog)) && ram_index < RAM_LENGTH){
        fgets(char_RAM[ram_index], 4, prog);
        ram_index++;
    }
    fclose(prog);
    int RAM[100];
    int i = 0;
    while(i < ram_index){
        RAM[i] = atoi(char_RAM[i]);
        i++;
    }
    

    void ( * instruction[10])() = {
        HLT, 
        ADD_ins, 
        SUB, 
        STA, 
        ERR, 
        LDA, 
        BRA, 
        BRZ, 
        BRP, 
        INPOUT
    };
    int temp;
    while(1){
        temp = RAM[PC];
        INS = (int) temp / 100;
        ADD = (int) temp % 100;
	instruction[INS]();
        PC++;
    }
}


void HLT(){
    /*Stops the LMC simulator executing the program.*/
    printf("HLT\n");
    exit(EXIT_SUCCESS);
    return;
}

void ADD_ins(){
    /*Adds the contents of address xx to the accumulator.*/
    printf("ADD\n");
    ACC = ACC + RAM[ADD];
    return;
}

void SUB(){
    /*Subtracts the contents address xx from the accumulator.*/
    printf("SUB\n");
    ACC = ACC - RAM[ADD];
    return;
}

void STA(){
    /*Stores the contents of the accumulator to address xx.*/
    printf("STA\n");
    RAM[ADD] = ACC;
    return;
}

void ERR(){
    /*The 4 is not used as an instruction in the LMC. Exits.*/
    printf("ERR\n");
    exit(IO_ERROR);
    return;
}

void LDA(){
    /*Loads the contents of address xx onto the accumulator.*/
    printf("LDA\n");
    ACC = RAM[ADD];
    return;
}

void BRA(){
    /*Set the program counter to address xx.*/
    printf("BRA\n");
    PC = ADD;
    return;
}

void BRZ(){
    /*If the contents of the accumulator are ZERO, set the program counter to address xx.*/
    printf("BRZ\n");
    if(ACC == 0){
        PC = ADD;
    }
    return;
}

void BRP(){
    /*If the contents of the accumulator are ZERO or positive (i.e. the negative flag is not set), sets the program counter to address xx.*/
    printf("BRP\n");
    if(ACC >= 0){
        PC = ADD;
    }
    return;
}

void INPOUT(){
    /*If the argument is '01', copies the value from the "in box" onto the accumulator.
    If the argument is '02', Copy the value from the accumulator to the "out box". Note: the contents of the accumulator are not changed.*/
    switch(ADD){
        case 1:
            printf("INBOX :\n");
            scanf("%3s", input_temp);
            ACC = atoi(input_temp);
            break;
        case 2:
            printf("OUTBOX:\n");
            printf("%3d\n", ACC);
            break;
        default:
            fprintf(stderr, "Error: on instruction %d: instruction '9' can only be used with arguments '01' and '02'", PC);
            exit(IO_ERROR);
    }
    return;
}
