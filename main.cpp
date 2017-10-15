//coding=utf-8
#include <iostream>
#include <string.h>
using namespace std;

#define M 20
int college_num=20,item_num=20;
int man_item_num=20;
int item_data[M][M];
int choice;
string item_name[M];
string college_name[M];
string file_path=NULL,file_name=NULL;
typedef struct college_data
{
    int id;
    string name;
    int score[M];
    int score_sum,item_man_sum,item_woman_sum;
}college_data;

void init_menu()
{
    cout<<"您想在线输入比赛成绩or从已有文件读取数据？"<<endl;
    cout<<">>>1.在线输入比赛成绩"<<endl<<">>>2.从已有文件读取数据"<<endl<<"请输入您的选择：(1 or 2)"<<endl;
    cin>>choice;
    while(choice<=0||choice>2)
    {
        cout<<"超出范围！！！"<<endl<<"请重新输入(1 or 2)"<<endl;
        cin>>choice;
    }
    return;
}

void if_file_path()
{
    if(file_path==NULL)
    {
        cout<<"请输入文件存储的位置"<<endl;
        cin>>file_path;
    }
    if(file_name==NULL)
    {
        cout<<"请输入文件的名称"<<endl;
        cin>>file_name;
    }
}

void write_file()
{
    FILE *file;
    string temp_path;
    if_file_path();
    temp_path=file_path;
    temp_path+=file_name;
    file=fopen(temp_path,'w');
    while(file==NULL)
    {
        cout<<"请输出有效的路径"<<endl;
        cin>>file_path;
        temp_path=file_path;
        temp_path+=file_name;
        file=fopen(temp_path,'w');
    }
    fprintf(file,"%d%d%d",college_num,item_num,man_item_num);
    for(int i=0;i<item_num;i++)
    {
        int temp;
        if(i<man_item_num)
            temp=3;
        else
            temp=5;
        for(int j=0;j<temp;j++)
        {
            fprintf(file,"%d",item_data[i][j]);
        }
    }
    for(int i=0;i<item_num;i++)
    {
        fprintf(file,"%s",item_name[i]);
    }
    for(int i=0;i<college_num;i++)
    {
        fprintf(file, "%s", college_name[i]);
    }
    fclose(file);
}

void read_file()
{
    FILE *file;
    string temp_path;
    if_file_path();
    temp_path=file_path;
    temp_path+=file_name;
    file=fopen(temp_path,'w');
    while(file==NULL)
    {
        cout<<"请输出有效的路径"<<endl;
        cin>>file_path;
        temp_path=file_path;
        temp_path+=file_name;
        file=fopen(temp_path,'w');
    }
    fscanf(file,"%d%d%d",&college_num,&item_num,&man_item_num);
    for(int i=0;i<college_num;i++)
    {
        int temp;
        if(i<man_item_num)
            temp=3;
        else
            temp=5;
        for(int j=0;j<temp;j++)
        {
            fscanf(file,"%d",&item_data[i][j]);
        }
    }
    for(int i=0;i<item_num;i++)
    {
        fscanf(file,"%s",&item_name[i]);
    }
    for(int i=0;i<college_num;i++)
    {
        fscanf(file, "%s", &college_name[i]);
    }
    fclose(file);
}

void menu()
{
    cout<<"##成绩系统菜单##"<<endl;
    cout<<">>>1.按学院  编号排序输出"<<endl;
    cout<<">>>2.按学院  名字排序输出"<<endl;
    cout<<">>>3.按学院  总分排序输出"<<endl;
    cout<<">>>4.按学院  男生团体总分输出"<<endl;
    cout<<">>>5.按学院  女生团团体总分输出"<<endl;
    cout<<">>>6.按学院  编号查询某个项目的情况"<<endl;
    cout<<">>>7.按项目编号查询有成绩的学院"<<endl;
    cout<<">>>8.修改学院的名称"<<endl;
    cout<<">>>9.修改项目的名称"<<endl;
    cout<<">>>10.退出"<<endl;
    cin>>choice;
}

class university
{
public:
    college_data college[M];
    university()
    {
        for(int i=0;i<college_num;i++)
        {
            college[i].id=i;
            college[i].name="学院";
            college[i].name+=(char)(i+'0');
            college_name[i]=college[i].name;
            memset(college[i].score,0, sizeof(college[i].score));
        }
        for(int i=0;i<item_num;i++)
        {
            if(i<man_item_num)
            {
                for(int j=0;j<3;j++)
                {
                    switch (j)
                    {
                        case 0:
                            college[item_data[i][j]].score[i]=5;
                            break;
                        case 1:
                            college[item_data[i][j]].score[i]=3;
                        case 2:
                            college[item_data[i][j]].score[i]=2;
                        default:;
                    }
                }
            }
            else
            {
                for(int j=0;j<5;j++)
                {
                    switch (j)
                    {
                        case 0:
                            college[item_data[i][j]].score[i]=7;
                            break;
                        case 1:
                            college[item_data[i][j]].score[i]=5;
                        case 2:
                            college[item_data[i][j]].score[i]=3;
                        case 3:
                            college[item_data[i][j]].score[i]=2;
                        case 4:
                            college[item_data[i][j]].score[i]=1;
                        default:;
                    }
                }
            }
        }
        for(int i=0;i<college_num;i++)
        {
            college[i].score_sum=0;
            college[i].item_man_sum=0;
            college[i].item_woman_sum=0;
            for(int j=0;j<item_num;j++)
            {
                college[i].score_sum+=college[i].score[j];
                if(j<man_item_num)
                    college[i].item_man_sum+=college[i].score[j];
                else
                    college[i].item_woman_sum+=college[i].score[j];
            }
        }
    }

