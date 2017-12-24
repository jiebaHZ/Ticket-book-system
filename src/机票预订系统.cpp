#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#define N 100//航班数量 
#define M 1000//乘客数量 
using namespace std;
class passenger{
private: 
	char ID[20];//身份证号
	char name[20];//姓名
	char sex[10];//性别
	char phone[20];//手机号
	char card[30];//银行卡号
	char code[30];//密码 
	int num[20];//所乘航班号
public:
	passenger(){}
	char* get_ID()                  {return ID;}
	char* get_name()                {return name;}
	char* get_sex()                 {return sex;}
	char* get_phone()               {return phone;}
	char* get_card()                {return card;}
	char* get_code()                {return code;}
	int* get_num()                  {return num;}
	void set_ID(char a[])           {strcpy(ID,a);}
	void set_name(char a[])         {strcpy(name,a);}
	void set_sex(char a[])          {strcpy(sex,a);}
	void set_phone(char a[])        {strcpy(phone,a);}
	void set_card(char a[])         {strcpy(card,a);}
	void set_code(char a[])         {strcpy(code,a);}
	void set_num(int a[])           {for(int k=0;k<20;k++)num[k]=a[k];}
	int login();//登陆 
	void enroll();//注册 
	void order();//订票
    void refund();//退票
    void check();//查看订单 
    ~passenger(){}
};//乘客类

class passenger_manage{
private:
	passenger p[M];//乘客对象数组 
	int i;//数组下标 
public:
	passenger_manage();//文件读取 
	int search_p(char a[]);//寻找乘客,返回数组下标 
	~passenger_manage();//写入文件 
	friend class passenger;
};//乘客信息管理类 

class air{
private:
    int num;//航班号
    char start[20];//起始站
    char end[20];//终点站
    char time[30];//时间
    int count;//规定机票数 
    int r_count;//已定机票数
public:
	air(){}
	int get_num()                   {return num;}
	char* get_start()               {return start;}
	char* get_end()                 {return end;}
	char* get_time()                {return time;}
	int get_count()                 {return count;}
	int get_r_count()               {return r_count;}
	void set_num(int a)             {num=a;}
	void set_start(char a[])        {strcpy(start,a);}
	void set_end(char a[])          {strcpy(end,a);}
	void set_time(char a[])         {strcpy(time,a);}
	void set_count(int a)           {count=a;}
    void set_r_count(int a)         {r_count=a;}
	void add();//添加航班信息
	void delet();//删除航班信息
    void search();//查询航班信息
    void change();//修改航班信息 
	~air(){}
};//航班类 

class air_manager{
private:
	air a[N];//航班对象数组 
	int i;//数组下标 
public:
	air_manager();//文件读取 
	int search_num();//用航班号搜索航班,返回数组下标 
	void delte1(int k);//从数组中删除方式1 
	void delte2();//从数组中删除方式2 
	~air_manager();//写入文件 
	friend class air;
	friend void passenger::order();
	friend void passenger::refund();
	friend void passenger::check();
};//航班信息管理类 

//航班类成员函数 
void air::add(){
	air_manager Air;
	cout << "请输入航班号："; 	          cin >> num;         Air.a[Air.i].set_num(num);//放入航班对象数组 
	cout << endl << "请输入起始站：";     cin >> start;       Air.a[Air.i].set_start(start);
	cout << endl << "请输入终点站：";     cin >> end;         Air.a[Air.i].set_end(end);
	cout << endl << "请输入时间：";       cin >> time;        Air.a[Air.i].set_time(time);
	cout << endl << "请输入规定机票数："; cin >> count;       Air.a[Air.i].set_count(count);
	Air.a[Air.i].set_r_count(0);//已定机票数初始化为0 
	Air.i++;//航班数组下标加一 
	cout << endl << "该航班已添加成功！"<< endl<< endl ;
}//添加航班信息 

