#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{

    float * array;
    size_t size;

} dynamicArray;

int isNumber(char* s){

    for(size_t i = 0; i < strlen(s); i++){
        if(!(s[i] >= 48 && s[i] <= 57)) {
            printf("\n\n%s is NOT a number\nAT CHAR %c (%d) INDEX %d\n",s,s[i],s[i],i);
            return 0;
        }
    }

    return 1;
}

int validateArgs(int argc, char **argv){

    for(int i = 1; i < argc; i++){
        if(!isNumber(argv[i])){
            return 0;
        }
    }

    return 1;
}

float mbpsToMB(float mbps){
    return mbps / 8;
}

float mbToGB(float mb){
    return mb/1000;
}

float calculateTime(float totalSize, float currentDownloadAmount,float mbps, dynamicArray array){
    // function assumes that currentDownloadAmount and totalSize are in GB

    float mbs = mbpsToMB(mbps);
    float sizeLeft = totalSize - currentDownloadAmount;
    float secondsToFinish = sizeLeft / mbToGB(mbs);
    
    
    for(size_t i = 0; i < array.size; i++){
        secondsToFinish += array.array[i];
    }

    return secondsToFinish;
}

dynamicArray extras(int argc,char** argv){

    //skip needed values AKA 4

    dynamicArray array;

    const size_t SKIP = 4;
    const size_t size = argc - SKIP;
    if(size <=0){return array;}

    float * nums = malloc(size * sizeof(float));

    for(int i = 4; i < argc; i++){
        float currentFloat = strtof(argv[i],NULL);
        nums[i-SKIP] = currentFloat;

    }

    array.array = nums;
    array.size  = size; // all this because you cant calculate dynamic array length at runtime


    return array;
}

void prettyPrintTime(float seconds){

    // ty https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/c-programming-basic-exercises-17.php

    int  h, m, s;

    h = (seconds/3600); 
    m = (seconds -(3600*h))/60;
    s = (seconds -(3600*h)-(m*60));

    printf("Time to finish downloading program: %dH:%dM:%dS\n",h,m,s);

}

int main(int argc, char **argv){

    // totalSize, currentDownloadAmount, mbps, extra**

    if(argc <=3){
        printf("Not enough arguments given to the program. Usage [totalSize] [currentDownloadAmount] [mbps] [extra**]\n");
        return -1;
    }

    if(!validateArgs(argc,argv)){
        printf("Detected a non number input. All arguments MUST be numbers.\n");
    }

    float totalSize = strtof(argv[1],NULL);
    float currentDownloadAmount = strtof(argv[2],NULL);
    float mbps = strtof(argv[3],NULL);

    dynamicArray _extras = extras(argc,argv);
    
    float seconds = calculateTime(totalSize,currentDownloadAmount,mbps,_extras);

    prettyPrintTime(seconds);

    if(_extras.array != NULL){
        free(_extras.array);
    }

    printf("Call shutdown to close system in that time? y/n: ");

    char decision = getchar();

    if(decision == 'y' || decision == 'Y'){
        char buffer[1000]; // give a KB cos why not 
        int errorNo = snprintf(buffer, 1000 -1, "shutdown -s -t %d", (int)seconds);
        if(errorNo <=0 || errorNo >= 1000){
            printf("Error writing system command to buffer\n");
            return -1;
        }
        system(buffer);

    }

    return 0;
}