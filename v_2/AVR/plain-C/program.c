#include <stdio.h>
#include <string.h>

const char * morseTable[37] = {		// morse code array
  "012",		//a                 // 0 - dot
  "10002",	    //b                 // 1 - dash
  "10102",	    //c                 // 2 - end of letter
  "1002",		//d                 // 3 - end of word
  "02",			//e                 // 4 - end of sentence
  "00102",	    //f
  "1002",		//g
  "00002",	    //h
  "002",		//i
  "01112",	    //j
  "1012",		//k
  "01002",	    //l
  "112",		//m
  "102",		//n
  "1112",		//o
  "01102",	    //p
  "11012",	    //q
  "0102",		//r
  "0002",		//s
  "12",			//t
  "0012",		//u
  "0112",		//w
  "00012",	    //v
  "10012",	    //x
  "1012",		//y
  "11002",	    //z
  "011112",     //1
  "001112",     //2
  "000112",     //3
  "000012",     //4
  "000002",     //5
  "100002",     //6
  "110002",     //7
  "111002",     //8
  "111102",     //9
  "111112"      //0
};

char * msg_morse[100];

struct message{

    char * msg_asci;
    //char msg_morse[100];
    //unsigned int msg_length;
};

char * asci_to_morse(struct message msg_arg)
{
    unsigned int n = strlen(msg_arg.msg_asci);
    for(int i=0; i<n; i++)
    {
        if(msg_arg.msg_asci[i] == ' ')
        {
            strcat(msg_morse, "3");
        }
        else if(msg_arg.msg_asci[i] == '.')
        {
            strcat(msg_morse, "4");
        }
        else
        {
            strcat(msg_morse, morseTable[ msg_arg.msg_asci[i] - 97]); 
        }
    }
    return msg_morse;
}

// int broadcast(struct message msg_arg)
// {
//     unsigned int n = strlen(msg_arg.msg_morse);
//     for(int j=0; j<n; j++)
//     {
//         if(msg_arg.msg_morse[j] == '1')
//         {
//             printf("Dash!\n");
//         }
//         else if(msg_arg.msg_morse[j] == '0')
//         {
//             printf("Dot!\n");
//         }
//         else if(msg_arg.msg_morse[j] == '2')
//         {
//             printf("End of letter!\n");
//         }
//         else if(msg_arg.msg_morse[j] == '3')
//         {
//             printf("End of word!\n");
//         }
//     }
// }

int main(int argc, char **argv)
{
    struct message msg_1;
    msg_1.msg_asci = "abc def ";
    //msg_1.msg_length = strlen(msg_1.msg_asci);
    char * output;

    output = asci_to_morse(msg_1);

    //printf("%d\n",msg_1.msg_length);
    puts(msg_1.msg_asci);
    puts(output);

   // broadcast(msg_1);

 return 0;
}