void air::search(){
	int in,x; 
	air_manager Air;
      cout << "***** 请选择查找方式: *****" << endl << endl;
      cout << "***** 1  按航班号查找 *****" << endl;
      cout << "***** 2  按航线查找   *****" << endl;
      cout << "***** 0  返回         *****" << endl << endl;
      cout << "请在0-3中选择："; cin >> in;
    if(in==0) return;//返回 
    switch(in){
       case 1:
          x=Air.search_num();//找出数组下标 
          if(x==-1) return; //无此航班 
          cout << "查询结果如下：" << endl;
		  cout << "航班号        起始站        终点站        时间        已定机票数" << endl;
		  cout <<"  "<<Air.a[x].num<<"            "<<Air.a[x].start<<"         "<<Air.a[x].end<<"         "
			   <<Air.a[x].time<<"         "<<Air.a[x].r_count<<"/"<<Air.a[x].count<<endl;
		  cout <<endl<<endl<<endl;
       break;
       case 2:
	      cout << endl << "请输入起始站："; cin >> start;
	      cout << endl << "请输入终点站："; cin >> end;
	      cout <<endl<<endl<< "查询结果如下：" << endl;
	      cout << "航班号        起始站        终点站        时间        已定机票数" << endl;
	      for(int j=0;j<Air.i;j++)
	         if(strcmp(Air.a[j].get_start(),start)==0 && strcmp(Air.a[j].get_end(),end)==0){
			 cout <<"  "<<Air.a[j].num<<"            "<<Air.a[j].start<<"         "<<Air.a[j].end<<"         "
			      <<Air.a[j].time<<"         "<<Air.a[j].r_count<<"/"<<Air.a[j].count<<endl;
	         }//起点和终点相同，则打印 
	      cout <<endl<<endl<<endl;
       break;
       default:
         cout << "输入错误！请重新输入" << endl << endl << endl;
    }
}//查询航班信息 

void air::delet(){
	int in,x; 
	air_manager Air;
      cout << "***** 请选择删除方式: *****" << endl << endl;
      cout << "***** 1  按航班号删除 *****" << endl;
      cout << "***** 2  按航线删除   *****" << endl;
      cout << "***** 0  返回         *****" << endl << endl;
      cout << "请在0-3中选择："; cin >> in;
    if(in==0) return ;//返回 
    switch(in){
       case 1:
          x=Air.search_num();//找出数组下标 
          if(x==-1)return;//无此航班
          Air.delte1(x);//按航班号删除 
       break;
       case 2:
		  Air.delte2();//按航线删除 
       break;
       default:
         cout << "输入错误！请重新输入" << endl << endl << endl;
    }
}//删除航班 

void  air::change(){
	int j,in,x;
	air_manager Air;
	j=Air.search_num();//找出数组下标
	do{ system("cls");//清屏 
	cout << "***** 请选择修改内容: *****" << endl << endl;
    cout << "*****   1  起始站     *****" << endl;
    cout << "*****   2  终点站     *****" << endl;
    cout << "*****   3  时间段     *****" << endl;
    cout << "*****   0  返回       *****" << endl << endl;
	cout << "请在0-3中选择："; cin >> in;
	switch(in){
		case 1:{
			cout << "请输入新的起始站："; cin >> start;
			cout <<endl<< "是否确认修改:   1  是     2  否" <<endl;
			cin >> x;
			if(x==1) {
                Air.a[j].set_start(start); //放入数航班对象数组 
				cout <<endl<<"修改成功！";} 
			break;}
		case 2:{
			cout << "请输入新的终点站："; cin >> end;
			cout <<endl<< "是否确认修改:   1  是     2  否" <<endl;
			cin >> x;
			if(x==1) {
			    Air.a[j].set_end(end);//放入数航班对象数组 
				cout <<endl<<"修改成功！";} 
			break;}
		case 3:{
			cout << "请输入新的时间段："; cin >> time;
			cout <<endl<< "是否确认修改:   1  是     2  否" <<endl;
			cin >> x;
			if(x==1) {
			    Air.a[j].set_time(time);//放入数航班对象数组 
				cout <<endl<<"修改成功！";} 
			break;}
		case 0:
			break;
		default:
    		cout << "输入错误！请重新输入" << endl << endl << endl;
	}
   }while(in!=0);
}//修改航班信息 

