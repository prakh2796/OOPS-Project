 #include<iostream.h>
 #include<stdio.h>
 #include<string.h>
 #include<graphics.h>
 #include<stdlib.h>
 #include<dos.h>
 #include<conio.h>
 #include<assert.h>
 //using namespace std;


//MOUSE FUNCTIONS
 int initmouse();
 void showmouseptr();
 void restrictmouseptr(int, int, int, int);
 void getmousepos(int*,int*,int*);
 union REGS i, o;

//CLASSES
class train;
class station;
class user;
class normal;
class admin;
class pnr;
class ticket;
class welcome;
class home;
class common;
class print;
class train_btw_2_station;

void common2();
//void Exit();
void gotoxy(int x,int y);
int initmouse()
{
   i.x.ax = 0;
   int86(0X33,&i,&o);
   return ( o.x.ax );
}

void showmouseptr()
{
   i.x.ax = 1;
   int86(0X33,&i,&o);
}

void restrictmouseptr(int x1, int y1, int x2, int y2)
{
   i.x.ax = 7;
   i.x.cx = x1;
   i.x.dx = x2;
   int86(0X33,&i,&o);

   i.x.ax = 8;
   i.x.cx = y1;
   i.x.dx = y2;
   int86(0X33,&i,&o);
}

void getmousepos(int *button, int *x, int *y)
{
   i.x.ax = 3;
   int86(0X33,&i,&o);

   *button = o.x.bx;
   *x = o.x.cx;
   *y = o.x.dx;
}

int trainno=1010;
int trcount=0,stcount=0,pnrcount=0;

char *retzone(int x)
{
if(x==1)
return ("North");
else if(x==2)
return ("East");
else if(x==3)
return ("South");
else
return ("West");
}

char *unrem(char *a)
{
	for(int i=0;i<strlen(a);i++)
	{
		if(a[i]=='_')
			a[i]=' ';
	}
	//cout<<a;
	return a;
}

//class train;
class station
{
char *code;
char *name;
int  subcount;
char *zone;
char *city;
train *st_tr[20];
public:
	station()
	{
		subcount=-1;
	}
	station(char *s,int zonal,char *c)
	{
	  subcount=-1;
	  name=new char[50];
	  city=new char[50];
	  strcpy(name,s);
	  name=unrem(name);
	  strcpy(city,c);
	  zone=retzone(zonal);
	  int temp=s[0]*2+stcount;
	  code=new char[strlen(s)+1];
	  code[0]=s[0];
	  code[1]=NULL;
	  char str[3];
	  sprintf(str,"%d",temp);
	  strcat(code,str);
	}
	char*retcode()
	{

		return(code);
	}

	char *retstname()
	{
		return(name);
	}

	char *retcity()
	{
		return(city);
	}

	void gettrain(train *);
	void findtrain()
	{
		for(int i=0;i<subcount+1;i++)
		cout<<st_tr[i]->retname()<<" ";
	}

	void printst()
	{
	 int  count=subcount+1;
	 int j=0,k=0,i=0,flag=0;

	 gotoxy(1,1);
	 cleardevice();

	 setcolor(RED);
	 settextstyle(0,HORIZ_DIR,0);
	 outtextxy(12,35,"S.No");
	 outtextxy(55,35,"CODE");
	 outtextxy(115,35,"STATION NAME");
	 outtextxy(230,35,"CITY");
	 outtextxy(375,35,"TRAINS");
	 settextstyle(3,HORIZ_DIR,2);
	 setcolor(RED);
	 //delay(1000);                  //110

		rectangle(10,50,40,105);
		rectangle(40,50,85,105);
		rectangle(85,50,195,105);
		rectangle(195,50,300,105);
		rectangle(300,50,630,105);
		//delay(500);
	setfillstyle(SOLID_FILL,WHITE);
		floodfill(16,51,RED);
		floodfill(41,51,RED);
		floodfill(86,51,RED);
		floodfill(196,51,RED);
		floodfill(301,51,RED);


	 setcolor(DARKGRAY);
	 settextstyle(0,HORIZ_DIR,2);
	 outtextxy(200,10,"STATION DETAILS");

      setcolor(RED);
      settextstyle(0,HORIZ_DIR,0);
      char no[3];
      outtextxy(14,55,"1.");
      //getch();
      outtextxy(45,55,code);
      //getch();
      outtextxy(90,55,name);
      //getch();
      outtextxy(200,55,city);
     // outtextxy(285,130,"Lucknow,Kanpur,Bareilly,Etawah,Hapur,");
     // outtextxy(285,140,"Ghziabad,Delhi");

   // outtextxy(225,150+m,zone);
     // gotoxy(1,1);
      //gotoxy(1,1);

      char tname[50] ;
      int n=0;
      k=0;
      //name=new char[20*subcount];
      for( i=0;i<6;i=i+2)
      {
       //tname=new char[50];
      // tname[0]=' ';
       strcpy(tname,st_tr[k]->retname());
      // cout<<tname<<" ";
       count=count-1;
      // cout<<count<<" ";

      if(count==0)
      {
      //cout<<tname<<" ";
      outtextxy(303,55+n,tname);
      flag=1;
      strcpy(tname,NULL);
      //delete tname;
      break;
      }
      strcat(tname,",");
      strcat(tname,st_tr[k+1]->retname());

       //cout<<tname<<" ";
      count=count-1;

      if(count==0)
      {
      outtextxy(303,55+n,tname);
      //cout<<tname<<" ";
     strcpy(tname,NULL);
     //	delete tname;

       flag=1;
      //flag=1;
      break;
      //return;
      }
      else
      {
      strcat(tname,",");
       outtextxy(303,55+n,tname);
      //cout<<tname<<" ";
       n=n+18;
      //cout<<endl;
     strcpy(tname,NULL) ;
     // delete tname;
      }
      k=k+2;
      }
      if(flag==1)
      {
      //getch();

      return;
      }

 }

	void display(int m,int stno)
	{
       //	cout<<code<<" "<<name<<" "<<zone<<" "<<city<<endl;
//	getch();
	 int  count=subcount+1;
	 int j=0,k=0,i=0,flag=0;
	 if(m==0)
	 {
	 gotoxy(1,1);
	 cleardevice();

	 setcolor(RED);
	 settextstyle(0,HORIZ_DIR,0);
	 outtextxy(12,35,"S.No");
	 outtextxy(55,35,"CODE");
	 outtextxy(115,35,"STATION NAME");
	 outtextxy(230,35,"CITY");
	 outtextxy(375,35,"TRAINS");
	 settextstyle(3,HORIZ_DIR,2);
	 setcolor(RED);
	 //delay(1000);                  //110
	 for(k=0;k<5;k++)
	 {
		rectangle(10,50+j,40,105+j);
		rectangle(40,50+j,85,105+j);
		rectangle(85,50+j,195,105+j);
		rectangle(195,50+j,300,105+j);
		rectangle(300,50+j,630,105+j);
		j=j+60;
		//delay(500);
	 }
	 rectangle(20,400,100,430);
	 rectangle(280,400,360,430);
	 rectangle(540,400,620,430);
	j=0;
	setfillstyle(SOLID_FILL,WHITE);
	for(k=0;k<5;k++)
	{
		floodfill(16,51+j,RED);
		floodfill(41,51+j,RED);
		floodfill(86,51+j,RED);
		floodfill(196,51+j,RED);
		floodfill(301,51+j,RED);
		j=j+60;
	}
	floodfill(21,401,RED);
	floodfill(281,401,RED);
	floodfill(541,401,RED);
	outtextxy(35,403,"BACK");
	outtextxy(295,403,"MENU");
	outtextxy(555,403,"NEXT");
	//getch();
      //setcolor(RED);
     // settextstyle(3,HORIZ_DIR,1);
      //outtextxy(25,80,"Sations Details");
      }
	 setcolor(DARKGRAY);
	 settextstyle(0,HORIZ_DIR,2);
	 outtextxy(200,10,"STATION DETAILS");

      setcolor(RED);
      settextstyle(0,HORIZ_DIR,0);
      char no[3];
      sprintf(no,"%d",stno);
      strcat(no,".");
      outtextxy(14,55+m,no);
      //getch();
      outtextxy(45,55+m,code);
      //getch();
      outtextxy(90,55+m,name);
      //getch();
      outtextxy(200,55+m,city);
     // outtextxy(285,130,"Lucknow,Kanpur,Bareilly,Etawah,Hapur,");
     // outtextxy(285,140,"Ghziabad,Delhi");

   // outtextxy(225,150+m,zone);
     // gotoxy(1,1);
      //gotoxy(1,1);

      char tname[50] ;
      int n=0;
      k=0;
      //name=new char[20*subcount];
      for( i=0;i<6;i=i+2)
      {
       //tname=new char[50];
      // tname[0]=' ';
       strcpy(tname,st_tr[k]->retname());
      // cout<<tname<<" ";
       count=count-1;
      // cout<<count<<" ";

      if(count==0)
      {
      //cout<<tname<<" ";
      outtextxy(303,55+m+n,tname);
      flag=1;
      strcpy(tname,NULL);
      //delete tname;
      break;
      }
      strcat(tname,",");
      strcat(tname,st_tr[k+1]->retname());

       //cout<<tname<<" ";
      count=count-1;

      if(count==0)
      {
      outtextxy(303,55+m+n,tname);
      //cout<<tname<<" ";
     strcpy(tname,NULL);
     //	delete tname;

       flag=1;
      //flag=1;
      break;
      //return;
      }
      else
      {
      strcat(tname,",");
       outtextxy(303,55+m+n,tname);
      //cout<<tname<<" ";
       n=n+18;
      //cout<<endl;
     strcpy(tname,NULL) ;
     // delete tname;
      }
      k=k+2;
      }
      if(flag==1)
      {
      return;
      }

 }

};

