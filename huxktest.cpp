#include <iostream>
#include <libpq-fe.h>
#include <ctime>
using namespace std;

 #define max 100
  string to_String(int n)
 {
  int m = n;
    char s[max];
     char ss[max];
     int i=0,j=0;
     if (n < 0)// 处理负数
     {
         m = 0 - m;
         j = 1;
        ss[0] = '-';
     }    
     while (m>0)
     {
         s[i++] = m % 10 + '0';
         m /= 10;
    }
     s[i] = '\0';
     i = i - 1;
     while (i >= 0)
     {
         ss[j++] = s[i--];
    }    
     ss[j] = '\0';    
     return ss;
 }
int main()
{
    PGconn  *conn;
    PGresult *res;
    const  char *pghost="127.0.0.1";
    const  char *pgport="5432";
    const  char *pgoptions=NULL;
    const  char *pgtty=NULL;
    const  char *pglogin="postgres";
    const  char *pgpwd="123456";
    const  char *dbname="postgres";


    conn=PQsetdbLogin(pghost,pgport,pgoptions,pgtty,dbname,pglogin,pgpwd);
    clock_t temp;
    clock_t Stime;
    if(PQstatus(conn)==CONNECTION_BAD)
    {
      cout << " Connection to database " << dbname << endl;
      PQfinish(conn);
      return 0;
    }
    temp = clock();
      for (int i = 1 ; i < 315360000; i++)
      {
        string instr = "insert into conditions values ( now(), \'huxk\', " ;
        instr += to_String(i);
        instr += ");";
        if(i == 1)
        {
                cout << instr << endl;
        }
        if(i % 10000000 == 0)
        {
            res = PQexec(conn, "COMMIT");
            Stime = clock() - temp;
            cout << " 第 " << i/10000000 <<" 次插入提交10000000 条数据使用的时间是： " << ((float)Stime)/CLOCKS_PER_SEC << " 秒"<< endl;
            temp = clock();

        }
      }

    PQfinish(conn);
    PQclear(res);
    return 0;
}
