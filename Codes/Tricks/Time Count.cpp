clock_t start,finish;
double timespent;
start=clock();
//Here Comes your Code/Function
finish=clock();
timespent=(double)(finish-start)/CLOCKS_PER_SEC;
cout << timespent << '\n';
