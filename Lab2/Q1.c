#include<stdio.h>
#include<ctype.h>

int main() {
    FILE *fp1 = fopen("Input1.txt","r"); //to open Input1.txt file
    FILE *fp2 = fopen("Outpur.txt","w"); // to copy text from Input1.txt to Output.txt
    
    if (fp1 == NULL){
        printf("Not opening file");   //check if fp1 is NULL
        return 1;
    }
    
    char ch;
    
    while( (ch = fgetc(fp1)) != EOF){    //While loop to get each character of file
        if(isupper(ch)){
            ch = tolower(ch);   // check if ch is uppercase and convert to lowercase
        }
        else if(islower(ch)){
            ch = toupper(ch);  //check if ch is lowercase and convert to uppercase
        }
        fputc(ch,fp2);           // copy character to output.txt
        printf("%c",ch);        // print character
    }
    
    fclose(fp1);          // closing file pointers
    fclose(fp2);
    
    return 0;
}