train *t[20];
station *s[50];
ticket *tic[20];

class train
{
protected:
char *tname;
int t_no;
int subcount;
char *zone;
int seats;
char *t_type;
station *tr_st[15];
public:
	train()
	{
       //	cout<<"non p"<<endl;
	subcount=-1;
	seats=0;
	}
	virtual char*rettype()=0;
	virtual int retfare(char*,char*)=0;

	train(char *t,int zonal,int seat)//,char *stat)
	{
		subcount=-1;
		tname=new char[strlen(t)+1];
		strcpy(tname,t);
		tname=unrem(tname);
		t_no=++trainno;
		zone=retzone(zonal);
		seats=seat;
	}

	void getstat(station *stat_obj)
	{       if(stat_obj!=NULL )
		tr_st[++subcount]=stat_obj;
	}

	int retno()
	{
		return(t_no);
	}

	char *retname()
	{
		//strstr
	    //	char*temp1,temp2;
		//temp=new char[20];

		//temp=tname - "Express";

		return(tname);
	}

	void train_by_stat(char*,char*);

	void changeseats(int x)
	{
	      //	cout<<x<<" "<<seats;
		assert(x<seats);
		seats=seats+x;
	       //	cout<<" "<<seats;
	     //	getch();
	}

	void operator ++(int)
	{
		seats=seats+1;
	}
	void operator --(int)
	{
		seats=seats-1;
	}
	void showseats(int choice)
	{
		 cleardevice();
		 setcolor(RED);
		 settextstyle(0,HORIZ_DIR,0);
		 if(choice==2)
		 {
		 outtextxy(8,35,"T.No");
		 outtextxy(52,35,"Seats");
		 }
		 else
		 {
		 outtextxy(8,35,"S.No");
		 outtextxy(52,35,"T_no.");
		 }
		 outtextxy(115,35,"TRAIN NAME");
		 outtextxy(255,35,"ZONE");
		 outtextxy(375,35,"Stations");
		 settextstyle(3,HORIZ_DIR,2);
		 setcolor(RED);
	 //delay(1000);                  //110
		rectangle(10,50,45,105);
		rectangle(45,50,85,105);
		rectangle(85,50,240,105);
		rectangle(240,50,300,105);
		rectangle(300,50,630,105);
		setfillstyle(SOLID_FILL,WHITE);

		floodfill(16,51,RED);
		floodfill(46,51,RED);
		floodfill(86,51,RED);
		floodfill(241,51,RED);
		floodfill(301,51,RED);
	 setcolor(DARKGRAY);
	 settextstyle(0,HORIZ_DIR,2);
	 outtextxy(200,10,"STATION DETAILS");

      setcolor(RED);
      settextstyle(0,HORIZ_DIR,0);
      if(choice==2)
      {
      char no[5];
      sprintf(no,"%d",t_no);
      outtextxy(14,55,no);
      //getch();
      sprintf(no,"%d",seats);

      outtextxy(54,55,no);
      //getch();
      }
      else
      {
      char no[5];
      sprintf(no,"%d",t_no);
      outtextxy(14,55,"1");
      //getch();

      outtextxy(54,55,no);
      }

      outtextxy(90,55,tname);
      //getch();
      outtextxy(250,55,zone);
     // outtextxy(285,130,"Lucknow,Kanpur,Bareilly,Etawah,Hapur,");
     // outtextxy(285,140,"Ghziabad,Delhi");

   // outtextxy(225,150+m,zone);
     // gotoxy(1,1);
      //gotoxy(1,1);

      char stname[70] ;
      int n=0;
     int  k=0,i,flag=0;
     int count=subcount+1;
      //name=new char[20*subcount];
      for( i=0;i<12;i=i+4)
      {
       //tname=new char[50];
      // tname[0]=' ';
       strcpy(stname,tr_st[k]->retcity());
      // cout<<tname<<" ";
       count=count-1;
      // cout<<count<<" ";

      if(count==0)
      {
      //cout<<tname<<" ";
      outtextxy(303,55+n,stname);
      flag=1;
      strcpy(stname,NULL);
      //delete tname;
      break;
      }
      strcat(stname,",");
      strcat(stname,tr_st[k+1]->retcity());

       //cout<<tname<<" ";
      count=count-1;

      if(count==0)
      {
      outtextxy(303,55+n,stname);
      //cout<<tname<<" ";
     strcpy(stname,NULL);
     //	delete tname;

       flag=1;
      //flag=1;
      break;
      //return;
      }
      strcat(stname,",");
      strcat(stname,tr_st[k+2]->retcity());

       //cout<<tname<<" ";
      count=count-1;

      if(count==0)
      {
      //cout<<tname<<" ";
      outtextxy(303,55+n,stname);
      flag=1;
      strcpy(stname,NULL);
      //delete tname;
      break;
      }
      strcat(stname,",");
      strcat(stname,tr_st[k+3]->retcity());

       //cout<<tname<<" ";
      count=count-1;



      if(count==0)
      {
      outtextxy(303,55+n,stname);
      //cout<<tname<<" ";
      strcpy(stname,NULL);
     //	delete tname;

       flag=1;
      //flag=1;
      break;
      //return;
      }
      else
      {
      strcat(stname,",");
       outtextxy(303,55+n,stname);
      //cout<<tname<<" ";
       n=n+18;
      //cout<<endl;
     strcpy(stname,NULL) ;
     // delete tname;
      }
      k=k+4;
      }
      if(flag==1)
      {
       strcpy(stname,NULL) ;
      //delete stname;
      return;
      }
		//delay(500);
      }

	void display(int m,int tno)
	{
	 int j=0,k=0;
	 if(m==0)
	 {
	 gotoxy(1,1);
	 cleardevice();

		 setcolor(RED);
		 settextstyle(0,HORIZ_DIR,0);
		 outtextxy(8,35,"S.No");
		 outtextxy(52,35,"T.No");
		 outtextxy(115,35,"TRAIN NAME");
		 outtextxy(255,35,"ZONE");
		 outtextxy(375,35,"Stations");
		 settextstyle(3,HORIZ_DIR,2);
		 setcolor(RED);
		for(k=0;k<5;k++)
		{

		rectangle(10,50+j,45,105+j);
		rectangle(45,50+j,85,105+j);
		rectangle(85,50+j,240,105+j);
		rectangle(240,50+j,300,105+j);
		rectangle(300,50+j,630,105+j);
		j=j+60;
		}
		rectangle(20,400,100,430);
		rectangle(280,400,360,430);
		rectangle(540,400,620,430);

		j=0;
		 for(k=0;k<5;k++)
		{

		setfillstyle(SOLID_FILL,WHITE);

		floodfill(16,51+j,RED);
		floodfill(46,51+j,RED);
		floodfill(86,51+j,RED);
		floodfill(241,51+j,RED);
		floodfill(301,51+j,RED);
		j=j+60;
		}
		getch();
	floodfill(21,401,RED);
	floodfill(281,401,RED);
	floodfill(541,401,RED);
	outtextxy(35,403,"BACK");
	outtextxy(295,403,"MENU");
	outtextxy(555,403,"NEXT");

	 setcolor(DARKGRAY);
	 settextstyle(0,HORIZ_DIR,2);
	 outtextxy(200,10,"TRAIN DETAILS");
      }                                        //if close
      setcolor(RED);
      settextstyle(0,HORIZ_DIR,0);
      char no[5];
      sprintf(no,"%d",tno);
      outtextxy(14,55+m,no);
      sprintf(no,"%d",t_no);

      outtextxy(54,55+m,no);
      outtextxy(90,55+m,tname);
      outtextxy(250,55+m,zone);

      char stname[70] ;
      int n=0;
     int  i=0,flag=0;
     k=0;
     int count=subcount+1;
   //  count=subcount+1;
      //name=new char[20*subcount];
      for( i=0;i<12;i=i+4)
      {
       //tname=new char[50];
      // tname[0]=' ';
       strcpy(stname,tr_st[k]->retcity());
     // cout<<"count ";
     // getch();
      // cout<<tname<<" ";
       count=count-1;
      // cout<<count<<" ";

      if(count==0)
      {
      //cout<<tname<<" ";
      outtextxy(303,55+m+n,stname);
      flag=1;
      //getch();
      strcpy(stname,NULL);
      //delete tname;
      break;
      }
      strcat(stname,",");
      strcat(stname,tr_st[k+1]->retcity());

       //cout<<tname<<" ";
      count=count-1;
      if(count==0)
      {
      outtextxy(303,55+n+m,stname);
      //cout<<tname<<" ";
     //getch();
     strcpy(stname,NULL);
     //	delete tname;

       flag=1;
      //flag=1;
      break;
      //return;
      }
      strcat(stname,",");
      strcat(stname,tr_st[k+2]->retcity());
      count=count-1;

      if(count==0)
      {
      //cout<<tname<<" ";
      outtextxy(303,55+n+m,stname);
      flag=1;
      //getch();
      strcpy(stname,NULL);
      //delete tname;
      break;
      }
      strcat(stname,",");
      strcat(stname,tr_st[k+3]->retcity());

       //cout<<tname<<" ";
      count=count-1;
      if(count==0)
      {
      outtextxy(303,55+n+m,stname);
      //cout<<tname<<" ";
      strcpy(stname,NULL);
     //	delete tname;

       flag=1;
      //flag=1;
      break;
      //return;
      }
      else
      {
      strcat(tname,",");
       outtextxy(303,55+n+m,stname);
      //cout<<tname<<" ";
       n=n+18;
      //cout<<endl;
     strcpy(stname,NULL) ;
     // delete tname;
      }
      k=k+3;
      }
      if(flag==1)
      {
       strcpy(stname,NULL) ;
      //delete stname;
      return;
      }
		//delay(500);
     }
};


