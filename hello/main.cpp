#include <iostream>
#include <string>
#include<iomanip>
#include<math.h>
using namespace std;
//注释快捷键ctrl+shift+c；解除注释ctrl+shift+x

//字符串题1
void print(char c){
    int base;
    //判断大小写
    if(c>=65&&c<=90){
        if(c<=90)base=65;
        else if(c>=97&&c<=122)base=97;
        else cout<<"不合法输出"<<endl;
    }else{
        cout<<"不合法输出"<<endl;
    }
    int num=c-base;
    int temp;
    for(int i=num;i>=0;i--){//每行
        temp=num;//重置
        while(temp>i){//输出空格
            temp--;
            cout<<" ";
        }
        for(int j=0;j<=i;j++){//正向输出
            cout<<(char)(base+j);
        }
        for(int j=i-1;j>=0;j--){//逆向输出
            cout<<(char)(base+j);
        }
        cout<<endl;//换行
    }
}

//字符串题2（有点问题，+32可能3位数以上）
class MyString
{
    public:
        string newStr;
        int length;
};
MyString compress(string str){
    //压缩后的新字符串
    MyString newStr;
    int length=str.size();
    string sub;
    int j;
    for(int i=0;i<length;i+=2){
        if(i<length-1){
            sub=str.substr(i,2);
        }else{
            //最后一组
            sub=str.substr(i,1)+'0';
        }
        newStr.newStr=newStr.newStr+to_string(stoi(sub,0,10)+32);//从0位置开始变为10进制数字，并加上32
        newStr.length=length;
    }
    cout<<"压缩成功"<<endl;
    return newStr;
}
string uncompress(MyString newStr){
    string str,sub;
    if(newStr.length%2==0){
        //如果为偶数
        for(int i=0;i<newStr.length;i+=2){
            sub=newStr.newStr.substr(i,2);
            str=str+to_string(stoi(sub,0,10)-32);
        }
    }else{
        //如果为奇数
        for(int i=0;i<newStr.length-1;i+=2){
            sub=newStr.newStr.substr(i,2);
            str=str+to_string(stoi(sub,0,10)-32);
        }
        sub=newStr.newStr.substr(newStr.length-1,2);
        cout<<sub;
        str=str+to_string(stoi(sub,0,10)-32).substr(0,1);//最后的数字
    }

    cout<<"解压缩成功"<<endl;
    return str;
}

//排序查找题3
float findAverage(float scores[]){
    int max_num=0,min_num=0;
    int i;
    float sum;
    for(i=1;i<=6;i++){
        //有更大值
        if(scores[i]>scores[max_num]){
            max_num=i;
        }
        //有更小值
        if(scores[i]<scores[min_num]){
            min_num=i;
        }
    }
    for(i=0;i<=6;i++){
        if(i!=min_num&&i!=max_num){
            sum+=scores[i];
        }
    }
    return sum/5;
}

//字符串题4
string deleteBlank(string str){
    //消除开头空格
    int i=0;
    while(i<str.size()&&isspace(str[i])){
        i++;
    }//i指向第一个非空字符
    return str.substr(i);
}
string mergeBlank(string str){
    //中间多个空格只保留一个
    int flag=0,i;//前面是否有空格
    string new_str;
    for(i=0;i<str.size();i++){
        if(isspace(str[i])&&flag==0){//第一个空格
            flag=1;
            new_str+=str[i];
        }else if(!isspace(str[i])){//非空格
            new_str+=str[i];
            if(flag==1)flag=0;
        }
    }
    return new_str;
}
string separate(string str){
    //数字字母间加上_
    int flag=2,i;//前面是字母为1，数字为0，空格为2
    for(i=0;i<str.size();i++){
        if(!isspace(str[i])&&flag==2){
            //第一个非空字符
            if(isalpha(str[i]))flag=1;
            else if(isdigit(str[i]))flag=0;
        }
        if(isalpha(str[i])&&flag==0){
            flag=1;
            str.insert(i,"_");//在此字符前插入
        }else if(isdigit(str[i])&&flag==1){
            flag=0;
            str.insert(i,"_");
        }
    }
    return str;
}

//标准c题5
void getPrime1(int n){//得到全部不小于n的素数（筛选）
    bool* b = new bool[n+1];
    for(int i=2;i<=n;i++){//从2开始进行筛选
        if(!b[i]){
            printf("%d\n",i);//输出素数
            for(int j=i+i;j<=n;j+=i){
                //为true的筛选掉
                b[j] = true;
            }
        }
    }
}
void getPrime2(int n){//得到全部不小于n的素数（计算）
    int j;
    for(int i=2;i<=n;i++){
        for(j=2;j<=sqrt(i);j++){
            if(i%j==0)break;
        }
        if(j>sqrt(i))printf("%d\n",i);
    }
}
void twinPrime(int m){//两个数均不超过m的最大孪生素数
    //可以用第一个程序，先找到2~m的所有素数，从后往前判断
}

//标准c题6
void printMatrix(int n){//n维方阵的顺转方阵
    //方阵
    int **matrix=(int **)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        matrix[i]=(int *)malloc(sizeof(int)*n);
    }
    int *r=(int *)malloc(sizeof(int)*n);//每行已定元素数
    int *c=(int *)malloc(sizeof(int)*n);//每列已定元素数
    for(int i=0;i<n;i++){//初始化
        r[i]=0;
        c[i]=0;
    }

    int x=0,y=-1;
    int flag=0;//表示下一个数字的填写方向——0/1/2/3
    for(int j=1;j<pow(n,2)+1;j++){
        //根据方向改变位置，填入数字
        if(j==25)printf("%f\n",pow(n,2));//就离谱
        switch(flag){
            case 0:y++;break;
            case 1:x++;break;
            case 2:y--;break;
            case 3:x--;break;
            default:printf("错误");
        }
        matrix[x][y]=j;
        //修改
        r[x]++;
        c[y]++;
        if(flag==0&&r[x]>=n){
            //此行满了
            flag=1;
        }else if(flag==1&&c[y]>=n){
            flag=2;
        }else if(flag==2&&r[x]>=n){
            flag=3;
        }else if(flag==3&&c[y]>=n){
            flag=0;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            printf("%d ",matrix[i][j]);
        printf("\n");
    }
    //释放
    free(r);
    free(c);
    for(int i=0;i<n;i++)
        free(matrix[i]);
    free(matrix);
}



int main()
{
//程序1
//    cout<<"请输入字符："<<endl;
//    char c;
//    cin>>c;
//    print(c);

//程序2
//    string str1,str2;
//    do{
//       cout<<"请输入字符串"<<endl;
//       cin>>str1;
//    }while(str1.empty());//如果为空或不全为数字，继续读取
//
//    MyString newStr=compress(str1);
//    cout<<"已压缩为："<<newStr.newStr<<endl;
//    str2=uncompress(newStr);
//    cout<<"解压得原文为："<<str2<<endl;

//程序3
//    cout<<"请输入七位评委评分："<<endl;
//    float scores[7];
//    for(int i=0;i<7;i++){
//        cin>>scores[i];
//    }
//    float average_score=findAverage(scores);
//    cout<<fixed<<setprecision(1)<<"平均分为："<<average_score<<endl;

//程序4
//    string str,new_str;
//    cout<<"请输入一串字符："<<endl;
//    getline(cin,str);//因为输入的字符串含空格，要用这种方法输入
//    new_str=separate(str);
//    cout<<"处理结果为："<<new_str<<endl;

//程序5
//    getPrime1(400);

//程序6
//    printMatrix(5);

//程序7
}

