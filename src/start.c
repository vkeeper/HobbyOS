//char* dispPos = (char*)0xB8000;
/*
void puts(char* str){
    //unsigned int absolutePos = (80*4+0)*2;
   // dispPos += absolutePos;
    unsigned char c;
    while((c=*(str++))!=0){
        if(c==13){
            dispPos -=((unsigned int)dispPos)%160-64;
        } else if(c==10){
            dispPos += 160;
        }else{
            *(dispPos++)=c;
            *(dispPos++)=0x0F;
        }
    }
    
}

void cstart(){
    puts("\nCall C by NASM success");
    for(;;){}
}
*/

void cmain(){
    char *vm = (char*)0xb8000;
    *vm = 'X';
}
