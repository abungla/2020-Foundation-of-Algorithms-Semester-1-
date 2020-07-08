/* Emoticon message cleanser:
 *
 * Skeleton code written by Farhana Choudhury and Jianzhong Qi, April 2020
 * Rest of the code written by Anuj Bungla, April 2020 (Student ID 1003633)
 * Algorithms are fun!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define STAGE_NUM_ONE 1							/* stage numbers */ 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5
#define STAGE_HEADER "Stage %d\n==========\n"	/* stage header format string */

#define MAX_MSG_LENGTH 280						/* maximum message length */
#define MAX_NUM_MSGS 100						/* maximum number of messages */
#define MAX_EMTCN_LENGTH 50						/* maximum emot. line length */
#define MAX_NUM_EMTCN 50						/* maximum number of emot. */

#define ZERO 0
#define ONE 1
#define TWO 2

typedef char msg_t[MAX_MSG_LENGTH+1];			/* a message */
typedef char emtcn_t[MAX_EMTCN_LENGTH+1];		/* an emoticon */

/****************************************************************/

/* function prototypes */
void read_one_msg(msg_t one_msg, int max_len);
void print_stage_header(int stage_num);
int count_tokens(msg_t one_msg);

void stage_one(msg_t one_msg);
void stage_two(msg_t msgs[], int *num_msgs);
void stage_three(msg_t msgs[], int num_msgs);
void stage_four(emtcn_t emtcns[], int *num_emtcns);
void stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns);

/* add your own function prototypes here */

void cleanse(msg_t one_msg[], int max_len);
void remove_trailing(msg_t one_msg[], int max_len, int num_msgs);
void remove_leading(msg_t one_msg[], int max_len, int num_msgs);
void replace_two_or_more_commas(msg_t one_msg[], int max_len, int num_msgs);

void compare_pattern_comma(char pattern_arr[], int size_of_pattern, 
                           emtcn_t emtcns[], int num_emtcns);

void compare_pattern_null(char pattern_arr[], int size_of_pattern, 
                          emtcn_t emtcns[], int num_emtcns);

void print_no_emotes(emtcn_t emtcns[], int *num_emtcns);
void print_longest_emote_and_length(emtcn_t emtcns[], int *num_emtcns);

/****************************************************************/

/* main function controls all the action, do NOT modify this function */
int
main(int argc, char *argv[]) {
	
	/* to hold all input messages */
	msg_t msgs[MAX_NUM_MSGS];	
	/* to hold the number of input messages */
	int num_msgs = ZERO;	
	/* to hold all input emoticons in the dictionary */
	emtcn_t emtcns[MAX_NUM_EMTCN];
	/* to hold the number of emoticons in the dictionary */
	int num_emtcns = ZERO;	
	
	/* stage 1: reading the first message */
	stage_one(msgs[num_msgs]); 
	num_msgs++;
	
	/* stage 2: removing alphanumeric characters */
	stage_two(msgs, &num_msgs);
	
	/* stage 3: removing extra commas */ 
	stage_three(msgs, num_msgs);
	
	/* stage 4: reading the dictionary and finding the longest emoticon */
	stage_four(emtcns, &num_emtcns);
	
	/* stage 5: removing invalid emoticons with the help of the dictionary */
	stage_five(msgs, num_msgs, emtcns, num_emtcns);
	
	/* all done; take some rest */
	return 0;
}

/* read a line of input into one_msg */
void
read_one_msg(msg_t one_msg, int max_len) {
	
	int i = ZERO, c;
	
	while (((c = getchar()) != EOF) && (c != '\n') && (c != '\r')) {
		if (i < max_len) {
			one_msg[i++] = c;
		} else {
			printf("Invalid input line, toooooooo long.\n");
			exit(EXIT_FAILURE);
		}
	}
	one_msg[i] = '\0';
}

/* print stage header given stage number */
void 
print_stage_header(int stage_num) {
	printf(STAGE_HEADER, stage_num);
}

/****************************************************************/
/* add your code below */

/* scan a message and count the number of tokens (separated by commas) in it */
int 
count_tokens(msg_t one_msg) {
	
	int counter = ZERO;
	int i = ZERO;
	
	while (one_msg[i] != '\0') {
		if (one_msg[i] == ',') {
			counter++;
		}
		i++;
	}
	
	/* add code here to count the number commas in one_msg,
	   and return the count + 1 */
	return (counter+ONE);
}

/* stage 1: reading the first message */
void 
stage_one(msg_t one_msg) {
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);
	
	/* read the first message */
	read_one_msg(&one_msg[ZERO], MAX_MSG_LENGTH+ONE);
	
	/* count and print the number of tokens */
	printf("Number of tokens: %d\n\n", count_tokens(one_msg));
	return;
}

