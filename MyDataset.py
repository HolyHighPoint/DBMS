import os
import subprocess
import sys
import time
from peewee import ForeignKeyMetadata
from peewee import IndexMetadata
from peewee import ColumnMetadata
def exe(command,delay=3):
    wr=open('sqlcommand.txt','w')
    wr.write(command)
    wr.close()
    fi=open(os.path.join('sqlcommand.txt'),'r')
    p=subprocess.Popen("nc 138.128.213.58 2333",stdin=fi)
    time.sleep(3)
    p.kill()
    time.sleep(delay)
    fo=open(os.path.join('sqlreturn.txt'),'w')
    p=subprocess.Popen("nc 138.128.213.58 2334",stdout=fo)
    time.sleep(delay)
    p.kill()
    rd=open('sqlreturn.txt','r')
    s=rd.readlines()
    errMsg=""
    return (s,errMsg)

class MyDataset:
    def __init__(self,database):
        self.database=database
        command='''USE DATABASE '''+database+''' ;'''
        command=command+'''  SHOW TABLES;'''
        code=exe(command)[0]
        info = code
        tablelist=list([])
        for line in info:
            line=line.strip('\n')
            tablelist.append(line)
        self.tables=tablelist
        self.tables.pop()
        
    def create_table(self,table):
        command='''USE DATABASE '''+self.database+''' ;'''
        command=command+'''  CREATE TABLE '''
        command=command+table
        command=command+''' (id integer NOT NULL, PRIMARY KEY(id) );'''
        code=exe(command)[0]
        self.tables.append(table)

    def drop_table(self,table):
        command='''USE DATABASE '''+self.database+''' ;'''
        command=command+'''  DROP TABLE '''
        command=command+table
        command=command+''' ;'''
        code=exe(command)[0]
        self.tables.remove(table)

    def get_columns(self,table):
        command='''USE DATABASE '''+self.database+''' ;'''
        command=command+'''  DESC '''
        command=command+table
        command=command+''' ;'''
        code=exe(command)[0]
        code.pop()
        columns=list([])
        for line in code:
            line=line.strip('\n')
            values=line.split(' ')
            name=values[0].strip(':')
            data_type=values[1]
            if (values[2]=='--Not'):
                null=False
            else:
                null=True
            if (values[len(values)-2]=='Not'):
                pk=False
            else:
                pk=True
            column=ColumnMetadata(name=name,data_type=data_type,null=null,primary_key=pk,table=table)
            columns.append(column)
        return columns

    def get_content(self,table,page,rpp):
        columns=self.get_columns(table)
        cnames=([])
        offset=(page-1)*rpp
        for column in columns:
            cnames.append(column[0])
        command='''USE DATABASE ''' + self.database+ ''';'''
        command=command+''' SELECT * FROM '''
        command=command+table
        command=command+''' LIMIT '''+str(rpp)+''' '''
        command=command+''' OFFSET '''+str(offset)+''' '''
        command=command+''' ;'''
        code=exe(command,10)[0]
        code.pop()
        records=([])
        for line in code:
            line=line.strip('\n')
            attrs=line.split('| |')
            entry=([])
            for i in range(len(attrs)):
                if i==0 :
                    att=attrs[0][2:]
                    att.strip(' ')
                    att=att[:len(att)-1]
                    entry.append((cnames[0],att))
                elif (i==len(attrs)-1) :
                    att=attrs[i].strip(' |')
                    att=att[0:]
                    entry.append((cnames[i],att))
                else:
                    att=attrs[i].strip(' ')
                    att=att[0:]
                    entry.append((cnames[i],att))
            records.append(dict(entry))
        records.pop()
        records=records[1:]
        return records
    
    def get_foreign_keys(self,table):
        #ForeignKeyMetadata(column= ,dest_table= , dest_column= , table= )
        return
        #同上，用ForeignKeyMetadata构造

    def get_indexes(self,table):
        command='''USE DATABASE '''+self.database+''' ;'''
        command=command+'''  DESC '''
        command=command+table
        command=command+''' ;'''
        code=exe(command)[0]
        code.pop()
        indexes=list([])
        for line in code:
            line=line.strip('\n')
            values=line.split(' ')
            if (values[len(values)-2]=='Not'):
                name=values[0].strip(':')
                idxname=table+"_"+name
                unique=False
                if (values[len(values)-3]=='Indexed,'):
                    idx=True
                else:
                    idx=False
            else:
                name=values[0].strip(':')
                idxname=table+"_"+name
                unique=True
                if (values[len(values)-2]=='Indexed,'):
                    idx=True
                else:
                    idx=False
            if idx:
                sql='''CREATE INDEX '''+table+''' ( '''+name+''' ) '''
                index=IndexMetadata(name=idxname,sql=sql,columns=[name],unique=unique,table=table)
                indexes.append(index)
        return indexes
        #同上，用IndexMetadata构造

    def get_table_sql(self,table):
        columns=self.get_columns(table)
        sql='''CREATE TABLE '''+table+''' ('''
        for column in columns:
            sql=sql+column[0]+" "+column[1]+" "
            if not column[2]:
                sql=sql+" NOT NULL "
            sql=sql+", "
            if column[3]:
                pkname=column[0]
        sql=sql+'''PRIMARY KEY ('''+pkname+''') );'''
        return sql
        #返回值为字符串，用以建表的sql语句

    def add_column(self,table,name,col_type):
        return
        #以下全是内部维护

    def drop_column(self,table,name):
        return

    def rename_column(self,table,rename,rename_to):
        return

    def add_index(self,table,indexed_columns,unique=False):
        command='''USE DATABASE '''+self.database+''' ;'''
        command=command+'''  CREATE INDEX '''
        command=command+table
        command=command+''' ('''+indexed_columns[0]+''');'''
        code=exe(command)[0]
        return code

    def drop_index(self,table,name):
        command='''USE DATABASE '''+self.database+''' ;'''
        command=command+'''  DROP INDEX '''
        command=command+table
        command=command+''' ('''+name+''');'''
        code=exe(command)[0]
        return code

    def count(self,table):
        command='''USE DATABASE ''' + self.database+ ''';'''
        command=command+''' SELECT NUM(id) FROM '''
        command=command+table
        command=command+''' ;'''
        code=exe(command)[0]
        c=code[1].split('|')
        c=c[1]
        start=-1
        for i in range(len(c)):
            if (c[i]=='=')and(start<0):
                start=i
        c=c[start+1:]
        return int(c)
        #整数，记录的个数

    def execute_query(self,sql):
        sql="USE DATABASE "+self.database+" ; "+sql
        code=exe(sql)
        err=code[1]
        code=code[0]
        if not code:
            return (0,"",err)
        matrix=([])
        rowcount=0
        for line in code:
            line=line.strip('\n')
            row=line.split('| |')
            if len(row)>0:
                if (len(row[0])>0):
                    if(row[0][0]=='|'):
                        row[0]=row[0][1:]
                if (len(row[len(row)-1])>0):
                    if(row[len(row)-1][len(row[len(row)-1])-2]=='|'):
                        row[len(row)-1]=row[len(row)-1][:len(row[len(row)-1])-2]
            rowcount=rowcount+1
            matrix.append(row)
        if len(matrix)>0:
            matrix.pop()
        if len(matrix)>0:
            matrix.pop()
        if len(matrix)>0:
            matrix=matrix[1:]
        if (rowcount>=3):
            rowcount=rowcount-3
        return (rowcount,matrix,err)

#mydataset=MyDataset("orderDB")
#mydataset.create_table("student")
#mydataset.drop_table("student")
#print(mydataset.get_columns("book"))
#print(mydataset.get_content("book",2,5))
#print(mydataset.get_table_sql("book"))
#mydataset.add_index("book",["authors"])
#mydataset.drop_index("book","authors")
#print(mydataset.get_indexes("book"))
#print(mydataset.count("book"))
#print(mydataset.execute_query("SELECT MAX(id) FROM book;"))