class pass:public train
{
int time;
public:
       pass()
	{
	//cout<<"\n a pass";
	}
	pass(char *name,int x,int y):train(name,x,y)
	{
		t_type="passenger";

	}
	char*rettype()
	{
		return(t_type);
	}

	int retfare(char*source,char*dest)
	{
		int initial,final;
		int fare;
		for(int i=0;i<subcount+1;i++)
		{
		if(strcmp(tr_st[i]->retstname(),source)==0)
		initial=i;
		else if(strcmp(tr_st[i]->retstname(),dest)==0)
		final=i;
		}
		fare=abs(final-initial)*200;
		assert(fare>0);
		return fare;

	}


};

class superfast:public train
{
int time;
public:
	superfast()
	{
	//cout<<"\n a pass";
	}
	superfast(char *name,int x,int y):train(name,x,y)
	{
		t_type="superfast";
	}
	char*rettype()
	{
		return(t_type);
	}

	int retfare(char*source,char*dest)
	{
		int initial,final;
		for(int i=0;i<subcount+1;i++)
		{
		if(strcmp(tr_st[i]->retcode(),source)==0)
		initial=i;
		else if(strcmp(tr_st[i]->retcode(),dest)==0)
		final=i;
		}
		int fare=abs(final-initial)*300;
		return fare;
	}

};

void station::gettrain(train *tr_obj)
{
	if(tr_obj!=NULL)
	st_tr[++subcount]=tr_obj;
}

//void throw(int,int);
int found=0;
void train::train_by_stat(char *source,char *dest)
{
	int flag=0;
	//cout<<source<<" "<<dest;
     /*try{	if(source==NULL)
	{
		throw(0,1);
	}
	else if(dest==NULL)
		throw(1,0);
	else if(source==NULL && dest==NULL)
		throw(0,0);
	}*/
		for(int i=0;i<subcount+1;i++)
		{
		if(strcmp(tr_st[i]->retcode(),source)==0 || strcmp(tr_st[i]->retcode(),dest)==0)
		{
			flag++;
		}
			if(flag==2)
			{
			found=1;
			if(tr_st[i]!=NULL)
			cout<<" "<<t_no<<" "<<tname<<endl;
			flag=0;
			}
		}
}


class pnr
{
protected:
char *p_no;
char *pname;
char gender;
int age;
int no_of_pas;
train *taken;
station *source_st;
station *dest_st;

public:
pnr()
{
}

pnr(int ag,int passno,char g,char *name,train *take,station *source,station *dest)
{
gender=g;
age=ag;
no_of_pas=passno;
pname=new char[strlen(name)];
strcpy(pname,name);
pname[strlen(name)]=NULL;
//cout<<pname;
taken=take;
source_st=source;
dest_st=dest;
p_no=new char[7];
char *var=source_st->retcode();
p_no[0]=var[0];
p_no[1]=NULL;
var=dest_st->retcode() ;
p_no[1]=var[0];
p_no[2]=NULL;

var=source_st->retcode();
int temp=var[0];
char str[3];
sprintf(str,"%d",temp);
strcat(p_no,str);
char rtr[3];
var=dest_st->retcode();
temp=var[0]+pnrcount;
sprintf(rtr,"%d",temp);
strcat(p_no,rtr);

/*cout<<p_no<<" "<<pname<<" "<<age<<" "<<no_of_pas<<endl;
cout<<taken->rettype()<<" "<<taken->retno()<<" "<<taken->retname()<<"\n";
cout<<source_st->retstname()<<" "<<dest_st->retstname()<<endl<<endl;
*/
}

char*retpnr()
{
	return p_no;
}

void viewpnr()
{
cout<<p_no<<" ";
}

};


class ticket:public pnr
{
char*t_name;
int fare;
int j_time; //journey time
public:
ticket()
{
}

ticket(int ag,int no,char g,char *name,train *take,station *source,station *dest):pnr(ag,no,g,name,take,source,dest)
{
fare=0;
int initial,final;
fare=taken->retfare(source_st->retcode(),dest_st->retcode());
if(no_of_pas>1)
taken->changeseats(-(no_of_pas));
else
(*taken)--;
//cout<<fare<<" ";
//cout<<taken->retname();

//cout<<p_no<<" "<<pname<<" "<<fare<<endl;
}
friend ostream& operator << (ostream&,ticket*);

void viewticket()
{
cleardevice();
setfillstyle(SOLID_FILL,WHITE);
bar(0,0,getmaxx(),getmaxy());
setcolor(BLACK);
rectangle(10,10,630,470);
rectangle(15,15,625,465);
rectangle(15,80,625,82);
settextstyle(0,HORIZ_DIR,3);
outtextxy(250,40,"TICKET");
rectangle(15,82,625,180);
rectangle(15,82,getmaxx()/2,250);
settextstyle(0,HORIZ_DIR,0);
outtextxy(25,115,"PNR NO. - ");
outtextxy(25,145,"DATE - ");
outtextxy(325,100,"TRAIN NO. - ");
outtextxy(325,130,"TRAIN NAME - ");
outtextxy(325,160,"JOURNEY TIME - ");
rectangle(15,180,625,250);
outtextxy(25,210,"BOARDING - ");
outtextxy(325,210,"DESTINATION - ");
outtextxy(100,115,p_no);
outtextxy(100,145,"11/12/2014");

	       char str[5];
	       sprintf(str,"%d",taken->retno());
	       s[4]=NULL;

outtextxy(440,100,str);
outtextxy(440,130,taken->retname());
outtextxy(440,160,"1800 mins");
outtextxy(130,210,source_st->retcity());
outtextxy(440,210,dest_st->retcity());
rectangle(15,250,625,252);
rectangle(15,252,250,465);
rectangle(15,252,325,465);
rectangle(15,252,375,465);
rectangle(15,252,475,465);
rectangle(15,252,550,465);
rectangle(15,252,625,310);

outtextxy(100,280,"NAME");
outtextxy(265,280,"GENDER");
outtextxy(340,280,"AGE");
outtextxy(377,280,"No. of SEATS");
outtextxy(490,280,"STATUS");
outtextxy(572,280,"FARE");
outtextxy(570,290,"(INR)");
char name[20];
strcpy(name,pname);
outtextxy(50,350,name);
char *p;
p[0]=gender;
p[1]=NULL;
outtextxy(280,350,p);
char r[5];
sprintf(r,"%d",age);
outtextxy(345,350,"19");
sprintf(r,"%d",no_of_pas);

outtextxy(410,350,r);
outtextxy(495,350,"CNF");
sprintf(r,"%d",fare);
sprintf(r,"%d",fare);
outtextxy(566,350,r);
getch();
}


void operator --();
};

void ticket:: operator -- ()
{
	cout<<"ticket  \n";
	getch();
	if(no_of_pas>1)
	{
	taken->changeseats(no_of_pas);
	}
	else
	(*taken)++;       //	return *this;
}