/* stage 2: removing alphanumeric characters */
void 
stage_two(msg_t msgs[], int *num_msgs) {
	/* add code for stage 2 */
	
	/* print stage header */
	print_stage_header(STAGE_NUM_TWO);
	
	int i;
	
	/* store all the messages until ### is encountered in 2d array msgs*/
	for (i = ONE; i < MAX_NUM_MSGS; i++) {
		read_one_msg(msgs[i], MAX_MSG_LENGTH+ONE);
		if ((msgs[i][ZERO] == '#') && (msgs[i][ONE] == '#') && 
        (msgs[i][TWO] == '#')) {
			break;
		} else {
			*(num_msgs) = *(num_msgs) + ONE;
			continue;
		}
	}
	
	/* cleanse and print cleansed version */
	cleanse(msgs, MAX_MSG_LENGTH+ONE);
	printf("\n");
	return;
}

void cleanse(msg_t msg[], int max_len) {
	
	int i, j, z;
	
	/* use msg array to cleanse and at the same time modify it so 
    it accommodates the new cleansed version of the message */
	for (i = ZERO; i < max_len; i++) {
		j = ZERO;
		z = ZERO;
		if ((msg[i][j] == '#') && (msg[i][j+ONE] == '#') &&
        (msg[i][j+TWO] == '#')) {
			break;
		}
		while (j < max_len) {
			if (msg[i][j] == '\0') {
				break;
			}
			/* skip any english letters and digits */
			else if (isalpha(msg[i][j]) || ('0' <= msg[i][j] && 
            msg[i][j] <= '9')) {
				j++;
				continue;
			}
			/* store all characters that are not english 
            letters or digits into our original msg array */
			else {
				msg[i][z] = msg[i][j];
				printf("%c", msg[i][j]);
				j++;
				z++;
			}	
		}
		printf("\n");
		msg[i][z] = '\0';
	}
	return;
}
			
/* stage 3: removing extra commas */ 
void 
stage_three(msg_t msgs[], int num_msgs) {
	/* add code for stage 3 */
	
	/* print stage header */
	print_stage_header(STAGE_NUM_THREE);
	
	int i;
	
	/* remove any trailing commas */
	remove_trailing(msgs, MAX_MSG_LENGTH+ONE, num_msgs);
	
	/* remove any leading commas */
	remove_leading(msgs, MAX_MSG_LENGTH+ONE, num_msgs);
	
	/* replace two or more commas so there is only one comma 
    between any two adjacent tokens remaining in a message */
	replace_two_or_more_commas(msgs, MAX_MSG_LENGTH+ONE, num_msgs);
	
	/* print out the newly cleansed version that doesn't 
    have the excess commas */
	for (i = ZERO; i < num_msgs; i++) {
		printf("%s\n", msgs[i]);
	}
	printf("\n");
	return;	
}

void remove_trailing(msg_t one_msg[], int max_len, int num_msgs) {
	
	int i, j, z, len, counter;

	/* iterate over row */
	for (i = ZERO; i < num_msgs; i++) {
		len = strlen(one_msg[i]);
		counter = ZERO;
		/* iterate over column, accessing each character in that row */
		for (j = ZERO; j < len; j++) {
			/* count number of trailing commas present in that row */
			if (one_msg[i][j] != ',') {
				break;	
			} else {
				counter++;
			}
		}
		/* move back all characters "counter" spaces 
        back to get rid of the trailing commas */
		for (z = ZERO; z <= (len-counter); z++) {
			one_msg[i][z] = one_msg[i][counter+z];
		}
	}
}
	
void remove_leading(msg_t one_msg[], int max_len, int num_msgs) {
	
	int i, j, len, counter;
	
	/* iterate over row */
	for (i = ZERO; i < num_msgs; i++) {
		len = strlen(one_msg[i]);
		counter = ZERO;
		/* iterate over column, accessing each character in that row */
		for (j = (len-ONE); j >= ZERO; j--) {
			/* count number of leading commas present in that row */
			if (one_msg[i][j] != ',') {
				break;
			} else {
				counter++;
			}
		}
		/* insert null character at where the leading commas start */
		one_msg[i][len - counter] = '\0';
	}
}
	
void replace_two_or_more_commas(msg_t one_msg[], int max_len, int num_msgs) {
	
	int i ,j ,z ,len;
	
	/* iterate over row */
	for (i = ZERO; i < num_msgs; i++) {
		j = ZERO;
		/* iterate over column, accessing each character in that row */
		while(one_msg[i][j] != '\0') {
			if (one_msg[i][j] == ',') {
				/* check if there are multiple commas in a 
                row between two tokens */
				if (one_msg[i][j+ONE] == ',') {
					len = strlen(one_msg[i]);
					/* if there are, then move all characters back by 
                    one in that row, so only one out of the two comas is left. 
                    Repeat if need be. */
					for (z = j; z < len; z++) {
						one_msg[i][z] = one_msg[i][z+ONE];
					}
				} else {
					j++;
				}
			} else {
				j++;
			}
		}
	}
}

	
/* stage 4: reading the dictionary and finding the longest emoticon */ 
void stage_four(emtcn_t emtcns[], int *num_emtcns) {
	/* add code for stage 4 */
	
	/* print stage header */
	print_stage_header(STAGE_NUM_FOUR);
	
	/* print no. of emotes */
	print_no_emotes(emtcns, num_emtcns);
	
	/* print longest emote and its length */
	print_longest_emote_and_length(emtcns, num_emtcns);
	
	printf("\n");
}