    void sort_by_sum()
    {
        for(int i=0;i<college_num;i++)
        {
            int j=i;
            int max_num = college[i].score_sum;
            for(int k=i+1;k<college_num;k++)
            {
                if(max_num<college[k].score_sum)
                {
                    max_num = college[k].score_sum;
                    j=k;
                }
            }
            if(j!=i)
            {
                swap(i,j);
            }
        }
        print_out();
    }

    void sort_by_man_sum()
    {
        for(int i=0;i<college_num;i++)
        {
            int j=i;
            int max_num = college[i].item_man_sum;
            for(int k=i+1;k<college_num;k++)
            {
                if(max_num<college[k].item_man_sum)
                {
                    max_num = college[k].item_man_sum;
                    j=k;
                }
            }
            if(j!=i)
            {
                swap(i,j);
            }
        }
        print_out();
    }

    void sort_by_woman_sum()
    {
        for(int i=0;i<college_num;i++)
        {
            int j=i;
            int max_num = college[i].item_woman_sum;
            for(int k=i+1;k<college_num;k++)
            {
                if(max_num<college[k].item_woman_sum)
                {
                    max_num = college[k].item_woman_sum;
                    j=k;
                }
            }
            if(j!=i)
            {
                swap(i,j);
            }
        }
        print_out();
    }

    void sort_by_id()
    {
        for(int i=0;i<college_num;i++)
        {
            int j=i;
            int max_num = college[i].id;
            for(int k=i+1;k<college_num;k++)
            {
                if(max_num<college[k].id)
                {
                    max_num = college[k].id;
                    j=k;
                }
            }
            if(j!=i)
            {
                swap(i,j);
            }
        }
        print_out();
    }

    void sort_by_name()
    {
        for(int i=0;i<college_num;i++)
        {
            int j=i;
            string min_name = college[i].name;
            for(int k=i+1;k<college_num;k++)
            {
                if(min_name>college[k].name)
                {
                    min_name = college[k].name;
                    j=k;
                }
            }
            if(j!=i)
            {
                swap(i,j);
            }
        }
        print_out();
    }

    void search_by_id(int search_id,int search_item_id)
    {
        if(search_id>=college_num||search_id<0||search_item_id<0||search_item_id>=item_num)
        {
            cout<<"访问的数据超出范围"<<endl;
            return;
        }
        for(int i=0;i<college_num;i++)
        {
            if(college[i].id==search_id)
                cout<<"您要找的学院是\t"<<college[i].name<<endl<<"您要找的项目是\t"<<item_name[search_item_id]<<endl<<"得分为:\t"<<college[i].score[search_item_id]<<endl;
        }
    }

    void search_by_item(int search_item_id)
    {
        if(search_item_id<0||search_item_id>=item_num)
        {
            cout<<"访问的数据超出范围"<<endl;
            return;
        }
        cout<<"您要找的项目"<<item_name[search_item_id]<<"的排名如下"<<endl;
        if(search_item_id<man_item_num)
        {
            for(int i=0;i<3;i++)
            {
                cout<<"名次"<<i<<"\t"<<college_name[item_data[search_item_id][i]]<<endl;
            }
        }
        else
        {
            for(int i=0;i<5;i++)
            {
                cout<<"名次"<<i<<"\t"<<college_name[item_data[search_item_id][i]]<<endl;
            }
        }
    }

    void print_out()
    {
        cout<<"学院编号\t学院名称\t总分\t男生团体总分\t女生团体总分\t排名"<<endl;
        for(int i=0;i<college_num;i++)
        {
            cout<<college[i].id<<"\t"<<college[i].name<<"\t"<<college[i].score_sum<<"\t"<<college[i].item_man_sum<<"\t"<<college[i].item_woman_sum<<"\t"<<i<<endl;
        }
    }
private:
    void swap(int i,int j)
    {
        college_data temp = college[i];
        college[i] = college[j];
        college[j] = temp;
    }
};

int main() {
    choice = 0;
    init_menu();
    if(choice==1)
    {
        do
        {
            cout<<"请输入学院的数量：(请勿大于20)"<<endl;
            cin>>college_num;
        }while(college_num>20||college_num<=0);
        do
        {
            cout<<"请输入项目的数量：(请勿大于40)"<<endl;
            cin>>item_num;
        }while(item_num>40||item_num<=0);
        do
        {
            cout<<"请输入男生项目的数量：(请勿大于40)"<<endl;
            cin>>man_item_num;
        }while(man_item_num>20||man_item_num<=0);
        cout<<"开始输入"<<item_num<<"个项目的成绩："<<endl;
        for(int i=0;i<item_num;i++)
        {
            if(i<man_item_num)
            {
                cout<<">>>请输入第"<<i+1<<"个项目的前3名学院编号："<<endl;
                for(int j=0;j<3;j++)
                {
                    cin>>item_data[i][j];
                }
            }
            else
            {
                cout<<">>>请输入第"<<i+1<<"个项目的前5名学院编号："<<endl;
                for(int j=0;j<5;j++)
                {
                    cin>>item_data[i][j];
                }
            }
        }

    }
    else
        read_file();

    university hit;
    return 0;
}