//航班管理类成员函数 
air_manager::air_manager(){
	i=0;air A;	
	fstream file("air.txt",ios::in);
	while(1){
        file.read((char*)&A,sizeof(A));
        if(!file) break; 
          a[i]=A;i++; }//文件数据中按照对象读取到数组 
	file.close();
}//构造函数（读取文件数据）

int air_manager::search_num(){
	int n;
	cout << "请输入航班号："; 	cin >> n;
	cout << endl;
	int j;
	for(j=0;j<i;j++)
	   if(a[j].get_num()==n)
	      return j;//返回数组下标 
	if(j==i){
	   cout <<" 此航班不存在！"<< endl; return -1;
    }   
}//寻找下标  

void air_manager::delte1(int k){
	 if(k==-1) return;
	 for(int j=k;j<i;j++)
	        a[j]=a[j+1];//找出下标，后面向前移动一位 
	 i--; 
	 cout << "删除成功！"<< endl<< endl;
}//删除方式1

void air_manager::delte2(){
	 char start[20],end[20];
	 cout << endl << "请输入起始站："; cin >> start;
	 cout << endl << "请输入终点站："; cin >> end;
	 int j,n;
	 for(j=0;j<i;j++)
	    if(strcmp(a[j].get_start(),start)==0 && strcmp(a[j].get_end(),end)==0) break;//起点和终点都相同 
     if(j==i){
     	cout <<" 此航班不存在！"<< endl; return;  }
	 do{
	 for(int k=j;k<i;k++)
	        a[k]=a[k+1];//后面向前移动一位  
	 i--; 
	 for(n=0;n<i;n++)
	    if(strcmp(start,a[n].get_start())==0 && strcmp(end,a[n].get_end())==0)
	      { j=n;break;} //继续寻找相同航线的航班 
	 }while(n!=i);
	 cout << "删除成功！"<< endl<< endl;
}//删除方式2 

air_manager::~air_manager(){
    ofstream file("air.txt",ios::out);
    for(int j=0;j<i;j++){
	   file.write((char*)&a[j],sizeof(a[j])); }//对象生存期结束时重新写入文件 
	file.close();	
}//析构函数 (写入文件)

//乘客类成员函数 
int passenger::login(){
	cout <<endl<<"请输入手机号:";cin>>phone;
	cout <<endl<<"请输入密码:";cin>>code;
	int j;
	passenger_manage pas;
	for(j=0;j<pas.i;j++){
       if(strcmp(pas.p[j].get_phone(),phone)==0 && strcmp(pas.p[j].get_code(),code)==0){ //账号和密码都相同 
	     return 0;} 
	}
	if(j==pas.i){
	 cout<<endl<<"输入有误！"<<endl; return -1;  }
}//登陆 

void passenger::enroll(){
	 passenger_manage pas;  
	 cout <<endl<< "请输入姓名：";     cin >> name;     pas.p[pas.i].set_name(name);//放入对象数组 
	 cout <<endl<< "请输入性别：";     cin >> sex;      pas.p[pas.i].set_sex(sex);
	 cout <<endl<< "请输入身份证号："; cin >> ID;       pas.p[pas.i].set_ID(ID);
	 cout <<endl<< "请输入手机号：";   cin >> phone;    pas.p[pas.i].set_phone(phone);
	 cout <<endl<< "请输入银行卡号："; cin >> card;     pas.p[pas.i].set_card(card);
	 cout <<endl<< "请设定密码：";     cin >> code;     pas.p[pas.i].set_code(code);
	 int n[20];
	 for(int k=0;k<20;k++)
	     n[k]=0;//乘客所有航班号初始化为零 
     pas.p[pas.i].set_num(n);
	 pas.i++;
	 cout <<endl<< "注册成功！"<<endl;
}//注册 
	