void print_no_emotes(emtcn_t emtcns[], int *num_emtcns) {
	
	int i;
	
	/* increment no. of emotes by one until first 
    character in a row is a null */
	for (i = ZERO; i < MAX_NUM_EMTCN; i++) {
		read_one_msg(emtcns[i], MAX_EMTCN_LENGTH+ONE);
		if (emtcns[i][ZERO] == '\0') {
			break;
		} else {
			*(num_emtcns) = *(num_emtcns)+ONE;
		}
	}
	
	/* print total number of emotes */
	printf("Emoticon total: %d\n", *(num_emtcns));
}

void print_longest_emote_and_length(emtcn_t emtcns[], int *num_emtcns) {
	
	int i, j, counter, max, preserve_i;
	max = ZERO;
	
	for (i = ZERO; i < *(num_emtcns); i++) {
		counter = ZERO;
		j = ZERO;
		/* count length of emote unitl the first comma is encountered */
		while (emtcns[i][j] != ',') {
			counter++;
			j++;
		}
		/* if that counter is greater than the max, set it as max and 
        preserve the index of where that emote starts */
		if (counter > max) {
			max = counter;
			preserve_i = i;
		}
	}
	
	/* print the character starting at the index saved by the 
    preserve_i variable up until a comma is encountered  */
	printf("Longest: ");
	j = ZERO;
	while (emtcns[preserve_i][j] != ',') {
		printf("%c", emtcns[preserve_i][j]);
		j++;
	}
	printf("\n");
	
	/* print length of longest emote */
	printf("Length: %d\n", max);
}
	
	

/* stage 5: removing invalid emoticons with the help of the dictionary */
void 
stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns) {
	/* add code for stage 5  */
	/* print stage header */
	print_stage_header(STAGE_NUM_FIVE);
	
	/* declare an array that will hold emotes one by one */
	char pattern[MAX_MSG_LENGTH+ONE];
	
	int i, j, z;
	
	/* Iterate over the rows of emotes */
	for (i = ZERO; i < num_msgs; i++) {
		z = ZERO;
		for (j = ZERO; j < (MAX_MSG_LENGTH+ONE); j++) {
			if (msgs[i][j] == ',') {
				/*  Insert ',' at last index so when comparing, function below 
                compares upto ":)," rather then ":),happy" for eg. */
				pattern[z] = ',';
				/*  Pass the array that holds the emote to the function 
                that will compare our pattern array with the dictionary given.
                Note: this uses a different function from when the pattern
                ends with a null character. */
				compare_pattern_comma(pattern, z, emtcns, num_emtcns);
				/*  Regardless of whether or not the pattern is in 
                the dictionary, print ',' */
				printf(",");
				/*  Reset the index to 0, to store the next emote 
                to compare to the dictionary */
				z = ZERO;
			} else if (msgs[i][j] == '\0') {
				/*  Insert ',' at last index so when comparing, function below 
                compares upto ":)," rather then ":),happy" for eg. */
				pattern[z] = ',';
				compare_pattern_null(pattern, z, emtcns, num_emtcns);
				break;
			} else {
				/* Otherwise keep on storing characters into our 
                pattern array */
				pattern[z] = msgs[i][j];
				z++;
			}
		}
	}
}

void compare_pattern_comma(char pattern_arr[], int size_of_pattern, 
                           emtcn_t emtcns[], int num_emtcns) {

	int i, j, counter;
	
	for (i = ZERO; i < num_emtcns; i++) {
		counter = ZERO;
		/* compare pattern with first row of the emote 
        dictionary up until ',' */
		for (j = ZERO; j <= size_of_pattern; j++) {
			if (pattern_arr[j] == emtcns[i][j]) {
				counter++;
			} else {
				break;
			}
		}
		/* if  patterns match up with one of the emotes 
        in the dict, then print it out */
		if (counter == (size_of_pattern + ONE)) {
			for (j = ZERO; j < size_of_pattern; j++) {
				printf("%c", pattern_arr[j]);
			}
			
		}
	}
}

/* Probably could've made a function that took care of pattern that ended 
with , or \0 together but ran out of time */
void compare_pattern_null(char pattern_arr[], int size_of_pattern, 
                          emtcn_t emtcns[], int num_emtcns) {
	
	int i, j, counter;
  
	for (i = ZERO; i < num_emtcns; i++) {
		counter = ZERO;
		/* compare pattern with first row of the emote dictionary 
        up until ',' */
		for (j = ZERO; j <= size_of_pattern; j++) {
			if (pattern_arr[j] == emtcns[i][j]) {
				counter++;
			} else {
				break;
			}
		}
		/* If they did match then print out pattern then conclude with a \n. 
        If not then dont print anything */
		if (counter == (size_of_pattern+ONE)) {
			for (j = ZERO; j < size_of_pattern; j++) {
				printf("%c", pattern_arr[j]);
			}
            printf("\n");
		}
	}
}
