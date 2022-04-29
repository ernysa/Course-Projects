#include <stdio.h>
#include <stdlib.h>

struct candidate {
	char letter; 
	int votes;
	float percent;
};

int **vote_read(char filename[]) {
	FILE *districts = fopen(filename,"r");
	int line=0;
	char line_num = getc(districts);
	while (line_num != EOF) {
		if (line_num == '\n')
		line++;
		line_num = getc(districts);
	}
	fclose(districts);
	line++;
	int ** votes= (int**)malloc(sizeof(int*)*4);
	for (int i=0;i<4;i++) {
		votes[i] = (int*)malloc(sizeof(int)*line);
	}
	for (int j=0;j<line;j++) {
		votes[0][j]=0;
		votes[1][j]=0;
		votes[2][j]=0;
		votes[3][j]=0;
	}
	districts = fopen(filename, "r");
	int c=0;
	while (!feof(districts)) {
		fscanf(districts,"%d %d %d %d",votes[0]+c,votes[1]+c,votes[2]+c,votes[3]+c);
		c++;
	}
	fclose(districts);
	return votes;
}

void vote_num_total(int **votes, int line,struct candidate *A,struct candidate *B,struct candidate *C,struct candidate *D) {
	int total_vote=0;
	for (int i=0;i<line;i++) {
		A->votes += votes[0][i];
		B->votes += votes[1][i];
		C->votes += votes[2][i];
		D->votes += votes[3][i];
	}
	int total = A->votes+B->votes+C->votes+D->votes;
	A->percent= (1.0)*A->votes/total;
	B->percent= (1.0)*B->votes/total;
	C->percent= (1.0)*C->votes/total;
	D->percent= (1.0)*D->votes/total;
}
void winner(int total, struct candidate A,struct candidate B,struct candidate C,struct candidate D) {
	struct candidate arr[4];
	arr[0]=A;
	arr[1]=B;
	arr[2]=C;
	arr[3]=D;
	for (int i=0;i<4;i++) {
		if (arr[i].percent>0.5) {
			printf("Winner: %c",arr[i].letter);
			return;
		}
	}

	for (int i=0;i<4;i++) {
		for (int j=0;j<4;j++) {
			if (arr[i].percent>arr[j].percent) {
				struct candidate tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
	printf("Second Round: %c and %c\n",arr[0].letter,arr[1].letter);
}

int main(int argc, char*argv[]) {
	char file_name[20];
	scanf("%s",file_name);
	struct candidate A= {'A',0,0},B= {'B',0,0}, C= {'C',0,0}, D= {'D',0,0};
	int **votes = vote_read(file_name);
	FILE *districts = fopen(file_name,"r");
	int line=0;
	char line_num = getc(districts);
	while (line_num != EOF) {
		if (line_num == '\n')
		line++;
		line_num = getc(districts);
	}
	fclose(districts);
	vote_num_total(votes,line,&A,&B,&C,&D);
	int total=A.votes+B.votes+C.votes+D.votes;
	winner(total,A,B,C,D);
	free(votes);
	
	return 0;
}
