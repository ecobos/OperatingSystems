int main(int argc, char *argv[]) 
{ 
 int n; 
 n = atoi(argv[1]); execvp(argv[n], &argv[n]); 
perror("Exec Failure"); 
 printf ("\nHELLO\n"); 
 return(1); 
} 
