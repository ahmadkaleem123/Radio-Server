#include <SoftwareSerial.h>
SoftwareSerial HC12(10,11);
char names[4][20];
char texts[4][100];
char username[] = "Ahmad"; 
char password[] = "abcd1234";
char a[100];
int i = 0;
int j = 0;
int k;
int x;
int y;
int c=0;
int d = 0;
int e;
int g;
int l;
int h;
int state = 0;
int process;
void setup() {
  Serial.begin(9600);
  HC12.begin(9600); 
  HC12.write("Welcome to the Radio Server.\n");
  delay(100);
  HC12.write("Please enter your username.\n");
  //HC12.write("Type W to create a file and R to read a file.\n");  
}

void loop() {
  while (HC12.available() && c < 100) {
    if(d == 0){
      c = 0;    
      for(int f = 0; f<100; f++){
        a[f] = '\0';
      }    
    }
    a[c] = HC12.read();
    d = 1;
    if(a[c] == '~'){
      d = 2;
    }
    c++;
  }
  if(d == 2){
    if(state == 0){
      e = 0;
      for(int f = 0; f<strlen(username); f++){
        if(a[f] != username[f]){
          e = 1;
          break;
        }
      }
      if(e == 0){
        HC12.write("Please enter your password.\n");
        state++;
        e = 2;
      }
      else{
        HC12.write("Username not found. Please try again.\n");
        e = 2;
      }
    }
    else if(state == 1){
      e = 0;
      for(int f = 0; f<strlen(password); f++){
        if(a[f] != password[f]){
          e = 1;
          break;
        }
      }
      if(e == 0){
        HC12.write("Login successful. Type W to create a file, R to read a file, D to delete a file, E to edit a file or Q to exit.\n");
        state++;
        e=2;
      }
      else{
        HC12.write("Incorrect password. Please try again.\n");
        e = 2;
      }
    }
    else if(state == 2){
      if(a[0] == 'W'){
         if(i<4){
          HC12.write("Please enter the name of the file you want to create.\n");
          process = 0;
          state++;
         }
         else{
          HC12.write("Storage full. Please try deleting some files. \n");
          HC12.write("Press R, D, E or Q.\n");
         }
         
      }
      else if(a[0] == 'R'){
        HC12.write("Please enter a file name. All current file names are below:\n");
        for(int f = 0; f<i;f++){
          g = strlen(names[f]);
          for(int h = 0; h<g-1; h++){
            HC12.write(names[f][h]);
          }
          HC12.write("\n");
        }
        process = 1;
        state++;
      }
      else if(a[0] == 'D'){
        HC12.write("Please enter the name of the file you want to delete. All current file names are below:\n");
        for(int f = 0; f<i;f++){
          g = strlen(names[f]);
          for(int h = 0; h<g-1; h++){
            HC12.write(names[f][h]);
          }
          HC12.write("\n");
        }
        state++;
        process = 2;
      }
      else if(a[0] == 'E'){
        HC12.write("Please enter the name of the file you want to edit. All current file names are below:\n");
        for(int f = 0; f<i;f++){
          g = strlen(names[f]);
          for(int h = 0; h<g-1; h++){
            HC12.write(names[f][h]);
          }
          HC12.write("\n");
        }
        state++;
        process = 3;
      }
      else if(a[0] == 'Q'){
        HC12.write("Logged out successfully.\n");
        state = 0;
        delay(1000);
        HC12.write("Welcome to the Radio Server.\n");
        delay(100);
        HC12.write("Please enter your username.\n");
      }
      else{
        HC12.write("Please enter a valid letter (R, W, E, D, or Q).\n");
      }
      
    }
    else if(state == 3){
      if(process == 0){   // Writing
        for(int f = 0; f<strlen(a); f++){
          names[i][f] = a[f];
        }
        HC12.write("Please enter the text you want to save.\n");
        i++;
        state++;
      }
      else if(process == 1){ // Reading
        x = 0;
        for(int b = 0; b<i;b++){
          g = strlen(names[b]);
          y = 0;
          for(int h=0; h<g;h++){
            if(a[h] != names[b][h]){
              y = 1;
            }
          }
          if(y==0){
            g = strlen(texts[b]);
            HC12.write("File found. Reading contents: \n");
            delay(100);
            for(int f = 0; f<g-1; f++){
              HC12.write(texts[b][f]);
            }
            HC12.write("\n");
            x++;
            delay(100);
            HC12.write("Type W to create a file, R to read a file, D to delete a file, E to edit a file or Q to exit.\n");
            state = 2;
            break;
          }
        }
        if(x == 0){
          HC12.write("File not found. Please try again.\n");
        }
      }
      else if(process == 2){ // Deleting
        x = 0;
        for(int b = 0; b<i;b++){
          g = strlen(names[b]);
          y = 0;
          for(int h=0; h<g;h++){
            if(a[h] != names[b][h]){
              y = 1;
            }
          }
          if(y == 0){
            HC12.write("File found. Deleting contents...\n");
            h = strlen(names[b]);
            for(int f = 0; f<h; f++){
              names[b][f] = '\0';
            }
            h = strlen(texts[b]);
            for(int f = 0; f<h; f++){
              texts[b][f] = '\0';
            }
            for(int f=b+1; f<i; f++){
              h = strlen(names[f]);
              for(int l = 0; l<h; l++){
                names[f-1][l] = names[f][l];
                names[f][l] = '\0';
              }
              h = strlen(texts[f]);
              for (int l = 0; l<h; l++){
                texts[f-1][l] = texts[f][l];
                texts[f][l] = '\0';
              }
              
            }
            i--;
            j--;
            x++;
            delay(100);
            HC12.write("Type W to create a file, R to read a file, D to delete a file, E to edit a file or Q to exit.\n");
            state = 2;
            break;
            }
          }
          if(x == 0){
            HC12.write("File not found. Please try again.\n");
          }
      }
      else if(process == 3){ //Editing
        x = 0;
        for(int b = 0; b<i;b++){
          g = strlen(names[b]);
          y = 0;
          for(int h=0; h<g;h++){
            if(a[h] != names[b][h]){
              y = 1;
            }
          }
          if(y==0){
            HC12.write("File found. Please type the new text to save under this file name\n");
            delay(100);
            state++;
            x++;
            k = b;
          }
        }
        if(x == 0){
          HC12.write("File not found. Please try again.\n");
        }
    }
    }
    else if(state == 4){
      if(process == 0){
        for(int f = 0; f<strlen(a); f++){
          texts[j][f] = a[f];
        }
        HC12.write("File saved successfully.\n");
        delay(100);
        HC12.write("Type W to create a file, R to read a file, D to delete a file, E to edit a file or Q to exit.\n");
        state = 2;
        j++;
      }
      else if(process == 3){
        g = strlen(texts[k]);
        for(int f = 0; f<g; f++){
          texts[k][f] = '\0';
        }
        for(int f = 0; f<strlen(a); f++){
          texts[k][f] = a[f];
        }
        HC12.write("File edited successfully.\n");
        delay(100);
        HC12.write("Type W to create a file, R to read a file, D to delete a file, E to edit a file or Q to exit.\n");
        state = 2;
      }
    }
    d = 0;
  }
  /*while (Serial.available()) {
    HC12.write(Serial.read());      
  }*/
}
