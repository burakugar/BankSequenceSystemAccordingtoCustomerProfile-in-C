#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum type{ /* customer types */
	employee=0,
	retired=1,
	student=2,
	unemployed=3,
	other=4
}type;
typedef struct info{ /* struct holds customer informations*/
	char name[20];
	int age;
	type label;
	int index;
}info;
int checklastElement(int seq[50]){ /* function that returns the last customer's index in the seq array */
	int i;
	for(i=0;i<50;i++){
		if(seq[i]==-1){ /* returns the index of first -1 minus 1 */
			return i-1;
		}
	}
}

int checklastgivenElement(int seq[50],type label){ /* function that returns the last customer's index in the seq array */
    int last_e=checklastElement(seq);
	int i,first = -1, last = -1;
    for (i = 0; i <= last_e; i++) {
        if (label != seq[i])
            continue;
        if (first == -1)
            first = i;
        last = i;
    }
    if (first != -1)
        return last;
    else
        return 0; /* returns 0 if the given element is not in the array */
}
int checkfirstgivenElement(int seq[50],type label) /*finds the first occurence of the given element in the array */
{	int last_e=checklastElement(seq);
    int first = -1, last = -1,i;
    for ( i = 0; i < last_e; i++) {
        if (label != seq[i])
            continue;
        if (first == -1)
            first = i;
        	last = i;
    }
    if (first != -1)
        return first;
	else
        return 0; /* returns 0 if the given element is not in the array */
	}

/*Function to Insert an element at a specific position in an Array */
void inserttheElement(type label,int seq[50],int index){
    int i, n = 50;
    n++;
    /* shift elements forward */
    for (i = n-1; i >= index; i--)
    {	
        seq[i] = seq[i - 1];
	}
	seq[index] = label;
	
    for(i=0;i<50;i++)
    printf("%d ", seq[i]);
    
}
/* this function adds the new customer to the customer array and shift other customers */
void inserttheElement_1(info element,info arr[50],int index){
    int i, n = 50;
    n++;
    /* shift elements forward */
    for (i = n-1; i >= index; i--){
        if(arr[i-1].label!=-1){
		arr[i] = arr[i - 1];
    	}
	}	
    	arr[index] = element;
}

int findNumberoflabel(type label, int seq[50]){ /* finds the number of occurence of the given label in the queue*/
	int i,last,count=0;
	last=checklastElement(seq);
	for(i=0;i<last+1;i++){
		if(seq[i]==label){
			count++;
		}
	}
	return count;
}