void passenger::order(){
	 int in;
     air_manager Air;
     int k=Air.search_num();//找出数组下标 
     if(k==-1) return;
     if(Air.a[k].get_count()==Air.a[k].get_r_count()){
        cout << "此航班票已售完！"; 
		return; }
     cout <<endl<< "请输入您的手机号：";cin >> phone;
     passenger_manage pas;
     int j=pas.search_p(phone);//根据手机号寻找乘客 
     if(j==-1) return;
     for(int l=0;l<20;l++)
	    if(pas.p[j].num[l]==Air.a[k].get_num()){ // 一个航班只能订一张票 
	    cout<<endl<< "此航班已订过票"<<endl;
		return;} 
	 int y;//验证码 
	 cout <<endl<< "请输入"<<phone<<"接收到的验证码：";cin >> y;
     cout <<endl <<endl<< "是否提交订单： 1  是     2  否"<<endl;
	 cout <<endl<< "请输入1或2选择："; cin >> in;
	 if(in==1){
	 	for(int l=0;l<20;l++)
		    if(pas.p[j].num[l]==0){
		      pas.p[j].num[l]=Air.a[k].get_num();//航班号放入乘客信息 
			  break;} 
	 	Air.a[k].set_r_count(Air.a[k].get_r_count()+1);//已定票数加一 
	 	cout << endl << "订票成功！" << endl; 
	 }
	 else return;
}//订票 

void passenger::refund(){ 
     air_manager Air;
     int k=Air.search_num();//找出数组下标 
     if(k==-1)return;
     int in;
	 cout <<endl<< "请输入您的手机号：";cin >> phone;
	 int z;//验证码 
	 cout <<endl<<endl<< "请输入"<<phone<<"接收到的验证码：";cin >> z;
	 cout <<endl <<endl<< "是否确认此操作： 1  是     2  否"<<endl;
	 cout <<endl<< "请输入1或2选择：";cin >> in;
	 if(in==1){
	   passenger_manage pas;
 	   int j=pas.search_p(phone);
 	   if(j==-1) return;
 	   int l;
       for(l=0;l<20;l++){
	      if(pas.p[j].num[l]==Air.a[k].get_num()){
            Air.a[k].set_r_count(Air.a[k].get_r_count()-1);//已定票数减一 
            pas.p[j].num[l]=0; break;} }//去除航班号
       if(l!=20) cout <<endl<< "退票成功！" <<endl;     
       else cout <<endl<<"此用户未订此航班的票！"<<endl;  
	 }
     else return;
}//退票 

void passenger::check(){
	 int r=1;//订单号 
	 air_manager Air;
	 cout <<endl<< "请输入您的手机号：";cin >> phone;
	 int y;//验证码 
	 cout <<endl<< "请输入"<<phone<<"接收到的验证码：" ;cin >> y;
	 cout <<endl<< "我的订单信息如下："<<endl;
	 passenger_manage pas;
	 int j=pas.search_p(phone);
	 if(j==-1) return;
     for(int l=0;l<20;l++){
	     if(pas.p[j].num[l]!=0){
	        for(int k=0;k<Air.i;k++)
               if(Air.a[k].get_num()==pas.p[j].num[l]){//航班号 
                 cout <<endl<<endl<< "订单 "<<r<<endl; r++;
	             cout <<"姓名：  "<<pas.p[j].name;
	             cout <<endl<< "手机号："<<pas.p[j].phone;
	             cout <<endl<< "航班号："<<Air.a[k].get_num(); 
	             cout <<endl<< "起始站："<<Air.a[k].get_start();
	             cout <<endl<< "终点站："<<Air.a[k].get_end();
	             cout <<endl<< "时间：  "<<Air.a[k].get_time()<<endl<<endl; 
				 }
         }
      }
     if(r==1) cout <<endl<<"无订单！"<<endl; 
}//查看订单 

