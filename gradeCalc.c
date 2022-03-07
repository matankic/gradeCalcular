#include <stdio.h>
#include <stdlib.h>

#define N 7

typedef struct{
	int ID;
	int * grades;
	int amount_exams;
}student_init_data;

typedef struct{
	int ID;
	double avg;
}student_processed_data;

typedef struct{
	student_processed_data * belowAvg, * aboveAvg;
	int belowSz, aboveSz;
	double general_avg;
}statistics;

int * Input_Data(int);
double Student_Average(student_init_data *);
double Total_Average(double *, int);
void Classification(student_init_data *, int, statistics *);
void Print_Tab(statistics *);
void Free_Memory(statistics *, student_init_data *, int);

int main(){
	student_init_data students[N];
	int i, n;
	for(i = 0; i < N; i++){
		printf("Please type student #%d ID\n", i+1);
		scanf("%d", &((students+i)->ID));
		printf("Please type student #%d number of grades\n", i+1);
		scanf("%d", &n);
		(students+i)->amount_exams = n;
		(students+i)->grades = Input_Data(n);
	}
	statistics all;
	Classification(students, N, &all);
	Print_Tab(&all);
	Free_Memory(&all, students, N);
	return 0;
}

int * Input_Data(int num){
	int i, * grades  = (int *)malloc(num * sizeof(num));
	for(i = 0; i < num; i++){
		printf("Please type #%d grade\n", i+1);
		scanf("%d", grades+i);
	}
	return grades;
}

double Student_Average(student_init_data *data){
	int i, n = data->amount_exams;
	double sum = 0;
	for(i = 0; i < n; i++)
		sum += *(data->grades + i);
	sum /= n;
	return sum;
}

double Total_Average(double *avgArr, int n){
	int i;
	double sum = 0;
	for (i = 0; i < n; i++)
		sum += *(avgArr+i);
	sum /= n;
	return sum;
}

void Classification(student_init_data *data, int n, statistics *ptr){
	ptr->belowSz = ptr->aboveSz = 0;
	int i;
	double * avgArr = (double *)malloc(sizeof(double) * N);
		for(i = 0; i < n; i++)
			*(avgArr+i) = Student_Average(data+i);
	ptr->general_avg = Total_Average(avgArr, n);
	for(i = 0; i < n; i++){
		if(*(avgArr+i) >= ptr->general_avg)
			ptr->aboveSz++;
		else
			ptr->belowSz++;
	}
	ptr->aboveAvg = (student_processed_data *)malloc(ptr->aboveSz * sizeof(student_processed_data));
	ptr->belowAvg = (student_processed_data *)malloc(ptr->belowSz * sizeof(student_processed_data));
	int j = 0, k = 0;
	for(i = 0; i < n; i++){
		if(*(avgArr+i) >= ptr->general_avg){
			(ptr->aboveAvg + j)->ID = (data+i)->ID;
			(ptr->aboveAvg + j)->avg = *(avgArr+i);
			j++;
		}
		else{
			(ptr->belowAvg + k)->ID = (data+i)->ID;
			(ptr->belowAvg + k)->avg = *(avgArr+i);
			k++;
		}
	}
	free(avgArr);
	avgArr = NULL;
}

void Print_Tab(statistics *ptr){
	int i;
	printf("\n\nThe average grade of all average grades of all students is : %.2lf\n", ptr->general_avg);
	printf("%d students score below the average, ", ptr->belowSz);
	printf("whilst %d students score above.\n\n", ptr->aboveSz);
	printf("Students below average, their ID followed by their average grade :\n");
	for(i = 0; i < ptr->belowSz ; i++)
		printf("%d : %.2lf\n", (ptr->belowAvg + i)->ID, (ptr->belowAvg + i)->avg);
	printf("Students above average :\n");
	for(i = 0; i < ptr->aboveSz ; i++)
		printf("%d : %.2lf\n", (ptr->aboveAvg + i)->ID, (ptr->aboveAvg + i)->avg);
}


void Free_Memory(statistics *p1, student_init_data *p2, int n){
	int i;
	for(i = 0; i < n; i++){
		free((p2+i)->grades);
		(p2+i)->grades = NULL;
	}
	free(p1->aboveAvg);
	p1->aboveAvg = NULL;
	free(p1->belowAvg);
	p1->belowAvg = NULL;
	free(p1);
	p1 = NULL;
}