ostream& operator << (ostream &out,ticket *o)
{
if(o!=NULL)
o->viewticket();
}

ticket *findticket()
{
	    int index=-1,i;
	    cleardevice();
	    char *pno;
	    pno=new char[8];

	    gotoxy(1,1);
	    cout<<"Enter yOur pnr no. ";
	    cin>>pno;
	    for(i=0;i<pnrcount;i++)
	    {  	if(strcmp(tic[i]->retpnr(),pno)==0)
		{
			index=i;
			delete pno;
			break;

		}
	    }
	   // try{
	    if(index<0)
	    {
		//throw("pno");
		{
			cout<<"Entered wrong pnr"<<endl;
			cout<<"Enter again";
			delay(1090);
			delete pno;
			normal n;
			//return(findticket());
		}
	    }
	    //}
	    return tic[index];


}
/*
void file1();
void file2();
void file3();
void file4();
*/
void file5()
{
 FILE *fp;
 char *g;
 g="pnr2.txt";	  //We have four zone wise trains
 int flag=1,flag2=0,i=0,j=0;
 char gender;
 int age,tno,pas;
 int finish=0;
 char name[50];
 //char *name;
 char source[10],dest[10];
 int get,tindex,sindex,dindex;
 int temp;
 fp=fopen(g,"r");
 while(flag==1)
 {
 //cout<<"outer ";
 get=fscanf(fp,"%d %d %d %c %s %s %s",&age,&pas,&tno,&gender,name,source,dest);
       //	cout<<"outer "<<get;
	//cout<<get;
       //cout<<t[2]->retno()<<"done ";

	/*try{
	if(age<0 || pas<0 || tno<0 || gender!='M' || gender!='F')
			throw("file",5);
			}*/
	if(age<0 || pas<0 || tno<0 || gender!='M' || gender!='F')
			finish=1;
			//assert(finish!=1);
	if(get==7)
	{
	// cout<<(t[i]->retno());
	 //	cout<<tno;
		for(j=0;j<trcount;j++)
		{
			 temp=(t[j]->retno());

			if(temp==tno)
			{
	    // +	  //cout<<temp<<" ";
				tindex=j;
				break;
			}
		}
		//cout<<tindex<<" tdone";
		for(j=0;j<stcount;j++)
		{
			if(strcmp(s[j]->retcode(),source)==0)
			{
				sindex=j;
				flag2++;
			}
			if(strcmp(s[j]->retcode(),dest)==0)
			{
				dindex=j;
				flag2++;
			}
			if(flag2==2)
			{flag2=0;
			break;
			}
		}
		//cout<<sindex<<" "<<dindex;


     tic[i]=new ticket(age,pas,gender,name,t[tindex],s[sindex],s[dindex]);

	cout<<endl;
	//get=0;
	i++;
	pnrcount=i;
	}
	else
	{ cout<<"else ";
	break;
	}
 }
 fclose(fp);               //file close
}

void file4()
{
 FILE *fp;
 char *g,ch;
 g="st-tr.txt";	  //We have four zone wise trains
 //cout<<g<<endl;
 int q=-1,*c;
 fp=fopen(g,"r");
 c=new int[100];
 while((ch=getc(fp))!=EOF)
 {
	if(ch=='\n')
	{
		for(int i=1;i<=q;i++)
		{
		//cout<<c[i]<<" ";
		s[c[0]]->gettrain(t[c[i]]);
		}
		q=-1;
		delete c;
		c=new int[100];
	       i++;
	      // cout<<endl;
	}
	else
	{
		int temp;
		fscanf(fp,"%d",&temp);
		c[++q]=temp;
	}

 }
}

void file3()
{
 FILE *fp;
 char *g,ch;
 g="tr-st.txt";	  //We have four zone wise trains
 //cout<<g<<endl;
 int q=-1,*c;
 fp=fopen(g,"r");
 c=new int[50];
 int i=0;
 while((ch=getc(fp))!=EOF)
 {
	if(ch=='\n')
	{
		for(int i=1;i<=q;i++)
	       {
	       //	cout<<c[i]<<" ";
	       //	cout<<endl;

		t[c[0]]->getstat(s[c[i]]);
		}
		q=-1;
		delete c;
		c=new int[50];
	    i++;

	}
	else
	{
		int temp;
		fscanf(fp,"%d",&temp);
		c[++q]=temp;
	}
 }
}

void file2()
{
 FILE *fp;
 char *g;
 g="station.txt";	  //We have four zone wise trains
 cout<<g<<endl;
 int get,i=0,flag=1;
 int zone,finish=0;
 char fname[100];
 char lname[50];
 char city[30];
 char *name;
 fp=fopen(g,"r");          //File opening
 while(flag==1)
 {
	get=fscanf(fp,"%s %s %d %s",fname,lname,&zone,city);
	if(get==4)
	{
	/*try{
	if(fname==NULL || lname zone>4 || city==NULL)
			throw("file",2);
	}*/
	if(fname==NULL || lname==NULL || zone>4 || city==NULL)
			finish=1;
			assert(finish!=1);

	name=new char[100];
	name=strcat(fname," ");
	name=strcat(name,lname);
	s[i]=new station(name,zone,city);
      //cout<<get<<" "<<name<<" "<<city<<" "<<zone<<endl;
       //	name=NULL;
       //	fname=NULL;
       //	lnmae=NULL;
       //	city=NULL;
	i++;
	stcount=i;
	}
	else
	break;
 }
 fclose(fp);
 delete fname,lname,city;           //file close
}

