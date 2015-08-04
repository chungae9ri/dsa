/* struct node {
   	int sum;
	struct node *next;
   };
*/

/* sum of elements in linked list c code
int sumList(struct node *head) {
	struct node *cur = head;
	int sum = 0;
	while (cur != NULL) {
		sum += cur->value;
		cur = cur->next;
	}
	return sum;
}
 */
sumList:      	MOV R3, R0       ; R3 holds "cur"
		MOV R0, #0       ; R0 holds "sum"
sumList_loop:	TST R3, R3
		MOVEQ PC, LR     ; if cur is NULL, return: R0 already holds sum
		LDR R2, [R3]     ; load cur->value into R2, add it to R0
		ADD R0, R0, R2
		LDR R3, [R3, #4] ; update cur to be cur->next
		B sumList_loop

/* addfront to linked list c code
struct node* addFront(struct node *head, int val) {
	struct node *n = (struct node*) malloc(sizeof(struct node));
	n->value = val;
	n->next = head;
	return n;
}
*/
addFront:     	STMDB SP!, {R0, R1, LR}  ; push R0, R1, LR onto stack
		MOV R0, #8               ; call malloc(8)
		BL malloc
		LDMIA SP!, {R2, R3, LR}  ; pop stack into R2, R3, LR
		STR R3, [R0]             ; n->value = val (pushed R1 popped into R3)
		STR R2, [R0, #4]         ; n->next = head (pushed R0 popped into R2)
		MOV PC, LR               ; return from subroutine




/* remove element from linked list c code
struct node *remove(struct node *head, int val) {
	struct node *cur = head;
	struct node *prev = NULL;
	while (cur != NULL) {
		if (cur->value == val) {
			if (cur == head) {
				head = cur->next;
			} else {
				prev->next = cur->next;
			}
			free(cur);
			return head;
		}
		prev = cur;
		cur = cur->next;
	}
	return head;
}
*/

remove:		STMDB SP!, {R0, R4, LR} 	; Save "head", R4, LR onto stack.
		MOV R2, R0         		; Use R2 for "cur".
		MOV R3, R0         		; Use R3 for "prev".
remove_loop: 	TST R2, R2         		; If cur == NULL, return with R0 unchanged.
		LDMEQIA SP!, {R0, R4, PC}
		LDR R4, [R2]       		; Load cur->value,
    		CMP R4, R1         		;   compare to "val" argument,
    		BEQ remove_find    		;   and go to remove_find if they match.
    		MOV R3, R2         		; Otherwise prev = cur,
    		LDR R2, [R2, #4]   		;   cur = cur->next,
    		B remove_loop      		;   and repeat.
remove_find: 	LDR R4, [R2, #4]   	; Load cur->next into R4.
    		CMP R2, R0         		; Check whether cur == head:
    		STREQ R4, [SP]     		;   if so, replace "head" on stack with R4;
    		STRNE R4, [R3, #4] 		;   if not, save R4 into prev->next.
    		MOV R0, R2         		; Now free(cur).
    		BL free
    		LDMIA SP!, {R0, R4, PC} 	; Return "head" saved on stack.
