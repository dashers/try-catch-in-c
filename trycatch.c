// stubs for the three public functions for the exception handler
#include <stdio.h>

extern long *getRbp(void);
extern long *getRbx(void);
extern long *getR12(void);
extern long *getR13(void);
extern long *getR14(void);
extern long *getR15(void);

static long *activerbp;
static int catchcall = 0;
static int lastexceptionnumber;

struct frames{
	long currentrbp;
	long savedrbp;
	long rip; 
	long rbx;
	long r12;
	long r13;
	long r14;
	long r15;
	struct frames *next;
};

typedef struct frames frames_t;
static frames_t *list = NULL;


int catchException(void)
{	
	printf("catchException entered\n");
	activerbp = getRbp();
	long currentrbp = activerbp;
	long savedrbp = *activerbp;

	if(catchcall == 0){
		list = malloc(sizeof(frames_t));
		if(list == NULL){
			fprintf(stderr, "Fatal Error - Malloc failed for struct\n");
			exit(-1);
		}
		
		list->r15 = getR15();
		list->r14 = getR14();
		list->r13 = getR13();
		list->r12 = getR12();
		list->rbx = getRbx();
		list->currentrbp = currentrbp;
		list->savedrbp = savedrbp;
		list->rip = *(((long *) currentrbp) + 1);
		list->next = NULL;
	}

	if(catchcall != 0){
		while(list->next != NULL){
			list = list->next;
		}
		list->next = malloc(sizeof(frames_t));
		list->next->r15 = getR15();
		list->next->r14 = getR14();
		list->next->r13 = getR13();
		list->next->r12 = getR12();
		list->next->rbx = getRbx();
		list->next->currentrbp = currentrbp;
		list->next->savedrbp = savedrbp;
		list->next->rip = *(((long *) currentrbp) + 1);
		list->next->next = NULL;

	}

	catchcall = 1;
	
	/*	
	list.r15 = getR15();
	list.r14 = getR14();
	list.r13 = getR13();
	list.r12 = getR12();
	list.rbx = getRbx();

	activerbp = getRbp();
	long currentrbp = activerbp;
	long savedrbp = *activerbp;

	list.currentrbp = currentrbp;
	list.savedrbp = savedrbp;
	list.rip = *(((long *) currentrbp) + 1);
	*/
	return 0;	
}

void cancelCatchException(void)
{
	if(list->next == NULL){
		printf("Freeing list\n");
		free(list);
		return NULL;
	}
	printf("Deleting last item from list\n");
	while(list->next->next != NULL){
		list = list->next;
	}
	free(list->next);
	list->next = NULL;
	return NULL;
}

void throwException(int exceptionNumber)
{
	if(exceptionNumber == 0){
		fprintf(stderr, "Fatal Error - Exception number cannot be zero.\n");
		exit(-1);
	}

	if(catchcall != 1){
		fprintf(stderr, "Fatal Error - throwException called before catchException with exception number [%i].\n", exceptionNumber);
		exit(-1);
	}

	if(exceptionNumber == lastexceptionnumber){
		//fprintf(stderr, "Fatal Error - infinite loop of exception number [%i].\n", lastexceptionnumber);
		//exit(-1);

		long *rr15 = list->r15;
	  	long *rr14 = list->r14;
	  	long *rr13 = list->r13;
	  	long *rr12 = list->r12;
	  	long *rrbx = list->rbx;
	  	setRbx(rrbx);
	  	setR12(rr12);
	  	setR13(rr13);
	  	setR14(rr14);
	  	setR15(rr15);

	  	long *x = getRbp();
	  	long xx = x;

	  	setRsp(xx,exceptionNumber);
	}

	lastexceptionnumber = exceptionNumber;


	printf("throwException entered....\n");
	
	*activerbp = list->savedrbp;
	*(activerbp+1) = list->rip;

	long *rr15 = list->r15;
  	long *rr14 = list->r14;
  	long *rr13 = list->r13;
  	long *rr12 = list->r12;
  	long *rrbx = list->rbx;
  	setRbx(rrbx);
  	setR12(rr12);
  	setR13(rr13);
  	setR14(rr14);
  	setR15(rr15);

  	setRsp(activerbp,exceptionNumber);
}