void file1()
{
 FILE *fp;
 char *g;
 g="train.txt";	  //We have four zone wise trains
 cout<<g<<endl;
 int flag=1,i=0,finish=0;
 int type,seats,zone;
 char fname[20],lname[20],traintype;
 char *name;
 int get;
 fp=fopen(g,"r");
 while(flag)
 {
	get=fscanf(fp,"%d %s %s %d %d",&type,fname,lname,&zone,&seats);
	if(get==5)
	{
	//cout<<type<<" "<<fname<<" "<<lname<<" "<<zone<<" "<<seats;
	//cout<<endl;
	/*try{
	if(fname==NULL || lname==NULL || zone>4 || type>2)
			throw("file",5);
	}*/
	if(fname==NULL || lname==NULL || zone>4 || type>2)
			finish=1;
			assert(finish!=1);

	name=new char[40];
	name=strcat(fname," " );
	name=strcat(name,lname);
	if(type==1)
	t[i]=new pass(name,zone,seats);
	else
	t[i]=new superfast(name,zone,seats);
	i++;
	trcount=i;
	}
	else
	break;
 }
 fclose(fp);               //file close
}

 class welcome      //our first presenting page
 {
 public:
	welcome()
	{
	float i;
	setfillstyle(SOLID_FILL,WHITE);
	bar(0,0,getmaxx(),getmaxy());
	setcolor(BLUE);
	for(i=120.0;i>115.0;i=i-0.05)
	{
		circle(325,240,i);
	}
	setcolor(BROWN);
	for(i=114.0;i>109.0;i=i-0.05)
	{
		circle(325,240,i);
	}
	setcolor(CYAN);
	for(i=108.0;i>103.0;i=i-0.05)
	{
		circle(325,240,i);
	}
	setcolor(RED);
	for(i=102.0;i>97.0;i=i-0.05)
	{
		circle(325,240,i);
	}
	setcolor(MAGENTA);
	for(i=96.0;i>91.0;i=i-0.05)
	{
		circle(325,240,i);
	}
	setcolor(GREEN);
	for(i=90.0;i>85.0;i=i-0.05)
	{
		circle(325,240,i);
	}
       setcolor(YELLOW);
	for(i=84.0;i>79.0;i=i-0.05)
	{
		circle(325,240,i);
	}
	setcolor(BROWN);
	for(i=78.0;i>73.0;i=i-0.05)
	{
		circle(325,240,i);
	}
	setcolor(LIGHTBLUE);
	for(i=72.0;i>67.0;i=i-0.05)
	{
		circle(325,240,i);
	}
	setcolor(LIGHTGREEN);
	for(i=66.0;i>61.0;i=i-0.05)
	{
		circle(325,240,i);
	}
	setcolor(RED);
	for(i=60.0;i>55.0;i=i-0.05)
	{
		circle(325,240,i);
	}
	int j;
	int m=0;
	for(j=0;j<=6;j++)
	{
	setfillstyle(SOLID_FILL,retcol(j));
	bar(145,175,505,305);
	setfillstyle(SOLID_FILL,14);
	bar(150,180,500,300);
	setcolor(retcol(j));
	outtextxy(300,225,"WELCOME");
	outtextxy(320,235,"TO");
	outtextxy(262,245," RAILWAY ENQUIRY");
	m=m+2;
	delay(500);
	}
	setcolor(4);
	setfillstyle(SOLID_FILL,BLUE);
	bar(145,175,505,305);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(150,180,500,300);
	outtextxy(300,225,"WELCOME");
	outtextxy(320,235,"TO");
	outtextxy(262,245," RAILWAY ENQUIRY");
	setcolor(RED);
	outtextxy(230,275,"Press any key to continue");
	getch();
       }

       int retcol(int col)
       {
	 switch(col)
	 {
	case 0: return 0;     //BLACK;
	case 1: return 4;     //RED;
	case 13: return 2;     //GREEN
	case 2: return 0;   //black   //BROWN(6)
	case 4: return 1;     //BLUE;
	case 5: return 0;     //black //MAGENTA(5);
	case 8: return 3;     //CYAN;
	case 7: return 7;     //LIGHTGRAY;
	case 6: return 4;     //red //DARKGRAY(8);
	case 9: return 12;    //LIGHTRED;
	case 14:return 10;    //LIGHTGREEN
	case 12:return 14;    //YELLOW;
	case 3:return 9;     //LIGHTBLUE;
	case 11:return 15;    //white //LIGHTMAGENTA(13)
	case 10:return 11;    //LIGHTCYAN;
	case 15:return 15;    //WHITE;
   }
   return col;
}


void loading()
{
int j,i;
loadbitmap("tra.bmp",150,120); //tra.bmp is our image file
setcolor(WHITE);
settextstyle(2,HORIZ_DIR,7);
//outtextxy(260,310,"LOADING");


int m;
for(m=0;m<4;m++)
{

loadcolor(0);

	for(j=0;j<2;j++)
	{
		loadcolor(1+j);
		setcolor(j+1);
		circle(353,327,j);
		delay(500);
		circle(363,327,j);
		delay(500);
		circle(373,327,j);
	}
	setcolor(BLACK);
	for(j=0;j<2;j++)
	{
	       //	loadcolor(2*j+2);
		circle(353,327,j);
		circle(363,327,j);
		circle(373,327,j);
	}
}
 setcolor(WHITE);
 circle(353,327,2);
 circle(363,327,2);
 circle(373,327,2);
 outtextxy(155,340,"Press Any Key To Continue");
 getch();
 cleardevice();
 setcolor(BROWN);
 setfillstyle(1,BROWN);
 rectangle(0,5,5,25);
 setcolor(7);
}

void loadcolor(int i)
{
setcolor(i+1);
outtextxy(260,310,"L");
//delay(200);

setcolor(i+2);
outtextxy(263+10,310,"O");
//delay(200);

setcolor(i+3);
outtextxy(266+20,310,"A");
//delay(200);

setcolor(i+4);
outtextxy(269+30,310,"D");
//delay(200);


setcolor(i+5);
outtextxy(272+40,310,"I");
//delay(200);

setcolor(i+6);
outtextxy(273+50,310,"N");
//delay(200);

setcolor(i+7);
outtextxy(276+60,310,"G");
//delay(200);

}

void loadbitmap(char *a,int x,int y)
 {FILE *ptr;
 int width,height;
	       //width and height of the bitmap
   unsigned long temp=0,k=0,j=0;  //some variables i need
   unsigned long ww;
   int ch,ch1,ch2;
   ptr=fopen(a,"rb");      //open the bitmap file
	      //if its not there return

   width=0;height=0;              //initialise wisth and height to zero
   fseek(ptr,18,SEEK_SET);        //got to offset 18 in file
   for(k=0x1;k<=0x10000;k*=0x100) //read the width
   {
	   temp=fgetc(ptr);
	   width+=(temp*k);
   }
   fseek(ptr,22,SEEK_SET);        //go	 to offset 22 in file
   for(k=0x1;k<=0x10000;k*=0x100) //read the height
   {
	   temp=fgetc(ptr);
	   height+=(temp*k);
   }

   ww=width;         //ww is the number of reads to make for each horizontal line
   if(ww%2)          //ww has to be half of width - since each pixel is only 4 bits of information
  { ww++;ww/=2;}       //just getting the correct value
   if(ww%4)          //now - ww is stored as sets of 4 pixels each - i think !?! :so this is the adjustment    made
   ww=(ww/4)*4+4;    //if width is less than ww*2 we ignore what we read

   fseek(ptr,119,SEEK_SET);   //Ok! offset 119 - lets read the pixels -
			      //remember the bitmap is stroed up - side - down

   for(k=0;k<height;k++)
   for(j=0;j<ww;j++)
   {
	   ch=fgetc(ptr);    //each character read is 2 pixels - yes 4 bits per pixel - so 16 colors
	   ch1=ch;ch2=ch;                                //find those colors using bitwise ops
	   ch1=ch1&(0xf0);ch1=ch1>>4;                    // ~~
	   ch2=ch2&(0x0f);                               // ~~
	   if(j*2<width)                                 //ok so put the first pixel read on screen
	   putpixel((j*2)+x,(height-1-k)+y,getcol(ch1));
	   if(j*2+1<width)                               //put the second pixel read on screen
	   putpixel((j*2)+1+x,(height-1-k)+y,getcol(ch2));
   }
   fclose(ptr);				 //close the file handle
 }


int getcol(int col)
 {
   switch(col)
   {
      case 0: return 0;     //BLACK;
      case 1: return 4;     //RED;
      case 2: return 2;     //GREEN
      case 3: return 6;     //BROWN
      case 4: return 1;     //BLUE;
      case 5: return 5;     //MAGENTA;
      case 6: return 3;     //CYAN;
      case 7: return 7;     //LIGHTGRAY;
      case 8: return 8;     //DARKGRAY;
      case 9: return 12;    //LIGHTRED;
      case 10:return 10;    //LIGHTGREEN
      case 11:return 14;    //YELLOW;
      case 12:return 9;     //LIGHTBLUE;
      case 13:return 13;    //LIGHTMAGENTA
      case 14:return 11;    //LIGHTCYAN;
      case 15:return 15;    //WHITE;
   }
   return col;
 }

};
//	admin *u[3];

 class home                     //page=0
 {
 common *c;
// welcome w;
 public:
 home()
 {
 int status,k,j=0,x,y;
// setbkcolor(GREEN);
 //cleardevice();
 //w.loading();
 cleardevice();
 rectangle(0,0,getmaxx(),getmaxy());
 setcolor(RED);
 settextstyle(0,HORIZ_DIR,2);
 outtextxy(100,20,"WELCOME TO RAILWAYS ENQUIRY");
 status = initmouse();        //checking if mouse pointer available or not

  if ( status == 0 )
 {printf("Mouse support not available.\n");
  getch();
  assert(1);
  }
  else
   {
      showmouseptr();
      restrictmouseptr(1,5,600,420);
      settextstyle(3,HORIZ_DIR,2);
      setcolor(RED);

      for(k=0;k<3;k++)
      {
	//rectangle(10,120+j,250,150+j);    //bar3d
	bar3d(10,120+j,250,150+j,10,10);
	j=j+70;
      }

      setfillstyle(INTERLEAVE_FILL,RED);
      floodfill(11,121,RED);
      floodfill(11,191,RED);
      floodfill(11,261,RED);
      setcolor(YELLOW);
      outtextxy(20,120,"1) Administrator Login");
      outtextxy(20,190,"2) User's Login");
      outtextxy(20,260,"3) Exit");
      delay(1000);
      c=new common(0);
     }

   }
 };



