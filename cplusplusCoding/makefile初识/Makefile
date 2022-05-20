#定义变量
#src=sub.o add.o mult.o div.o main.o
#手动输入太麻烦，建议用函数定义
#$(wildcard PATTERN...)函数名 参数
#$(wildcard *.c ./sub/*.c) 当前目录下的所有.c文件和./sub目录下所有的.c文件
#返回 就是a.c b.c 等
#$(patsubst <pattern>,<replacement>,<text>)
#$(patsubst %.c, %.o, x.c bac.c)
#返回x.o bar.c
#AR 归档维护程序的名称，默认值为ar
#CC，c编译器
#CXX，c++编译器
#$@ 目标完整名称
#$< 第一条规则所需要的，第一个依赖文件的名称
#$^ 所有依赖文件
src=$(wildcard *.c)
target=app
objs=$(patsubst %.c, %.o, $(src))#把src中符合.c规则的，都替换成.o
$(target):$(objs)
	$(CXX) $(objs) -o $(target)
#$(CXX) g++ $^第一个

%.o:%.c
	$(CXX) -c $< -o $@

.PHONY:clean #伪目标，不会生成clean文件
clean:
	rm $(objs) -f
#app:sub.o add.o mult.o div.o main.o
#	g++ sub.o add.o mult.o div.o main.o -o app

#sub.o:sub.c
#	g++ -c sub.c -o sub.o

#add.o:add.c
#	g++ -c add.c -o add.o

#mult.o:mult.c
#	g++ -c mult.c -o mult.o

#div.o:div.c
#	g++ -c div.c -o div.o

#main.o:main.o
#	g++ -c main.c -o main.o

		
