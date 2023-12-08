#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_TO_INDEX(c) (c-'a')

enum Letters {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};

void calcOccurences(FILE *database, unsigned *occurrences);
void findBestWord(FILE *database, unsigned *occurrences, char *guess_word);

/*
 * \brief: Opens the database created by the python script and solves wordle
 */
int main(){
    printf("Starting Wordle Solver...\n");
    
    // Open the files for buffering and database
    FILE *fdatabase;
    fdatabase = fopen("./database/5_letter_words.txt", "r");
    if(fdatabase == NULL){
        printf("Please make sure you run the Python script to create the \
                database first");
        exit(1);
    }
    FILE *fbuffer;
    fbuffer = fopen("./database/buffer.txt", "w");
    if(fbuffer == NULL){
        printf("Couldn't create new file for buffering.");
        exit(1);
    }

    // Get occurences of each letter
    unsigned occurences[26] = {0};
    calcOccurences(fdatabase, occurences);

    // Find best starting guess
    rewind(fdatabase);
    char *guess_word;
    guess_word = (char*)malloc(6 * sizeof(char));
    findBestWord(fdatabase, occurences, guess_word);
    printf("Best first guess is: %s\n", guess_word);

    // Close the used files and delete the buffer
    fclose(fdatabase);
    fclose(fbuffer);
    if(remove("./database/buffer.txt") != 0){
        printf("Couldn't delete buffer.txt");
        exit(1);
    }
    return 0;
}

/*
 * \brief: Calculates the # of occurences of each letter, 0 is best score
 * \params: database is the current subset of words possible, occurrences is a
 *          reference to a unsigned array of length 26
 */
void calcOccurences(FILE *database, unsigned *occurrences){
    printf("Calculating Occurances\n");
    char *word = NULL;
    size_t len = 0;
    size_t read;
    while((read = getline(&word, &len, database)) != -1){
        for(unsigned i = 0; word[i] != '\n'; i++){
            switch(word[i]) {
                case 'a': occurrences[0] += 1; break;
                case 'b': occurrences[1] += 1; break;
                case 'c': occurrences[2] += 1; break;
                case 'd': occurrences[3] += 1; break;
                case 'e': occurrences[4] += 1; break;
                case 'f': occurrences[5] += 1; break;
                case 'g': occurrences[6] += 1; break;
                case 'h': occurrences[7] += 1; break;
                case 'i': occurrences[8] += 1; break;
                case 'j': occurrences[9] += 1; break;
                case 'k': occurrences[k] += 1; break;
                case 'l': occurrences[l] += 1; break;
                case 'm': occurrences[m] += 1; break;
                case 'n': occurrences[n] += 1; break;
                case 'o': occurrences[o] += 1; break;
                case 'p': occurrences[p] += 1; break;
                case 'q': occurrences[q] += 1; break;
                case 'r': occurrences[r] += 1; break;
                case 's': occurrences[s] += 1; break;
                case 't': occurrences[t] += 1; break;
                case 'u': occurrences[u] += 1; break;
                case 'v': occurrences[v] += 1; break;
                case 'w': occurrences[w] += 1; break;
                case 'x': occurrences[x] += 1; break;
                case 'y': occurrences[y] += 1; break;
                case 'z': occurrences[z] += 1; break;
            }
        }
    }
    unsigned max = occurrences[a];
    for(unsigned i = 0; i < 26; i++){
        if(occurrences[i] > max){
            max = occurrences[i];
        }
    }
    for(unsigned i = 0; i < 26; i++){
        occurrences[i] = max - occurrences[i];
    }
    return;
}

/*
 * \brief: Using the given occurences this function tries to find the best guess
 * \params: database are the currently still available words, occurrences are
 *          the scores for each letter, guess_word is the output of the function
 * \todo: Score currently doesn't take into account twice the same letter
 */
void findBestWord(FILE *database, unsigned *occurrences, char *guess_word){
    printf("Finding best possible guess\n");
    char *word = NULL;
    size_t len = 0;
    size_t read;
    unsigned best_score = UINT_MAX;
    while((read = getline(&word, &len, database)) != -1){
        unsigned this_score = 0;
        for(unsigned i = 0; word[i] != '\n'; i++){
            this_score += occurrences[CHAR_TO_INDEX(word[i])];
            if(this_score > best_score){
                break;
            }
        }
        if(this_score < best_score){
            best_score = this_score;
            sprintf(guess_word, word);
        }
    }
    return;
}
