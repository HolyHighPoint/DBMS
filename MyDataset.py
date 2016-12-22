import os
import subprocess
import sys
import time
from peewee import ForeignKeyMetadata
from peewee import IndexMetadata
from peewee import ColumnMetadata
def exe(command):
    wr=open('sqlcommand.txt','w')
    wr.write(command)
    wr.close()
    fi=open(os.path.join('sqlcommand.txt'),'r')
    p=subprocess.Popen("nc 138.128.213.58 2333",stdin=fi)
    time.sleep(3)
    p.kill()
    fo=open(os.path.join('sqlreturn.txt'),'w')
    p=subprocess.Popen("nc 138.128.213.58 2334",stdout=fo)
    time.sleep(3)
    p.kill()
    rd=open('sqlreturn.txt','r')
    s=rd.readlines()
    return s

class MyDataset:
    def __init__(self,database):
        self.database=database
        command='''USE DATABASE '''+database+''' ;'''
        command=command+'''  SHOW TABLES;'''
        code=exe(command)
        info = code
        tablelist=list([])
        for line in info:
            line=line.strip('\n')
            tablelist.append(line)
        self.tables=tablelist
        self.tables.pop()
        print(self.tables)
        
    def create_table(self,table):
        command='''USE DATABASE '''+self.database+''' ;'''
        command=command+'''  CREATE TABLE '''
        command=command+table
        command=command+''' (id integer NOT NULL, PRIMARY KEY(id) );'''
        code=exe(command)
        self.tables.append(table)

    def drop_table(self,table):
        command='''USE DATABASE '''+self.database+''' ;'''
        command=command+'''  DROP TABLE '''
        command=command+table
        command=command+''' ;'''
        code=exe(command)
        self.tables.remove(table)

    def get_columns(self,table):
        command='''USE DATABASE '''+self.database+''' ;'''
        command=command+'''  DESC '''
        command=command+table
        command=command+''' ;'''
        code=exe(command)
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
    
    def get_foreign_keys(self,table):
        #ForeignKeyMetadata(column= ,dest_table= , dest_column= , table= )
        return
        #同上，用ForeignKeyMetadata构造

    def get_indexes(self,table):
        return
        #同上，用IndexMetadata构造

    def get_table_sql(self,table):
        return
        #返回值为字符串，用以建表的sql语句

    def add_column(self,table,name,col_type):
        return
        #以下全是内部维护

    def drop_column(self,table,name):
        return

    def rename_column(self,table,rename,rename_to):
        return

    def add_index(self,table,indexed_columns,unique):
        return

    def drop_index(self,table,name):
        return

    def count(self,table):
        return
        #整数，记录的个数

mydataset=MyDataset("orderDB")
#mydataset.create_table("student")
#mydataset.drop_table("student")
print(mydataset.get_columns("book"))