admin *createadmin();

 void bookticket()
 {
     int j=0,k,age,tno,psg,d,m,y;
     char name[20],bst[20],dst[20],g;
     //setbkcolor(BROWN);
     cleardevice();
     setcolor(GREEN);
     settextstyle(0,HORIZ_DIR,2);
     outtextxy(100,20,"WELCOME TO RAILWAYS ENQUIRY");
     outtextxy(200,50,"FILL DETAILS");
     //gotoxy(1,7);
     setcolor(RED);
     rectangle(360,75,580,105);
     for(k=0;k<6;k++)
     {
	  rectangle(15,120+j,40,150+j);
	  rectangle(40,120+j,300,150+j);
	  rectangle(300,120+j,580,150+j);
	  j=j+45;
     }
     rectangle(20,400,80,430);
     rectangle(540,400,600,430);
     j=0;
     setcolor(WHITE);
     setfillstyle(SOLID_FILL,WHITE);
     for(k=0;k<6;k++)
     {
	  floodfill(16,121+j,RED);
	  floodfill(41,121+j,RED);
	  floodfill(301,121+j,RED);
	  j=j+45;
     }
     floodfill(361,76,RED);
     floodfill(541,401,RED);
     floodfill(21,401,RED);
     setcolor(RED);
     settextstyle(0,HORIZ_DIR,0);
     outtextxy(365,85,"Journey Date-");
     outtextxy(495,85,"/");
     outtextxy(520,85,"/");
     outtextxy(20,130,"1.");
     outtextxy(20,175,"2.");
     outtextxy(20,220,"3.");
     outtextxy(20,265,"4.");
     outtextxy(20,310,"5.");
     outtextxy(20,355,"6.");
     outtextxy(45,132,"Enter Name of Passenger-");
     outtextxy(45,177,"Enter Age-");
     outtextxy(305,177,"Enter Gender-");
     outtextxy(45,222,"Enter Boarding Station Code-");
     outtextxy(45,267,"Enter Destination Station Code-");
     outtextxy(45,312,"Enter Train No.-");
     outtextxy(45,357,"Enter no. of Passengers-");
     outtextxy(35,412,"BACK");
     outtextxy(555,412,"BOOK");
     gotoxy(61,6);
 //try{
     cin>>d;
     gotoxy(64,6);
     cin>>m;
     gotoxy(67,6);
     cin>>y;
     if(d<0 || m<0 || y<0 || d>30 || m>12 || y>2014)
     {
	//throw ("date");
	cleardevice();
	gotoxy(1,1);
	cout<<"Entered wrong date,month,year";
	getch();
	bookticket();
     }


     gotoxy(40,9);
     cin>>name;
     gotoxy(19,12);
     cin>>age;
     if(age<18)
     {
	cleardevice();
	cout<<"U must be greter than 18 ";
	//throw("age");
	getch();
	bookticket();
     }
     //}

     gotoxy(54,12);
     cin>>g;
     //if(g!='M' || g!= 'F')
     //throw("gender");
     gotoxy(40,14);
     cin>>bst;
     gotoxy(40,17);
     cin>>dst;
     gotoxy(40,20);
     cin>>tno;
     gotoxy(40,23);
     cin>>psg;
      int flag=1,flag2=0,i=0;

 char source[10],dest[10];
 int tindex=-1,sindex=-1,dindex=-1;
 int temp;

		for(j=0;j<trcount;j++)
		{
			 temp=(t[j]->retno());

			if(temp==tno)
			{
		  //cout<<temp<<" ";
				tindex=j;
				break;
			}
		}
		       // throw("tindex",-1);
		     //  cout<<"t_no is not valid ";
		       assert(tindex>0);
		for(j=0;j<stcount;j++)
		{
			if(strcmp(s[j]->retcode(),bst)==0)
			{
				sindex=j;
				flag2++;
			}
			if(strcmp(s[j]->retcode(),dst)==0)
			{
				dindex=j;
				flag2++;
			}
			if(flag2==2)
			{flag2=0;
			break;
			}
		}
		       //	throw("stcode",-1)
		      //	cout<<"invalid stcode";
			assert(sindex>0 || dindex>0);
		//cout<<sindex<<" "<<dindex;


     tic[pnrcount]=new ticket(age,psg,g,name,t[tindex],s[sindex],s[dindex]);
     pnrcount=pnrcount+1;
     tic[pnrcount-1]->viewticket();
     normal n;

}

void inserttrain();
void Exit();

class common
{
print *p;
user *u;
int give;
train_btw_2_station *tbts;

public:
	common()
	{
	}
common(int pg)           //pg=page from which common is called
 {                             //here pg is the page from which the function
  int button,x,y;             //is called  or on which we are in output
  getmousepos(&button,&x,&y);

  while(!kbhit())
  {
   getmousepos(&button,&x,&y);
      if(pg==0)
      {
	 if(button == 1 && x>=10 && x<=250 && y>=120 && y<=150)
	 {
	    button = -1;
	    cleardevice();
	 //   p=new print;
	    //u=new admin;

	    admin *a=createadmin();
	    a->admin1();           //admin fn or page 1
	 }
	 else if(button==1 && x>=10 && x<=250 && y>=190 && y<=220)
	 {
	    button = -1;
	    cleardevice();
	    //cout<<"NOT AVAILABLE YET";
	    normal n;            //page 2
	 }
	 else if(button==1 && x>=10 && x<=250 && y>=260 && y<=290)
	 {
	    button=-1;
	    cleardevice();
	    Exit();
	 }
      }
      else if(pg==1)                //from admin login
       {
	 if(button==1 && x>=540 && x<=635 && y>=330 && y<=360)
	 {
	    button=-1;
	    cleardevice();
	    home h;
	    //common chome(0);
	    //back(0);            // home()
	 }
       }

     else if(pg==3)
       {
	 if(button == 1 && x>=10 && x<=250 && y>=120 && y<=150)
	 {
	    button = -1;
	    cleardevice();
	    view(t,trcount);            //page4
	    //tbts=new train_btw_2_station ;	   //page 10
	 }
	 else if(button==1 && x>=10 && x<=250 && y>=190 && y<=220)
	 {
	    button = -1;
	    cleardevice();           //page5
	    view(s,stcount);
	    //user2();       //page 13
	 }
	 else if(button==1 && x>=10 && x<=250 && y>=260 && y<=290)
	 {
	    button=-1;
	    cleardevice();
	    inserttrain();
	    admin *a1=createadmin();
	    a1->admin1();
	   // t[trcount]=new train();
	   //trcount=trcount+1;
	    //home();//home or back(0) same thing
	 }
	 else if(button==1 && x>=10 && x<=250 && y>=330 && y<=360)
	 {
	    button=-1;
	    cleardevice();
	//    int tno=deltrain();
	  int j=0,tindex,tno;
	   gotoxy(37,12);
	   cout<<"Enter Train no. to delete ";
		cin>>tno;
		for(j=0;j<trcount;j++)
		{
			if(t[j]->retno()==tno)
			{
				tindex=j;
				break;
			}
		}


	   del(t[tindex],tno,1);
	  //admin*a->admin1();
	  // normal n;
	    //bookticket b;

	    //home();//home or back(0) same thing
	 }
	 else if(button==1 && x>=10 && x<=250 && y>=400 && y<=420)
	 {
	    button=-1;
	     cleardevice();

	     char*scode;
	     int j=0,sindex;
	     gotoxy(37,12);
	     cout<<"Enter station code to delete ";
	     cin>>scode;
		for(j=0;j<stcount;j++)
		{
			if(strcmp(s[j]->retcode(),scode)==0)
			{
				sindex=j;
				break;
			}
		}

	    del(s[sindex],scode,2);
	    //a->admin1();
	    // ticket t->viewticket(); b;
	    //home();//home or back(0) same thing
	 }
	 else if(button==1 && x>=540 && x<=635 && y>=330 && y<=360)
	 {
	    button=-1;               //rectangle(540,330,635,360);
	    //cleardevice();
	    home h;
	    //bookticket b;
	    //home();//home or back(0) same thing
	 }

       }
     else if(pg==2)
       {
	 if(button == 1 && x>=50 && x<=340 && y>=120 && y<=150)
	 {
	    button = -1;
	    cleardevice();
	    tbts=new train_btw_2_station ;	   //page 10
	 }
	 else if(button==1 && x>=50 && x<=340 && y>=165 && y<=195)
	 {
	    button = -1;
	    cleardevice();
	    int index=-1,tno;
	    int i;
	    gotoxy(1,1);
	    cout<<"Enter train no ";
	    cin>>tno;
	    for(i=0;i<trcount;i++)
	    {
			if(t[i]->retno()==tno)
			{
			index=i;
			break;
			}
	    }
	if(index>0)
	t[index]->showseats(1);
	else
	cout<<" T_no does not Matched Enter Again";
	getch();
	normal n;
	    //view(t,trcount);
	    //user2();       //page 13
	 }
	 else if(button==1 && x>=50 && x<=340 && y>=210 && y<=240)
	 {
	    button=-1;
	    cleardevice();
	    char *source;
	    int i;
	    int index=-1;
	    gotoxy(1,1);
	    cout<<"Enter Source code ";
	    cin>>source;

		for(i=0;i<stcount+1;i++)
		{
		if(strcmp(s[i]->retcode(),source)==0)
		{
			index=i;
			break;

		}
		}
		getch();
	if(index>=0)
	{    cout<<"correct";
	 getch();
	s[index]->printst();
	}
	else
	{cleardevice();
	cout<<" st_code does not Matched Enter Again";
	getch();
	}
	getch();
	normal n;      //on user page
	 }
	 else if(button==1 && x>=50 && x<=340 && y>=255 && y<=285)
	 {
	    button=-1;
	    cleardevice();
	    bookticket();
	    //bookticket b;
	    //home();//home or back(0) same thing
	 }
	 else if(button==1 && x>=50 && x<=340 && y>=300 && y<=330)
	 {
	    button=-1;
	    cleardevice();
	    ticketinfo();
	 }
	else if(button==1 && x>=50 && x<=340 && y>=345 && y<=375)
	 {
	    button=-1;
	    cleardevice();
	    checkseats();
	    //home();//home or back(0) same thing
	 }
	 else if((button==1 && x>=540 && x<=635 && y>=330 && y<=360) || (button==1 && x>=410 && x<=635 && y>=380 && y<=410))
	 {
	    button=-1;
	    cleardevice();
	    home h;
	    //common chome(0);
	    //back(0);            // home()
	 }

       }
       else if(pg==6)
       {
	 if(button==1 && x>=50 && x<=200 && y>=120 && y<=150)
	 {
	    button=-1;
	    cleardevice();
	    ticket *tick=findticket();
	    if(tick!=NULL)
	    cout<<tick;
	    else
	    {cleardevice();
	    gotoxy(1,1);
	    cout<<"Ticket does not exists ";
	    }
	    normal n;
	    //home();//home or back(0) same thing
	 }
	 else if(button==1 && x>=50 && x<=200 && y>=165 && y<=195)
	 {
	    button=-1;
	    cleardevice();
	    char b=NULL;
	    ticket *tick=findticket();
	    //tick->delticket();
	   // --(*tick);
	    getch();
	    cout<<tick;
	    cleardevice();
	    //tick--;
	    gotoxy(1,1);
	    cout<<"Confirm To Delete PRess Enter\n\n";
	    b=getch();
	    if(b==13)
	    {
		--(*tick);
       //	(*tick)--;
		delete tick;
		cout<<"Ticket has been Cancelled\n";
	    }
	    else
	    {   //tick--;
		cout<<"SoRRy Check aGain";

	    }
	    getch();
	    normal n;
	    //cout<<tick;
	    //home h;
	    //common chome(0);
	    //back(0);            // home()
	 }
       }

       else if(pg==5)
       {
	 if(button==1 && x>=20 && x<=100 && y>=400 && y<=430)
	 {
	    button = -1;
	    //cleardevice();
	    give=1;
	   // view(t,trcount);
	    //user2();       //page 13
	 }
	 else if(button==1 && x>=280 && x<=360 && y>=400 && y<=430)
	 {
	    button=-1;
	  //  cleardevice();
	    give=2;
	    //home();//home or back(0) same thing
	 }
	 else if(button==1 && x>=540 && x<=620 && y>=400 && y<=430)
	 {
	    button=-1;
	    //cleardevice();
	    give=3;
	    //bookticket b;
	    //home();//home or back(0) same thing
	 }
      }
      else if(pg==8)
      {
      if(button==1 && x>=20 && x<=80 && y>=400 && y<=430)
	 {
	    button=-1;
	    cleardevice();
	    home h;
	    //home();//home or back(0) same thing
	 }
	 else if(button==1 && x>=500 && x<=580 && y>=400 && y<=430)
	 {
	    button=-1;
	    cleardevice();
		gotoxy(33,12);
		cout<<"Train has been inserted\n";
		gotoxy(33,14);
		cout<<"U have a new train no. "<<(t[trcount-1]->retno());
		getch();
		home h;
	    //bookticket b;
	    //home();//home or back(0) same thing
	 }
      }
      else if(button==1 && x>=410 && x<=635 && y>=380 && y<=410)
      {
	    button=-1;
	    cleardevice();
	    home h;
	  //  back(0);           //page 0 or home()
      }
      /*else if(button==1 && x>=410 && x<=635 && y>=380 && y<=410)
	 {
	    button=-1;
	    cleardevice();
	    home h;
	    //home();//home or back(0) same thing
	 } */
   }
  }
  int givecommand()
  {
	return give;
  }
};

 void common2()             //creates back and return main menu button
 {
     setcolor(RED);
     rectangle(540,330,635,360);
     setfillstyle(INTERLEAVE_FILL,RED);
     floodfill(541,331,RED);
     setcolor(YELLOW);
     settextstyle(3,HORIZ_DIR,2);
     outtextxy(560,330,"Back");
     setcolor(RED);
     rectangle(410,380,635,410);
     setfillstyle(INTERLEAVE_FILL,RED);
     floodfill(411,381,RED);
     setcolor(YELLOW);
     settextstyle(3,HORIZ_DIR,2);
     outtextxy(420,382,"Return To Main Menu");
  }

