/* Longest Common Subsequence:
This program will print all different longest common subsequences
of two strings of lowercase letters
Complexity: O(max(length_of_longest_subsequence * number_of_solutions, l1 * l2))
with l1, l2 the length of the strings
Author: Adrian Kuegel
Date: 19. 1. 2003
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max(x,y) ((x>y)?(x):(y))

int dp[81][81],l1,l2;
char s1[81],s2[81],out[81],visit[81][81];

struct tree {
	struct tree *t[26];
}
*root,*m[6561];

typedef struct L {
	int i,j;
	struct L *next;
}
linkedList;

/*	void treecpy:
copy of the (sub)tree *orig to tree dest */
void treecpy(struct tree *dest, struct tree *orig) {
	int i;
	for (i=0; i<26; i++) {
		if (orig->t[i]!=NULL) {
			dest->t[i] = malloc(sizeof(struct tree));
			treecpy(dest->t[i],orig->t[i]);
		}
		else
		    dest->t[i] = NULL;
	}
}

/*	void construct:
constructs the subsequences, they will be stored in a prefix tree
parameters:
i				index in the first string
j				index in the second string
*t				pointer to the parent tree node */
void construct(int i, int j, struct tree *t) {
	int k;
	linkedList *q,*tail,*temp;
	if (!dp[i][j])
		return;
	/* bfs to find the next matchings of the two strings */
	temp = q = tail = malloc(sizeof(linkedList));
	q->next = NULL;
	q->i = i;
	q->j = j;
	while(q!=NULL) {
		if (s1[q->i] == s2[q->j]) {
			int ind = s1[q->i]-'a';
			if (t->t[ind] == NULL) {
				t->t[ind] = malloc(sizeof(struct tree));
				if (m[q->i*(l2+1)+q->j]!=NULL)
					treecpy(t->t[ind],m[q->i*(l2+1)+q->j]);
				else {
					for (k=0; k<26; k++)
						t->t[ind]->t[k] = NULL;
					/* matching found, recursive call */
					construct(q->i+1,q->j+1,t->t[ind]);
					m[q->i*(l2+1)+q->j] = t->t[ind]; /* memorize subtree */
				}
			}
		}
		else {
			if (dp[q->i+1][q->j] == dp[q->i][q->j] && !visit[q->i+1][q->j]) {
				tail->next = malloc(sizeof(linkedList));
				tail = tail->next;
				tail->next = NULL;
				tail->i = q->i+1;
				tail->j = q->j;
				visit[q->i+1][q->j] = 1;
			}
			if (dp[q->i][q->j+1] == dp[q->i][q->j] && !visit[q->i][q->j+1]) {
				tail->next = malloc(sizeof(linkedList));
				tail = tail->next;
				tail->next = NULL;
				tail->i = q->i;
				tail->j = q->j+1;
				visit[q->i][q->j+1] = 1;
			}
		}
		q = q->next;
	}
	/* clear the queue and reinitialize visit[i][j] to 0 */
	while(temp!=NULL) {
		q = temp;
		temp = temp->next;
		visit[q->i][q->j] = 0;
		free(q);
	}
}

/*	void printanddelete:
prints the strings that are stored in the prefix tree */
void printanddelete(struct tree *p, int len) {
	int i;
	if (len == dp[0][0])
		printf("%s\n",out);
	else
	    for (i=0; i<26; i++) {
		out[len] = i+'a';
		if (p->t[i]!=NULL)
			printanddelete(p->t[i],len+1);
	}
	free(p);
}

int main() {
	int i,j;
	freopen("trip.in","r",stdin);
	freopen("trip.out","w",stdout);
	gets(s1);
	gets(s2);
	l1 = strlen(s1);
	l2 = strlen(s2);
	/*	standard DP algorithm to find the length of
	longest common subsequence(s) */
	for (i=0; i<=l1; i++)
		dp[i][l2] = 0;
	for (j=0; j<=l2; j++)
		dp[l1][j] = 0;
	for (i=l1-1; i>=0; --i)
		for (j=l2-1; j>=0; --j) {
			if (s1[i] == s2[j])
				dp[i][j] = dp[i+1][j+1]+1;
			else
				dp[i][j] = max(dp[i][j+1],dp[i+1][j]);
		}
	/* dp[0][0] contains the length of the LCS */
	root = malloc(sizeof(struct tree));
	for (i=0; i<26; i++)
		root->t[i] = NULL;
	out[dp[0][0]] = 0;
	construct(0,0,root);
	printanddelete(root,0);
	return 0;
}