/* This function calculates the number of -1's in the sequence. if there are 50 -1's in the sequence it means we are at the
end of the sequence */
int checkEnd(int seq[50]){ 
	int i,counter=0;
	for(i=0;i<50;i++){ 
		if(seq[i]==-1){
		counter++;
		}
	}
	if(counter== 50){
		return 1;
	}
	else{
		return 0;
	}	
}
void printSeq(int seq[50],int flag){ /* this function is printing the current sequence in the queue. Since we fill our array with -1's initially which means
that element is not a customer, we have to print the elements which are not -1 */
	int i;
	if (flag==0){ /* for printing the first element */
	for(i=1;i<50;i++){
		if(seq[i]!=-1){
			printf("%d ",seq[i]);
			}
		}
	}
	else{
	for(i=0;i<50;i++){
		if(seq[i]!=-1){
			printf("%d ",seq[i]); /* for printing other elements */
			}
		}
	}
}
/*IMPORTANT: THE GENERAL WAY OF THIS FUNCTION: 
SEARCH FOR THE BEST LOCATION IN THE GIVEN LIST WITH IF ELSE STATEMENTS
AFTER FIND THE BEST LOCATION, RETURN THAT LOCATION'S INDEX AND CALL THE INSERTTHELEMENT FUNCTION TO INSERT THE NEW CUSTOMER TO THE ARRAY 
GOTO IS USED TO BLOCK FUNCTION TO IMPLEMENT MORE THAN ONE IF ELSE STATEMENT IF MORE THAN ONE CONDITION IS SATISFIED*/
/* this function organizes sorting, if any customer is added,it finds the correct index in the queue*/
/* this function returns the index of the correct index of the next customer will be added */
int implementtheOrder(type label,int seq[50],int* count_0,int* count_1,int* count_2,int* count_3,int* count_4){
	int last,temp,last_element,ret=-2,i,numb,index;
	last_element=checklastElement(seq);
	if(label == 0){ /* if the customer's label is 0 */
		if(*count_0<5){ /* there are at most 5 customer repedeately */
			if(last_element==-1){ /* if there is no customer in the queue, add the next customer as first customer */
				seq[0]=label;
				*count_0=*count_0+1;
				ret=0;
				goto a;
			}
			else if(checklastgivenElement(seq,label)!=0){ /* if there is an element with label 0, find the lastest one's index  */
			/* for ex. if the queue is 0 0 1  and next customer is 0, we have to add it to queue such as 0 0 0 1 */ 
				last=checklastgivenElement(seq,0); /* if there is a customer with given label at least one time, find it's index */
				inserttheElement(label,seq,last+1); /* insert the element to the next index */
				*count_0=*count_0+1; /* increment the counter */
				ret=last+1;
				goto a;
			}
			
			else{ /* if there is no 0 in the given list such as 1 2 3 4, we have to determine if any 1 is on the list or not. if there is one, we have to insert the 0 
			such that 0 1 2 3 4.*/
				if(checklastgivenElement(seq,label)==0){ /* if there is no customer with label 0 */
					if(findNumberoflabel(1,seq)){
						last=checklastgivenElement(seq,1); /* finding the last element of label 1*/
						index=last-*count_1+1;
						inserttheElement(label,seq,index);
						*count_0=*count_0+1;
						ret=index;
						goto a;
					}
					/* if there is no 0 in the given list such as 2 3 4, we have to determine if any 2 is on the list or not. if there is one, we have to insert the 0 
					such that 0 2 3 4.*/
					else if(findNumberoflabel(1,seq)==0 && findNumberoflabel(2,seq)!=0){
						last=checklastgivenElement(seq,2); /* finding the last element of label 2*/
						index=last-*count_2+1;
						inserttheElement(label,seq,index);
						*count_0=*count_0+1;
						ret=index;
						goto a;
					}
					/* if there is no 0 in the given list such as 3 4, we have to determine if any 3 is on the list or not. if there is one, we have to insert the 0 
					such that 0 3 4.*/
					else if(findNumberoflabel(1,seq)==0 && findNumberoflabel(2,seq)==0 && findNumberoflabel(3,seq)!=0){
						numb=findNumberoflabel(3,seq); /* finding number of occurence of the label 3*/
						last=checklastgivenElement(seq,3); /* finding the last element of label 3*/
						index=last-*count_3+1;
						inserttheElement(label,seq,index);
						*count_0=*count_0+1;
						ret=index;
						goto a;
					}
					/* if there is no 0 in the given list such as 4, we have to determine if any 4 is on the list or not. if there is one, we have to insert the 0 
					such that 0 4.*/
					else if(findNumberoflabel(1,seq)==0 && findNumberoflabel(2,seq)==0 && findNumberoflabel(3,seq)==0 && findNumberoflabel(4,seq)!=0){
						numb=findNumberoflabel(4,seq); /* finding number of occurence of the label 3*/
						last=checklastgivenElement(seq,4); /* finding the last element of label 3*/
						index=last-*count_4+1; /* calculating the new index */
						inserttheElement(label,seq,index);
						*count_0=*count_0+1;
						ret=index;
						goto a;
					}
					else{	/* if the conditions above are not satisfied */
						if(*count_0==0){ /* if there is no 0 in the queue insert the element to the first index */
						inserttheElement(label,seq,0);
						*count_0=*count_0+1;
						ret=0;
						goto a;
						}
						else{
						/*if there is one 0 label customer in the index, add the next customer next of it */
						seq[last_element+1]=label;
						*count_0=*count_0+1;
						ret=last_element+1;
						goto a;
						}
					}
				}		
			}
		}
		else if (*count_0==5){ /* if counter reaches 5, make it 0 and add the next element at the end of the queue */
			seq[last_element+1]=label;
			*count_0=0;
			ret=last_element+1;
			goto a;
		}
		a:;
	}
	
	else if(label == 1){	/* if the customer's label is 1 */
		if(*count_1<3){	/* there are at most 3 customer repedeately */
			if(last_element==-1){ /* if there is no customer in the queue, add the next customer as first customer */
				seq[0]=label;
				*count_1=*count_1+1;
				ret=0;
				goto y;
			}
			else if(checklastgivenElement(seq,label)!=0){ /* if there is an element with label 1, find the lastest one's index  */
			/* for ex. if the queue is 1 1 2  and next customer is 1, we have to add it to queue such as 1 1 1 2  */ 
				last=checklastgivenElement(seq,1); /* if there is a customer with given label at least one time, find it's index */
				inserttheElement(label,seq,last+1); /* insert the element to the next index */
				*count_1=*count_1+1; /* increment the counter */
				ret=last+1;
				goto y;
			}
			
			else{ /* if there is no 1 in the given list such as 2 3 4, we have to determine if any 1 is on the list or not. if there is one, we have to insert the 1
			such that 1 2 3 4.*/
				if(checklastgivenElement(seq,label)==0){ /* if there is no customer with label 1 */
					if(findNumberoflabel(2,seq)){
						last=checklastgivenElement(seq,2); /* finding the last element of label 2*/
						index=last-*count_2+1;
						inserttheElement(label,seq,index);
						*count_1=*count_1+1;/* increment the counter */
						ret=index;
						goto y;
					}
					else if(findNumberoflabel(2,seq)==0 && findNumberoflabel(3,seq)!=0){
						last=checklastgivenElement(seq,3); /* finding the last element of label 3*/
						last++;
						index=last-*count_3;
						inserttheElement(label,seq,index);
						*count_1=*count_1+1;/* increment the counter */
						ret=index;
						goto y;
					}
					else if(findNumberoflabel(2,seq)==0 && findNumberoflabel(3,seq)==0 && findNumberoflabel(4,seq)!=0){
						numb=findNumberoflabel(4,seq); /* finding number of occurence of the label 3*/
						last=checklastgivenElement(seq,4); /* finding the last element of label 3*/
						index=last-*count_4+1;
						inserttheElement(1,seq,index);
						*count_1=*count_1+1;/* increment the counter */
						ret=index;
						goto y;
					}
					else{
						if(*count_1==0){
							if(*count_0==0){
							inserttheElement(label,seq,0);
							*count_1=*count_1+1;/* increment the counter */
							ret=0;
							goto y;
							}
							else if(*count_0==1){
							inserttheElement(label,seq,1);
							*count_1=*count_1+1;/* increment the counter */
							ret=1;
							goto y;
							}
							else{
							numb=findNumberoflabel(0,seq);
							inserttheElement(label,seq,numb+1);
							*count_1=*count_1+1;/* increment the counter */
							ret=numb+1;
							goto y;
							}
							
						}
						else{
						seq[last_element+1]=label;
						*count_1=*count_1+1;/* increment the counter */
						ret=last_element+1;
						goto y;
						}
					}
				}		
			}
		}
		else if (*count_1==3){ /* if counter reaches 3, make it 0 and add the next element at the end of the queue */
			seq[last_element+1]=label;
			*count_1=0;
			ret=last_element+1;
			goto y;
		}
		y:;
	}
	
	else if(label == 2){	/* if the customer's label is 2 */
		if(*count_2<3){	/* there are at most 3 customer repedeately */
			if(last_element==-1){	/* if there is no customer in the queue, add the next customer as first customer */
				seq[0]=label;
				*count_2=*count_2+1;
				ret=0;
				goto p;
			}
			else if(checklastgivenElement(seq,label)!=0){ /* find the lastest element with label 2 */
				last=checklastgivenElement(seq,2); /* if there is a customer with given label at least one time, find it's index */
				inserttheElement(label,seq,last+1); /* insert the element to the next index */
				*count_2=*count_2+1; /* increment the counter */
				ret=last+1;
				goto p;
			}
			
			else{ /* if there is no 2 in the given list such as 1 3 4, we have to determine if any 1 is on the list or not. if there is one, we have to insert the 0 
			such that 0 1 2 3 4.*/
				if(checklastgivenElement(seq,label)==0){ /* if there is no customer with label 2 */
					if(findNumberoflabel(3,seq)){
						last=checklastgivenElement(seq,3); /* finding the last element of label 3*/
						index=last-*count_3+1;
						inserttheElement(label,seq,index);
						*count_2=*count_2+1;
						ret=index;
						goto p;
					}
					else if(findNumberoflabel(3,seq)==0 && findNumberoflabel(4,seq)!=0){
						last=checklastgivenElement(seq,4); /* finding the last element of label 3*/
						index=last-*count_4+1;
						inserttheElement(label,seq,index);
						*count_2=*count_2+1;
						ret=index;
						goto p;
					}
					else{
						if(*count_2==0){ /* if there is no 2 in the list check for the 0 and 1 because their number determines the index */
							if(*count_0==1 && *count_1==1 ){/* if there is one 0 and one 1, index should be 2 */
								inserttheElement(label,seq,2);
								*count_2=*count_2+1;
								ret=2;
								goto p;
							}
							else if(*count_0==0 && *count_1==1 ){ /* if there is no 0 and one 1, index should be 1 */
								inserttheElement(label,seq,1);
								*count_2=*count_2+1;
								ret=1;
								goto p;
							}
							else if(*count_0==1 && *count_1==0 ){ /* if there is one 1 and no 1, index should be 1 */
								inserttheElement(label,seq,1);
								*count_2=*count_2+1;
								ret=1;
								goto p;
							}
							else if(*count_0==0 && *count_1==0 ){
								inserttheElement(label,seq,0); /* if there is no 0 or 1, 2 should be initial element of the array */
								*count_2=*count_2+1;
								ret=0;
								goto p;
							}
							
							else{
								numb=findNumberoflabel(0,seq)+findNumberoflabel(1,seq);
								inserttheElement(label,seq,numb+1);
								*count_2=*count_2+1;
								ret=numb+1;
								goto p;
							}
						}
						else{
						seq[last_element+1]=label;
						*count_2=*count_2+1;
						ret=last_element+1;
						goto p;
						}
					}
				}		
			}
		}
		else if (*count_2==3){ /*  if counter reaches 3, make it 0 and add the next element at the end of the queue */
			seq[last_element+1]=label;
			*count_2=0;
			ret=last_element+1;
			goto p;
		}
		p:;
	}
	else if(label == 3){	/* if the customer's label is 1 */
		if(*count_3<2){
			if(last_element==-1){
				seq[0]=label;
				*count_3=*count_3+1;
				ret=0;
				goto r;
			}
			else if(checklastgivenElement(seq,label)!=0){ /* find the lastest label 3 element */
				last=checklastgivenElement(seq,3); /* if there is a customer with given label at least one time, find it's index */
				inserttheElement(label,seq,last+1); /* insert the element to the next index */
				*count_3=*count_3+1; /* increment the counter */
				ret=last+1;
				goto r;
			}
			
			else{ /* if there is no 3 in the given list such as 1 2 4, we have to determine if any 1 is on the list or not. if there is one, we have to insert the 3 
			such that 1 2 3 4.*/
				if(checklastgivenElement(seq,label)==0){ /* if there is no customer with label 3 */
					if(findNumberoflabel(4,seq)==1){
						last=checklastgivenElement(seq,4); /* finding the last element of label 3*/
						index=last-*count_4+1;
						inserttheElement(label,seq,index);
						*count_3=*count_3+1;
						ret=index;
							goto r;
					}
					else if(findNumberoflabel(4,seq)==0){
						seq[last_element+1]=label;
						*count_3=*count_3+1;
						ret=last_element+1;
						goto r;
					}
					else{ /* this else block investigates if there is any 1 or 2 in front of 3, if there at least one, find it and put 3 afterwards such as
					if the queue is 1 1 2 2, we have to find the last 2 and add the customer such that 1 1 2 2 3 */ 
						if(*count_3==0){
							if(*count_0!=1 && *count_1!=1 &&  *count_2!=1){
								inserttheElement(label,seq,0);
								*count_3=*count_3+1;
								ret=0;
								goto r;
							}
							else if(*count_0!=1 && *count_1!=1 &&  *count_2==1){
								inserttheElement(label,seq,1);
								*count_3=*count_3+1;
								ret=1;
								goto r;
							}
							else if(*count_0!=1 && *count_1==1 &&  *count_2!=1){
								inserttheElement(label,seq,1);
								*count_3=*count_3+1;
								ret=1;
								goto r;
							}
							else if(*count_0==1 && *count_1==1 &&  *count_2!=1){
								inserttheElement(label,seq,2);
								*count_3=*count_3+1;
								ret=2;
								goto r;
							}
							else if(*count_0==1 && *count_1==1 &&  *count_2==1){
								inserttheElement(label,seq,3);
								*count_3=*count_3+1;
								ret=3;
								goto r;
							}
							else if(*count_0!=1 && *count_1==1 &&  *count_2==1){
								inserttheElement(label,seq,2);
								*count_3=*count_3+1;
								ret=2;
								goto r;
							}
							else if(*count_4==1){
								if((*count_0==0&&*count_1==0&&*count_2==1)||(*count_0==0&&*count_1==1&&*count_2==0)||(*count_0==1&&*count_1==0&&*count_2==0))
								inserttheElement(label,seq,1);
								*count_3=*count_3+1;
								ret=1;
								goto r;
								}
							else if((*count_1==1&&*count_1==1&&*count_2==0)||(*count_0==0&&*count_1==1&&*count_2==1)||(*count_0==1&&*count_1==0&&*count_2==1)){
								inserttheElement(label,seq,2);
								*count_3=*count_3+1;
								ret=2;
								goto r;
								}
							else if((*count_1==1&&*count_1==1&&*count_2==0)){
								inserttheElement(label,seq,3);
								*count_3=*count_3+1;
								ret=3;
								goto r;
								}
							else{
								numb=findNumberoflabel(0,seq)+findNumberoflabel(1,seq)+findNumberoflabel(2,seq);
								inserttheElement(label,seq,numb+1);
								*count_3=*count_3+1;
								ret=numb+1;
								goto r;
							}
						}
						else{
						seq[last_element+1]=label;
						*count_3=*count_3+1;
						ret=last_element+1;
						goto r;
						}
					}
				}		
			}
		}
		else if (*count_3==2){	/* if counter reaches 2, make it 0 and add the next element at the end of the queue */
			last_element=checklastElement(seq);
			seq[last_element+1]=label;
			*count_3=0;
			ret=last_element+1;
			goto r;
		}
			r:;
	}
	
	else if(label == 4){	/* if the customer's label is 4 */
		if(*count_4<2){
			if(last_element==-1){
				seq[0]=label;
				*count_4=*count_4+1;
				ret=0;
				goto t;
			}
			else if(checklastgivenElement(seq,label)!=0){ /* find the lastest label 4 element */
				last=checklastgivenElement(seq,4); /* if there is a customer with given label at least one time, find it's index */
				inserttheElement(label,seq,last+1); /* insert the element to the next index */
				*count_4=*count_4+1; /* increment the counter */
				ret=last+1;
				goto t;
			}
			
			else{ /* it is not important what is in front of the 4 because we always add it at the end of the array */
			
						if(*count_4==0){ /* if there is no 4 in the array find the last element and add it at the end of it*/
						last=checklastElement(seq);
						inserttheElement(label,seq,last+1);
						*count_4=*count_4+1;
						ret=last+1;
						goto t;
						}
						else{ 
						seq[last_element+1]=label;
						*count_4=*count_4+1;
						ret=last_element+1;
						goto t;
						}
						
				}		
			}
		}
		 if (*count_4==2){	/* if counter reaches 2, make it 0 and add the next element at the end of the queue */
			last_element=checklastElement(seq);
			seq[last_element+1]=label;
			*count_4=0;
			ret=last_element+1;
			goto t;
		}
		t:
	return ret;
}
int deleteElement(int seq[50],int x) /* this function deletes the given element from the array and shifts the relevant elements*/
{	int i;
	int last= checklastElement(seq);
	for(i=1;i<=last;i++){
		seq[i-1]=seq[i];
	}
	seq[last]=-1;
	printSeq(seq,1);
}
void addCustomer(int seq[50],info arr[50],int* count_0,int* count_1,int* count_2,int* count_3,int* count_4,int* current_customer_index){ /* function that adds the given customer to the queue */	
	int i,index=0;
	info temp;
	info customer; /* creating a new customer type */
	char* name;
	int age;
	int label;
	if(*current_customer_index==0){
	printf("Please enter the name of the customer :"); /* receiving informations about new customer */
	scanf("%s",customer.name);
	printf("Please enter the age of the customer :");
 	scanf("%d",&age);
 	customer.age=age;
 	printf("Please enter the label of the customer :");
 	scanf("%d",&label);
 	customer.label=label;
	seq[0]=customer.label; /* we will do different operations between the first element and the others */
	customer.index=0;
	if(customer.label==0){	/*we increase the relevant counter by 1 according to the customer label */
		*count_0=*count_0+1;
	}
	else if(customer.label==1){
		*count_1=*count_1+1;
	}
	else if(customer.label==2){
		*count_2=*count_2+1;
	}
	else if(customer.label==3){
		*count_3=*count_3+1;
	}
	else if(customer.label==4){
		*count_4=*count_4+1;
	}
	arr[0]=customer; /* we determined the first customer as the initial element of customer array */
	}
	else{
	printf("Please enter the name of the customer :");
	scanf("%s",customer.name);
	printf("Please enter the age of the customer :");
 	scanf("%d",&age);
 	customer.age=age;
 	printf("Please enter the label of the customer :");
 	scanf("%d",&label);
 	customer.label=label;
	index=implementtheOrder(customer.label,seq,count_0,count_1,count_2,count_3,count_4); /* we give a parameter to this function to find the best index for
	the new customer */
	inserttheElement_1(arr[index],arr,index); /* after we fill our array with new customer,we are filling our customer array with new customer */
	arr[index]=customer;
	}
	*current_customer_index+=1;
}
void proceedCustomer(int seq[50],int* current_customer_index,info arr[50],int* count_0,int* count_1,int* count_2,int* count_3,int* count_4){	/* function proceeds the given customer in the queue */	
	int i,count;
	char* name;
	int index=checklastElement(seq);
	if(seq[0]==-1){
		printf("There is no customer in the queue!"); /*if seq[0]=-1 that means there is no customer in the queue */
		return;
	}
	strcpy(name,arr[0].name); /*copying the name of the customer and assing it to the customer's struct name */
	count=arr[0].label;
	/* We are substracting -1 from the counters because we proceed a customer from the array */
	if(count==0){
		*count_0-=1;
	}
	else if(count==1){
		*count_1-=1;
	}
	else if(count==2){
		*count_2-=1;
	}
	else if(count==3){
		*count_3-=1;
	}
	else if(count==4){
		*count_4-=1;
	}
	printf("Proceed customer is %s",name);
	
	for(i=0;i<=*current_customer_index;i++){ /* after the delete operation we are shifting the other elements in the array through deleted location */
		arr[i]=arr[i+1];
	}
	deleteElement(seq,1);
}