void inserttrain()                   //page 8
{
     int j=0,k;
     char tname[50],zone[10],st[10];
     char name[20],bst[20],dst[20],g[2];
     setcolor(GREEN);
     settextstyle(0,HORIZ_DIR,2);
     outtextxy(100,20,"WELCOME TO RAILWAYS ENQUIRY");
     setcolor(RED);
     outtextxy(200,50,"FILL DETAILS");
     for(k=0;k<2;k++)
     {
	rectangle(15,120+j,40,150+j);
	rectangle(40,120+j,200,150+j);
	rectangle(200,120+j,580,150+j);
	j=j+45;
     }
     rectangle(15,120+j,40,290+j);
     rectangle(40,120+j,200,290+j);
     rectangle(200,120+j,580,290+j);
     rectangle(20,400,80,430);
     j=0;
     setcolor(WHITE);
     setfillstyle(SOLID_FILL,WHITE);

     for(k=0;k<2;k++)
     {
       floodfill(16,121+j,RED);
       floodfill(41,121+j,RED);
       floodfill(201,121+j,RED);
       j=j+45;
     }
     floodfill(16,121+j,RED);
     floodfill(41,121+j,RED);
     floodfill(201,121+j,RED);
     floodfill(21,401,RED);
     setcolor(RED);
     settextstyle(0,HORIZ_DIR,0);
     outtextxy(20,130,"1.");
     outtextxy(20,175,"2.");
     outtextxy(20,220,"3.");
     outtextxy(45,132,"Enter Train Name - ");
     outtextxy(45,177,"Enter Train Zone - ");
     outtextxy(45,222,"Enter Stations - ");
     outtextxy(35,408,"BACK");
     gotoxy(27,9);
     common *c=new common(8);
     cin>>tname;
     delete c;
     gotoxy(27,12);

     c=new common(8);
     delete c;

     cin>>zone;
     int i;
     gotoxy(27,15);
     cout<<"yoU Must Enter Only 3 Trains At Beginning ";
     c=new common(8);
     delete c;

     for(i=0;i<8;i=i+2)
     {
     gotoxy(27,17+i);
     cin>>st;
     }

     setcolor(RED);
     rectangle(500,400,580,430);
	  setcolor(WHITE);
     setfillstyle(SOLID_FILL,WHITE);
     floodfill(501,401,RED);
    setcolor(RED);
    settextstyle(0,HORIZ_DIR,2);
     outtextxy(505,408,"Continue");



     int zonal;
     if(strcmp("North",zone)==0)
	      zonal=1;
     else if(strcmp("East",zone)==0)
		zonal=2;
     else if(strcmp("South",zone)==0)
		zonal=3;
     else
		zonal=4;

     t[trcount]=new pass(tname,zonal,100);
     trcount=trcount+1;
     c=new common(8);

   }

void ticketinfo()               //page 6
{       	cleardevice();
	setcolor(RED);
	settextstyle(0,HORIZ_DIR,2);
	outtextxy(100,20,"WELCOME TO RAILWAYS ENQUIRY");
	common2();
	setcolor(RED);
	int k,j=0 ;
	for(k=0;k<2;k++)
	{
		rectangle(15,120+j,50,150+j);
		rectangle(50,120+j,200,150+j);
		j=j+45;
	}
	j=0;
	setfillstyle(SOLID_FILL,WHITE);
	for(k=0;k<2;k++)
	{
	    floodfill(16,121+j,RED);
	floodfill(51,121+j,RED);
	j=j+45;
	}
	settextstyle(0,HORIZ_DIR,0);
	outtextxy(20,125,"1.");
	outtextxy(20,170,"2.");
	outtextxy(55,130,"View Ticket");
	outtextxy(55,175,"Cancel Ticket");
	common *c=new common(6);
}

class user
{
protected:
common *c;
public:
user()
{
	cleardevice();
	setcolor(RED);
	settextstyle(0,HORIZ_DIR,2);
	outtextxy(100,20,"WELCOME TO RAILWAYS ENQUIRY");
}
/*
void admin1()
{
}
char *retusername()
{};
char *retpass()
{};
*/
};