//乘客管理类成员函数 
passenger_manage::passenger_manage(){
	i=0;passenger a;	
	fstream file("passengers.txt",ios::in);
	while(1){
        file.read((char*)&a,sizeof(a));
        if(!file) break; 
          p[i]=a;i++; }//文件数据中按照对象读取到数组 
	file.close();
}//构造函数（读取文件数据） 

int passenger_manage::search_p(char a[]){
	 int j;
	 for(j=0;j<i;j++)
	 	if(strcmp(p[j].get_phone(),a)==0)//按手机号 
        return j;//返回数组下标 
     if(j==i) { cout<<"无此用户！"<<endl;
	 return -1;} 
}//找人 

passenger_manage::~passenger_manage(){
    ofstream file("passengers.txt",ios::out);
    for(int j=0;j<i;j++){
	   file.write((char*)&p[j],sizeof(p[j])); }//重新放回数组 
	file.close();	
}//析构函数 (写入文件)

//主函数 
int main()
{
 char n[30],m[4]="123";//管理员账号 
 int in,x,y,z; //switch结构的输入 
 do{
 cout << "************  欢迎进入飞机票管理系统!  ************" << endl << endl;
 cout << "********          请选择登陆身份:          ********" << endl;
 cout << "********          1    管理员              ********" << endl;
 cout << "********          2    用户                ********" << endl;
 cout << "********          0    退出                ********" << endl;
 cout << "请选择:";
 cin >> in;
 system("cls");
 switch(in){
  case 1:{ 
    cout << "请输入管理员账号(预设为123)："; cin >>n;
    if(strcmp(n,m)==0){
       do{
       	 cout << "********       1    添加航班信息           ********" << endl;
         cout << "********       2    查询航班信息           ********" << endl;
         cout << "********       3    删除航班信息           ********" << endl;
         cout << "********       4    修改航班信息           ********" << endl;
         cout << "********       0    返回                   ********" << endl << endl;
         cout<<"请选择："; 
         cin >>x;
         system("cls");
         switch(x){
         	case 1:{ air Air;Air.add();
         		break;}
         	case 2:{ air Air;Air.search();
         		break;}
         	case 3:{ air Air;Air.delet();
         		break;}
         	case 4:{ air Air;Air.change();
         		break; } 
         	case 0:
         		break;
            default:
             cout << "输入错误！请重新输入" << endl << endl << endl; 
         }
       }while(x!=0);
    }
    else cout << "错误！"<<endl; 
    break;} 
  case 2:{ 
   do{
    cout << "********       1    登陆           ********" << endl;
    cout << "********       2    注册           ********" << endl;
    cout << "********       0    返回           ********" << endl << endl;
    cout<<"请选择：";
    cin >> y;
    system("cls");
    switch(y){
    	case 1:{ 
    	      passenger p;
			  int s=p.login();//登录 
			  if(s==-1) break;//登陆失败则返回上一界面 
		      do{
    	      cout << "********       1    订票           ********" << endl;
              cout << "********       2    退票           ********" << endl;
              cout << "********       3    查看订单       ********" << endl;
              cout << "********       4    查询航班信息   ********" << endl;
              cout << "********       0    返回           ********" << endl <<endl;
              cout<<"请选择：";
              cin >>z;
              system("cls");
              switch(z){
              	case 1:{ passenger p;p.order();
              		break;}
              	case 2:{ passenger p;p.refund();
              		break;}
              	case 3:{ passenger p;p.check();
              		break;}
              	case 4:{ air Air;Air.search();
              		break;}
              	case 0:
              		break;
              	default:
              		cout << "输入错误！请重新输入" << endl << endl << endl;
              }
              }while(z!=0);
    		break;}
    	case 2:{
		    passenger p;
			p.enroll();//注册 
    		break;}
    	case 0:
    		break;
    	default:
    		cout << "输入错误！请重新输入" << endl << endl << endl;
    }
   }while(y!=0);
    break;}
  case 0:
    break;
  default:
   cout << "输入错误！请重新输入" << endl << endl << endl; 
  }
 }while(in!=0);
}