int main(void){
	int i,n,current_customer_index=0;
	int seq[50];/* array that holds the type of the customers in sequence */
	info arr[50];/* array that holds the structures of the customers */
	int count_0=0; /* counters to calculate number of each type of customer in the sequence up to given point */
	int count_1=0;
	int count_2=0;
	int count_3=0;
	int count_4=0;
	for(i=0;i<50;i++){
		seq[i]=-1; /* filling the array with -1's initially which means there is no customer in the queue */
		arr[i].label=-1;
	}
	printf("\n***********Banking System***********\n");
	printf("Current Sequence:\n");
	printSeq(seq,0);
	printf("\n1-Add customer:\n");
	printf("2-Process customer:\n");
	z:
	scanf("%d",&n);
	if(n==2){
		printf("There is not any customer in bank system sequence.");
		goto z;
	}
	else if(n==1){
		addCustomer(seq,arr,&count_0,&count_1,&count_2,&count_3,&count_4,&current_customer_index);
	}
	do{
	printf("\n***********Banking System***********\n");
	printf("Current Sequence:\n");
	for(i=0;i< current_customer_index;i++){
		if(seq[i]!=-1){
			printf("%d ",seq[i]);
		}
	}
	printf("\n1-Add customer:\n");
	printf("2-Process customer:\n");
	scanf("%d",&n);
	if(n==2){
		proceedCustomer(seq,&current_customer_index,arr,&count_0,&count_1,&count_2,&count_3,&count_4);
	}
	else if(n==1){
		addCustomer(seq,arr,&count_0,&count_1,&count_2,&count_3,&count_4,&current_customer_index);
		}	
	}
	while(checkEnd!=0); /* until there are 50 customers in the queue */
	return 0;
}
