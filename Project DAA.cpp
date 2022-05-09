#include<iostream>
#include<fstream>
#include<regex>
#include<iomanip>
#include<string.h>

using namespace std;

int main()
{
    string INDIA[]={"Rahane","Rohit Sharma","Kohli","Pandey","Jadhav","Hardik","Dhoni","Bhuvneshwar","Kuldeep","Bumrah","Chahal"};
    string AUSTRALIA[]={"Coulter-Nile","Agar","Kane Richardson","Cummins","Stoinis","Head"};
    int i=0,j=0,num=0,total=0;
    string line,INPUT_FILE,OUTPUT_FILE,L,str;
    float strike_rate[11]={0},runs[11]={0},dot_ball[11]={0},fours[11]={0},sixes[11]={0},balls[11]={0};
    float overs[6]={0},Balls[6]={0},dot[6]={0},RUNS[6]={0},noball[6]={0},wide[6]={0},byes[6]={0},eco[6]={0},w[6]={0};
    float crr,Extras,rrr;

    INPUT_FILE="Commentary.txt";
    OUTPUT_FILE="Scoreboard.txt";
    cout<<endl<<"********************INDIA VS AUSTRALIA********************"<<endl;
    cout<<endl<<"#Short Commentary of match over by over is given below#"<<endl;
    ifstream fin;
    fin.open(INPUT_FILE);
    while(fin)
    {
        int vis[50]={0};
        getline(fin,line);
        L=line;
        if((L.find(" to ")==-1)||(L.find(", ")==-1))
        {
            continue;
        }
        static int n=0;
        for(i=0;i<11;i++)
        {
            if((L.find(INDIA[i])==-1))
                continue;
            for(j=0;j<6;j++)
            {
                if((L.find(AUSTRALIA[j])==-1))
                    continue;
                else
                {
                    str="";
                    str=str.append(AUSTRALIA[j]);
                    str=str.append(" to ");
                    str=str.append(INDIA[i]);
                    str=str.append(", ");

                    if((L.find(str)!=-1))
                    {
                        if((n%6==0)&&((vis[n/6])==0))
                        {
                            vis[(n/6)]=1;
                            if(n/6==0)
                                cout<<endl<<" "<<(n/6)+1<<"st Over:\n";
                            else if(n/6==1)
                                cout<<endl<<" "<<(n/6)+1<<"nd Over:\n";
                            else if(n/6==2)
                                cout<<endl<<" "<<(n/6)+1<<"rd Over:\n";
                            else
                                cout<<endl<<" "<<(n/6)+1<<"th Over:\n";
                        }
                        cout<<" "<<L<<"\n";

                        if(L.find(", 1 run")!=-1)// ==-1 (not found) !=-1 (found)
                            num=1;
                        else if(L.find(", 2 runs")!=-1)
                            num=2;
                        else if(L.find(", 3 runs")!=-1)
                            num=3;
                        else if(L.find(", FOUR runs")!=-1)
                        {
                            num=4;
                            fours[i]++;
                        }
                        else if(L.find(", SIX runs")!=-1)
                        {
                            num=6;
                            sixes[i]++;
                        }
                        else if(L.find(", no run")!=-1)
                        {
                            num=0;
                            dot[j]++;
                        }
                        else if(L.find(", OUT")!=-1)
                        {
                            num=0;
                            w[j]++;
                        }
                        else if(L.find(", 1 wide")!=-1)
                        {
                            num=1;
                            wide[j]++;
                            --runs[i];
                            --Balls[j];
                            --n;
                            --balls[i];
                        }
                        else if(L.find(", 2 wide")!=-1)
                        {
                            num=2;
                            wide[j]++;
                            runs[i]-=2;
                            --Balls[j];
                            --n;
                            --balls[i];
                        }
                        else if(L.find(", 1 leg bye")!=-1)
                        {
                          num = 1;
                          byes[j]++;
                          runs[i]--;
                          --RUNS[j];
                        }
                        else if(L.find(",1 bye")!=-1)
                        {
                          num = 1;
                          byes[j]++;
                          total+=1;
                          runs[i]--;
                          --RUNS[j];
                        }
                        else if(L.find(", (no ball)")!=-1)
                        {
                            num = 1;
                            noball[j]++;
                            runs[i]--;
                            --Balls[j];
                            --n;
                        }
                        else if(L.find(", (no ball) 1 run")!=-1)
                        {
                                num = 2;
                                noball[j]++;
                                runs[i]--;
                                --Balls[j];
                                --n;
                        }
                        else if(L.find(", (no ball) 2 run")!=-1)
                            {
                                num = 3;
                                noball[j]++;
                                runs[i]--;
                                --n;
                                --Balls[j];
                            }

                        runs[i]+=num;
                        RUNS[j]+=num;
                        total+=num;
                        balls[i]++;
                        Balls[j]++;
                        ++n;
                    }
                }
            }
        }
    }

    for(i=0;i<11;i++)
    {
        if(balls[i]==0)
            strike_rate[i]=0.0;
        else
            strike_rate[i]=(float)((runs[i]/balls[i])*100);
    }
    for(j=0;j<6;j++)
    {
        if(Balls[j]==0)
            eco[j]=0;
        else
            eco[j]=(float)((RUNS[j]/Balls[j])*6);
    }
    for(j=0;j<6;j++)
    {
        overs[j]=(Balls[j]/6);
    }
    crr=total/50.0;
    rrr=(total+1)/50.0;
    fin.close();
    i=0;
    ofstream fout;
    fout.open(OUTPUT_FILE);
    fout<<"********************INDIA VS AUSTRALIA 2nd ODI********************"<<endl;
    fout<<"******************** 1st Inning Scorecard ********************"<<endl;
    fout<<"INDIA BATTING SCORECARD: "<<endl<<endl;
    fout<<left<<setw(30)<<"Batsman Name"<<left<<setw(10)<<"RUNS"<<left<<setw(10)<<"BALLS"<<left<<setw(10)<<"FOURS"<<left<<setw(10)<<"SIXES"<<left<<setw(10)<<"Strike Rate"<<endl;
    while(fout&&i<11)
    {
        fout<<left<<setw(30)<<INDIA[i]<<left<<setw(10)<<runs[i]<<left<<setw(10)<<balls[i]<<left<<setw(10)<<fours[i]<<left<<setw(10)<<sixes[i]<<left<<setw(10)<<strike_rate[i]<<endl;
        i++;
    }
    j=0;
    fout<<"================================================================================================="<<endl;
    fout<<endl<<"AUSTRALIA BOWLING SCOREBOARD: "<<endl<<endl;
    fout<<left<<setw(30)<<"Bowlers Name"<<left<<setw(10)<<"Overs"<<left<<setw(10)<<"RUNS"<<left<<setw(10)<<"DOT BALLS"<<left<<setw(10)<<"Wickets"<<left<<setw(10)<<"ECONOMY"<<left<<setw(10)<<"WIDE"<<left<<setw(20)<<"NO balls"<<endl;
    while(fout&&j<6)
    {
        fout<<left<<setw(30)<<AUSTRALIA[j]<<left<<setw(10)<<overs[j]<<left<<setw(10)<<RUNS[j]<<left<<setw(10)<<dot[j]<<left<<setw(10)<<w[j]<<left<<setw(10)<<eco[j]<<left<<setw(10)<<wide[j]<<left<<setw(20)<<noball[j]<<endl;
        j++;
    }
    fout<<endl<<"AUSTRALIA NEEDS "<<total+1<<" RUNS IN 50 OVER TO WIN WITH REQUIRED RUN-RATE OF "<<rrr<<endl;
    fout.close();
    return 0;
}
