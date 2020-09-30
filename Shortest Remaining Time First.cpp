#include <bits/stdc++.h> //library
using namespace std;

FILE *Outputfile()
{
    return fopen("output.txt","a");
}
//structure
struct Process {
   int pid;
   int bt;
   int art;
};

void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
   for (int i = 0; i < n; i++)
   tat[i] = proc[i].bt + wt[i];
}
// find the waiting time
void findWaitingTime(Process proc[], int n, int wt[]) {
   int rt[n];
   for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;
   int complete = 0, t = 0, minm = INT_MAX;
   int shortest = 0, finish_time;
   bool check = false;
   while (complete != n) {
      for (int j = 0; j < n; j++) {
         if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) {
            minm = rt[j];
            shortest = j;
            check = true;
         }
      }
      if (check == false) {
         t++;
         continue;
      }
      rt[shortest]--;
      minm = rt[shortest];
      if (minm == 0)
         minm = INT_MAX;
         if (rt[shortest] == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            wt[shortest] = finish_time -
            proc[shortest].bt -
            proc[shortest].art;
            if (wt[shortest] < 0)
               wt[shortest] = 0;
         }
         t++;
   }
}
// find average time to read it
void findavgTime(Process proc[], int n) {
   static int i=1;
   int wt[n], tat[n], total_wt = 0,
   total_tat = 0;
   float awt,atat;
   char avgwt[]="Average waiting time = ",avgtat[]="Average turn around time = ",
   p[]="Process       Arrival Time      Brust time        Waiting time    Turn Around Time";
   ofstream out,graph;
   out.open("output.csv", ios::app);
   graph.open("graph.csv", ios::app);
   findWaitingTime(proc, n, wt);
   findTurnAroundTime(proc, n, wt, tat);
   FILE *fp = Outputfile();
   fputs(p,fp);
   out <<"Processes" <<","<<"Arrival Time"<<","<<"Brust Time" << "," << "Waiting Time" << "," << "Turn Around Time" << endl;
   cout << "Processes " << " Arrival time " << " Brust time " << " Waiting time " << " Turn around time\n";
   for (int i = 0; i < n; i++) {
      total_wt = total_wt + wt[i];
      total_tat = total_tat + tat[i];
      cout << " " << proc[i].pid << "\t\t" << proc[i].art << "\t " << proc[i].bt << "\t\t "<< wt[i] << "\t\t " << tat[i] << endl;
        fprintf(fp,"\n%d\t\t%d\t\t\t%d\t\t%d\t\t%d",proc[i].pid, proc[i].art,proc[i].bt,wt[i],tat[i] );
        out << proc[i].pid <<","<< proc[i].art <<","<< proc[i].bt << "," << wt[i] << "," << tat[i] << endl;
   }
   awt=(float)total_wt / (float)n;
   atat=(float)total_tat / (float)n;
   cout << "\nAverage waiting time = " << awt; cout << "\nAverage turn around time = " << atat;
   fprintf(fp,"\n");
    fputs(avgwt,fp);
    fprintf(fp,"%f\t\t",awt);
    fputs(avgtat,fp);
    fprintf(fp,"%f\n",atat);
    out << "Total" << "," << "," << "," << total_wt << "," << total_tat << endl;
    out << "Average" << "," << "," << "," << awt << "," << atat << endl;
    graph << total_wt << "," << total_tat << "," << awt << "," << atat << endl;
}

int main()
{
    int x,y,i,j;
    char name[30];
    Process proc[5];
    ofstream graph;
    FILE *fptr,*fp,*op,*ch;
	fptr=fopen("input.txt","r");
	fp=fopen("output.txt","w");
	op=fopen("output.csv","w");
	ch=fopen("graph.csv","w");
	graph.open("graph.csv", ios::app);
	graph << "Total Waiting Time" << "," << "Total Turn Around Time" << "," << "Average Waiting Time" << "," << "Average Turn Around Time" <<endl;
    for(x=1;x<51;x++)
    {
        fscanf(fptr, "%d",&y);
        fscanf(fptr,"%s\n",name);
        printf("\n%d\n",y);
        for ( i = 0; i < 5; i++ )
            {
                    for ( j = 0; j < 3; j++ )
                    {
                        if(j==0)
                            fscanf(fptr, "%d",&proc[i].pid);
                        else if(j==1)
                            fscanf(fptr, "%d",&proc[i].art);
                        else
                            fscanf(fptr, "%d",&proc[i].bt);
                    }
            }

        int n = sizeof(proc) / sizeof(proc[0]);
        findavgTime(proc, n);
    }
    fclose(fptr);
    fclose(fp);
    return 0;
}
