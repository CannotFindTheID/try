#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
using namespace std;
//集合覆盖问题

bool **a;//矩阵
bool *solution;//m维的解
bool *best_solution;//最佳解
bool *iscovered;//第i行是否被覆盖
short *uncovered_num;//第j列包含多少未被覆盖的行
short *origin_uncovered_num;//初始数据
int cost=0,min_cost=INT_MAX;
int m,n,max_elem;


//初始化
void Init(){
    int i,j;
    a=new bool*[n];
    for(i=0;i<n;i++){
        a[i]=new bool[m];
    }

    solution=new bool[m];
    best_solution=new bool[m];
    iscovered=new bool[n];
    origin_uncovered_num=new short[m];
    uncovered_num=new short[m];
    for(i=0;i<n;i++){
        for(j=0;j<m;j++)
            a[i][j]=false;
        iscovered[i]=0;
    }
    for(j=0;j<m;j++){
            solution[j]=false;
            uncovered_num[j]=0;
            origin_uncovered_num[j]=0;
    }
}
//释放内存
void FreeResources(){
    for(int i=0;i<n;i++){
        delete(a[i]);
    }
    delete(a);
    delete(solution);
    delete(best_solution);
    delete(iscovered);
    delete(uncovered_num);
    delete(origin_uncovered_num);
}
//读取数据集
void ReadDataFromFile(string filename){
    ifstream fin(filename);
    int i=0,j=0;
    int x=0,y,num;//x为元素，y为集合
    string line;
    vector<int> temp1;
    while (getline(fin,line)) {
        stringstream ss;
        ss<<line;
        if (!ss.eof()) {
            if(j==0){
                ss>>n;
                ss>>m;
                Init();
                j=1;
                continue;
            }else if(i==0){
                ss>>x;
            }else if(i==1){
                ss>>num;
            }else if(i==2){
                while (ss >> y){
                    a[x][y]=true;
                    uncovered_num[y]++;
                    origin_uncovered_num[y]++;
                }
            }
        }
        i=(i+1)%3;
    }
    fin.close();
//    for(i=0;i<n;i++){
//        for(j=0;j<m;j++)
//            cout<<a[i][j];
//        cout<<endl;
//    }
}
//贪心算法
void Greedy(){
    short max_num=uncovered_num[0],temp=0;
    int i,j=0;
    cost=0;
    while(1){
        max_num=0;
        for(i=0;i<m;i++){//找到最多未覆盖
            if(solution[i]==false&&uncovered_num[i]>max_num){
                max_num=uncovered_num[i];
                temp=i;
            }

        }
        //如果所有行被覆盖，则结束
        if(max_num==0)break;

        if(j==0){
            max_elem=temp;//记下当次贪婪最大的编号
            j=1;
        }

        //加入解中
        solution[temp]=true;
        for(int j=0;j<n;j++){
            if((a[j][temp]==true)&&iscovered[j]==false){
                iscovered[j]=true;
                for(int k=0;k<m;k++)
                    if(solution[k]==false&&a[j][k]==true)uncovered_num[k]--;
            }
        }
        cost++;
    }
}
//输出文件
void WriteDataToFile(string filename){
    ofstream fout(filename);
    if(fout){
        fout<<min_cost<<endl;
        for(int i=0;i<m;i++){
            if(best_solution[i]==true)
                fout<<i<<" ";
        }
    }
    fout.close();
}
//每次筛掉origin_uncovered_num最大的集合
void DeleteMaxFromSolution(){
    //还原uncovered_num
    origin_uncovered_num[max_elem]=0;//去掉最大的
    memmove(uncovered_num,origin_uncovered_num,sizeof(int)*m);
}
//调整得到更优解
void Update(int times){
    int flag=1;//是否是可行解
    for(int i=0;i<times;i++){
        DeleteMaxFromSolution();
        //判断是否可行
        for(int j=0;j<n;j++){
            if(iscovered[j]==false)flag=0;
        }
        if(flag==1&&cost<min_cost){
            //更改最优解
            cout<<"更优解为："<<cost<<endl;
            min_cost=cost;
            memmove(best_solution,solution,sizeof(bool)*m);
        }
        for(int i=0;i<m;i++)solution[i]=false;
        for(int i=0;i<n;i++)iscovered[i]=false;
        Greedy();
    }
}
//主函数
int main(){
    ReadDataFromFile("C:/Users/diandian/Desktop/test/test01.txt");

    //运行算法并输出时间
    time_t start_time = clock();
    Greedy();
    Update(1000);
//    time_t end_time = clock();
//    cout<<"运算毫秒数为："<<double(end_time-start_time)*1000/CLOCKS_PER_SEC;

    WriteDataToFile("C:/Users/diandian/Desktop/result/test01.txt");
    FreeResources();
    return 0;
}