class normal:public user             //page 2
{
public:
normal()
{
	//cleardevice();
	int k,j=0;
	//cleardevice();
	rectangle(0,0,getmaxx(),getmaxy());
	setcolor(RED);
	settextstyle(0,HORIZ_DIR,0);
	//outtextxy(15,110,"S.No");
	settextstyle(3,HORIZ_DIR,2);
	setcolor(RED);
for(k=0;k<6;k++)
{
	rectangle(15,120+j,50,150+j);
	rectangle(50,120+j,340,150+j);
	j=j+45;
}
j=0;
setcolor(WHITE);
setfillstyle(SOLID_FILL,WHITE);
for(k=0;k<6;k++)
{
    floodfill(16,121+j,RED);
    floodfill(51,121+j,RED);
    j=j+45;
}
setcolor(RED);
outtextxy(20,125,"1.");
outtextxy(20,170,"2.");
outtextxy(20,215,"3.");
outtextxy(20,260,"4.");
outtextxy(20,305,"5.");
outtextxy(20,350,"6.");
outtextxy(55,125,"Train between two stations");
outtextxy(55,170,"Train details");
outtextxy(55,215,"Station details");
outtextxy(55,260,"Book Ticket");
outtextxy(55,305,"Ticket Info.");
outtextxy(55,350,"Seat availibility");
common2();
//getch();
delay(1000);
c=new common(2);
}

};
static entercount=0;


class admin:public user
{
char *name,*username,*password;
public:
admin()
{
}
admin(char *n,char*u,char*p)
{
//name=new char[strlen(n)+1];
//username=new char[strlen(u+1)];
//password=new char[strlen(p)+1];
name=n;
username=u;
password=p;
//cout<<name<<" "<<username<<" "<<password;
}

void admin1()                                     //page3
{
       //	clrscr();
	//static count=0;
	cleardevice();
	setcolor(RED);
	settextstyle(0,HORIZ_DIR,2);
	outtextxy(100,20,"WELCOME TO RAILWAYS ENQUIRY");

	setcolor(RED);
	int j=0;
	for(int k=0;k<5;k++)
	{
	   rectangle(10,120+j,250,150+j);
	   j=j+70;
	}

	setfillstyle(INTERLEAVE_FILL,RED);
	floodfill(11,121,RED);
	floodfill(11,191,RED);
	floodfill(11,261,RED);
	floodfill(11,331,RED);
	floodfill(11,401,RED);
	setcolor(YELLOW);
	settextstyle(3,HORIZ_DIR,2);
	outtextxy(20,120,"1)Print Train Details");
	outtextxy(20,190,"2)Print Station Details");
	outtextxy(20,260,"3)Insert a new Train");
	outtextxy(20,330,"4)Delete a Train");
	outtextxy(20,400,"5)Delete a Station");
	setcolor(RED);
	rectangle(540,330,635,360);
	floodfill(541,331,RED);
      //	setcolor(YELLOW);

      settextstyle(4,HORIZ_DIR,2);
	setcolor(9);
	outtextxy(460,45,"Welcome");
	outtextxy(540,45,name);
		setcolor(YELLOW);
	settextstyle(3,HORIZ_DIR,2);
	outtextxy(560,331,"Logout");
	//getch();
	delay(1000);
	entercount++;
	c=new common(3);
       // cleardevice();
	if(entercount<5)
	{admin1();
	}

}
friend admin *createadmin();
};

admin *createadmin()                  //page1
{
	cleardevice();
	int l=0,k,m=0,j,button,x,y;
	char v[4],b=NULL;
	admin *u[3];
	u[0]=new admin("Dishank","dish_95","3635");
	u[1]=new admin("Prakhar","prakh_95","3608");
	u[2]=new admin("Yugal","yugs_95","3611");

	setcolor(RED);
	settextstyle(0,HORIZ_DIR,2);
	outtextxy(100,20,"WELCOME TO RAILWAYS ENQUIRY");
	//settextstyle(0,HORIZ_DIR,0);
	char *a;
	common2();
	setcolor(RED);
     settextstyle(1,HORIZ_DIR,2);                     //gothic
     outtextxy(230,60,"MEMBER'S LOGIN");
     outtextxy(10,100+4+2,"Enter Username-");
     gotoxy(25,8);
     //delay(1000);
     common *c=new common(1);
     //delete common;		      //calling common from page 1
     gets(a);
    // delete c;
     int index=0,i;
   for(i=0;i<3;i++)
   {
   //cout<<index
   m=strcmp(a,u[i]->username);
   if(m==0)
   {
	index=i;
	break;
   }
   }
   outtextxy(10,120+10+2+4,"Enter Password-");
   gotoxy(25,10);
   common *c2=new common(1);		      //calling common from page 1
  // delete c2;
   while(b!=13)
   {
   b=getch();
   if(b==13)
   break;
   v[l]=b;
   printf("*");
   l++;
   }
   v[l]=NULL;
 //  cout<<a<<" "<<index<<" "<<v;

   if(m==0 && (strcmp(v,u[index]->password)==0)) //checking for correct condition of Username and Password
   {
   gotoxy(40,20);
   //outtexyxy(360,
   cout<<"successfully logined";
   delay(1000);
   cleardevice();
   return (u[index]);
   }
   else
   {
   gotoxy(30,20);
   cout<<"\nWrong Input Enter again ";

   getch();
   home h;
   //return(createadmin());
   }
  //return u[index];
  // common(1);
  }                 //calling common from page 1





/*class print
{
public:
	print()
	{ 	int i;
		cout<<"\nTrains:\n";
		for(i=0;i<trcount;i++)
		{
			cout<<i+1<<" ";
			t[i]->display();
		}
		cout<<"\nStations:\n";
		for(i=0;i<stcount;i++)
		{
			cout<<i+1<<" ";
			s[i]->display();
		}
	}
};*/


void checkseats()
{
int tno;
int index=-1;
int i;
gotoxy(1,1);
cout<<"Enter train no ";
cin>>tno;
cout<<"\nt_no matched";
gotoxy(10,30);
delay(1000);
for(i=0;i<trcount;i++)
{
	if(t[i]->retno()==tno)
	{
		index=i;

		break;
	}
}
if(index>=0)
t[index]->showseats(2);
else
cout<<" T_no does not Matched Enter Again";
getch();
normal *n=new normal;
}

class train_btw_2_station           //page 7
{
char *source,*dest;
public:
train_btw_2_station()
{
cleardevice();
//clrscr();
gotoxy(0,0);
source=new char[5];
dest=new char[5];
gotoxy(8,0);
cout<<"Enter Source station code ";
cin>>source;
cout<<"You have entered "<<source<<endl;
cout<<"Enter Destination station code ";
cin>>dest;
cout<<"You have entered "<<dest<<endl;
int once;
for(int i=0;i<trcount;i++)
t[i]->train_by_stat(source,dest);
delete source;
delete dest;
if(found==0)
cout<<"No such Train Found ";
getch();
normal *n=new normal;
}
};



template <class T,class z> void del(T *o ,z x,int choice )
{
//int choice;
if(choice==1)
{
cout<<"Train of t_no "<<x<<" has been Deleted";
}
else
{
cout<<"Station of st_code "<<x<<" has been Deleted";
}
delete o;
}

template <class T> void view(T *o,int count)
{
int m=0,j=0,i;
int page=0,flag=0;
int command;
common*cd ;
for(j=0;j<count;)
{
	m=0;
	for( i=j;i<j+5;i++)
	{
		if(o[i]!=NULL)
		{
		o[i]->display(m,i+1);
		}
		m=m+60;
	}
	page++;
	cd=new common(5);
	command=cd->givecommand();
	gotoxy(1,1);
	//cout<<command;
	//delay(1000);
	getch();
	if(command==1 && page==1)
	{
		//delete cd;
		cleardevice();
		admin *np=new admin;

	}
	else if(command==3)
	{
		  j=j+5;

	}
	else if(command==1)
	{
		page--;
		j=j-5;
	}
	else if(command==2)
	{
	     //	admin *np=new admin;

		flag=1;
		home h;
		break;
	}
	delete cd;

//getch();
}
//int d=0;
}
//int d=0;
//if(flag==1)
//home h;	//normal *np=new normal;


catch(int t,int d)
{
if(t==0 && d==1)
cout<<"Enter source again\n";
else if(t==1 && d==0)
cout<<"Enter destination again\n";
else
cout<<"Enter both\n";
}

catch(char *str)
{
cleardevice();
cout<<str<<" u have entered is not valid";
getch();
bookticket();
}

catch(char*str,int x)
{
cout<<"Error in "<<str<<x;
cout<<" \nError of negative no";
}

catch(...)
{
cout<<"Something is Wrong";
}




void main()
{
 int i;
 int gd=DETECT,gm;
 clrscr();
 initgraph(&gd,&gm,"C:\\turboc3\\BGI");
 file1();
 file2();
 file3();
 file4();
 file5();
  welcome w;
   cleardevice();

w.loading();
cleardevice();
home h;


getch();
}

 void Exit()
  {
  int flag=1;
   cleardevice();
   setcolor(YELLOW);
   settextstyle(3,HORIZ_DIR,5);

   outtextxy(160,180,"!!  THANK YOU   !!");
   outtextxy(120,280," Press any key to EXIT");
   getch();
   assert(flag==0);
//  exit;
  }

/*
-------------------------------------------------------------------------------------------------
FINISH
*/
