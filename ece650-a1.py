import math



import re



import sys







graph={}







class Point(object):



    def __init__(self,x,y):



        self.x=float(x)



        self.y=float(y)



    def __eq__(self, other):



        if self.x != other.x:



            return False



        if self.y != other.y:



            return False



        return True



    def __str__ (self):



        return '('+str('%.2f'%self.x)+','+str('%.2f'%self.y)+')'



    



class Edge(object):



    def __init__(self,m,n):



        self.m=int(m)



        self.n=int(n)



    def __eq__(self, other):



        if self.m != other.m:



            return False



        if self.n != other.n:



            return False



        return True



    def __str__ (self):



        return '<' +str(self.m)+','+str(self.n)+'>'



  



class Line(object):



    def __init__(self,src,dst):



        self.src=src



        self.dst=dst



    def __eq__(self, other):



        if self.src != other.src:



            return False



        if self.dst != other.dst:



            return False



        return True



    def __str__(self):



        return str(self.src) + str(self.dst)



    



def area(a0,a1,a2):



    s = a0.x*a1.y + a2.x*a0.y  +a1.x*a2.y - a2.x*a1.y - a0.x*a2.y - a1.x*a0.y



    return s;  







def intersect(l1,l2):



    x1,y1=l1.src.x,l1.src.y



    x2,y2=l1.dst.x,l1.dst.y



    x3,y3=l2.src.x,l2.src.y



    x4,y4=l2.dst.x,l2.dst.y



    p1=Point(x1,y1)



    p2=Point(x2,y2)



    p3=Point(x3,y3)



    p4=Point(x4,y4)



    s1 = area(p1, p2, p3);  



    s2 = area(p1, p2, p4);  



    s3 = area(p3, p4, p1);  



    s4 = area(p3, p4, p2);







    if(s1*s2 <=0 and s3*s4 <= 0):  



        if(s1*s2==0 or s3*s4 ==0):



            if(x1==x3 and y1==y3):



                if((p2.x-p3.x)*(p4.y-p3.y)-(p2.y-p3.y)*(p4.x-p3.x)==0 and 



                   p2.x >= min(p3.x,p4.x) and p2.x <= max(p3.x,p4.x) and 



                   p2.y >= min(p3.y,p4.y) and p2.y <=max(p3.y,p4.y)):



                    return p1,p2



                else:



                    return p1,0



            if(x2==x4 and y2==y4):



                if((p1.x-p3.x)*(p4.y-p3.y)-(p1.y-p3.y)*(p4.x-p3.x)==0 and 



                   p1.x >= min(p3.x,p4.x) and p1.x <= max(p3.x,p4.x) and 



                   p1.y >= min(p3.y,p4.y) and p1.y <=max(p3.y,p4.y)):



                    return p2,p1



                else:



                    return p2,0



            if(x2==x3 and y2==y3):



                if((p1.x-p3.x)*(p4.y-p3.y)-(p1.y-p3.y)*(p4.x-p3.x)==0 and 



                   p1.x >= min(p3.x,p4.x) and p1.x <= max(p3.x,p4.x) and 



                   p1.y >= min(p3.y,p4.y) and p1.y <=max(p3.y,p4.y)):



                    return p2,p1



                else:



                    return p2,0



            if(x1==x4 and y1==y4):







                if((p2.x-p3.x)*(p4.y-p3.y)-(p2.y-p3.y)*(p4.x-p3.x)==0 and 



                   p2.x >= min(p3.x,p4.x) and p2.x <= max(p3.x,p4.x) and 



                   p2.y >= min(p3.y,p4.y) and p2.y <=max(p3.y,p4.y)):



                    return p1,p2



                else:



                    return p1,0



            if((p3.x-p1.x)*(p2.y-p1.y)-(p3.y-p1.y)*(p2.x-p1.x)==0 and 



                  p3.x >= min(p1.x,p2.x) and p3.x <= max(p1.x,p2.x) and 



                  p3.y >= min(p1.y,p2.y) and p3.y <=max(p1.y,p2.y)):







                



                if((p4.x-p1.x)*(p2.y-p1.y)-(p4.y-p1.y)*(p2.x-p1.x)==0 and 







                   p4.x >= min(p1.x,p2.x) and p4.x <= max(p1.x,p2.x) and 



                   p4.y >= min(p1.y,p2.y) and p4.y <=max(p1.y,p2.y)):



                    return p3,p4



                else:



                    return p3,0            



            if((p4.x-p1.x)*(p2.y-p1.y)-(p4.y-p1.y)*(p2.x-p1.x)==0 and 



                   p4.x >= min(p1.x,p2.x) and p4.x <= max(p1.x,p2.x) and 



                   p4.y >= min(p1.y,p2.y) and p4.y <=max(p1.y,p2.y)):



                if((p3.x-p1.x)*(p2.y-p1.y)-(p3.y-p1.y)*(p2.x-p1.x)==0 and 



                  p3.x >= min(p1.x,p2.x) and p3.x <= max(p1.x,p2.x) and 



                  p3.y >= min(p1.y,p2.y) and p3.y <=max(p1.y,p2.y)):



                    return p3,p4



                else:



                    return p4,0



            if((p1.x-p3.x)*(p4.y-p3.y)-(p1.y-p3.y)*(p4.x-p3.x)==0 and 



               p1.x >= min(p3.x,p4.x) and p1.x <= max(p3.x,p4.x) and 



               p1.y >= min(p3.y,p4.y) and p1.y <=max(p3.y,p4.y)):







                if((p2.x-p3.x)*(p4.y-p3.y)-(p2.y-p3.y)*(p4.x-p3.x)==0 and 



                  p2.x >= min(p3.x,p4.x) and p2.x <= max(p3.x,p4.x) and 



                  p2.y >= min(p3.y,p4.y) and p2.y <=max(p3.y,p4.y)):



                    return p1,p2



                else:



                    return p1,0



            if((p2.x-p3.x)*(p4.y-p3.y)-(p2.y-p3.y)*(p4.x-p3.x)==0 and 



                  p2.x >= min(p3.x,p4.x) and p2.x <= max(p3.x,p4.x) and 



                  p2.y >= min(p3.y,p4.y) and p2.y <=max(p3.y,p4.y)):







                if((p1.x-p3.x)*(p4.y-p3.y)-(p1.y-p3.y)*(p4.x-p3.x)==0 and 



                  p1.x >= min(p3.x,p4.x) and p1.x <= max(p3.x,p4.x) and 



                  p1.y >= min(p3.y,p4.y) and p1.y <=max(p3.y,p4.y)):



                    return p1,p2                



                else:



                    return p2,0



            return 0,0  



        else:



            xnum=((x1*y2-x2*y1)*(x3-x4)-(x1-x2)*(x3*y4-x4*y3))



            xden=((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4))



            ynum=((x1*y2-x2*y1)*(y3-y4)-(y1-y2)*(x3*y4-x4*y3))



            yden=((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4))



            if(xden !=0 and yden !=0):



                xcoor=xnum/xden



                ycoor=ynum/yden  



                # return xcoor,ycoor



                return Point(xcoor,ycoor),0



            else:



                return 0,0    



    else:



        return 0,0







def input(array):







    if(re.compile(r' *a +\" *([A-Za-z]+ *[A-Za-z]*)+ *\" +( *\([-]?[0-9]+,[-]?[0-9]+\))+( *\([-]?[0-9]+,[-]?[0-9]+\)) *$').match(array)):



        cmp=[]



        key1=re.findall(r'[^""]+',array)[1].lower()



        key=key1.lower()



        value=re.findall('\((.*?)\)',array)



        cmp=graph.values()



        if(graph.has_key(key)):



            raise Exception("Error: Command Error in line {0}\nThe Street already exists".format(array))



        elif(value in cmp):



            raise Exception("Error: Content Error in line {0}\nParts or entirety of two streets should not completely overlap.".format(array))



        else:



            number=re.compile(r'-?\d+')



            pointgroup=[]



            for i in range(0,len(value)):



                p=number.findall(value[i])



                x1=p[0]



                y1=p[1]



                p1=Point(x1,y1)



                if (p1 in pointgroup):



                    raise Exception("Error: Cotent Error in line {0}\nThere is no circle in a street".format(array))



                else:



                    pointgroup.append(p1)



            graph[key]=value



    elif(re.compile(r' *g *$').match(array)):



        vertex(graph)



    elif(re.compile(r' *c +\" *([A-Za-z]+ *[A-Za-z]*)+ *\"( *\([-]?[0-9]+,[-]?[0-9]+\))+( *\([-]?[0-9]+,[-]?[0-9]+\)) *$').match(array)):



        key2=re.findall(r'[^""]+',array)[1]



        key=key2.lower()



        value=re.findall('\((.*?)\)',array)



        if(graph.has_key(key)):



            graph[key]=value



        else:



            raise Exception("Error: Command Error in line {0}\nThe Street doesn't exist".format(array))



    elif(re.compile(r' *r +\" *([A-Za-z]+ *[A-Za-z]*)+ *\" *$').match(array)):



        key3=re.findall(r'[^""]+',array)[1]



        key=key3.lower()



        if(graph.has_key(key)):



            graph.pop(key)



        else:



            raise Exception("Error: Command Error in line {0}\nThe Street doesn't exist".format(array))



    else:



        raise Exception("Error: Format Error in line {0}".format(array))



    



def vertex(dic):



    # connect vertexs and give all segements



    import re



    nums=re.compile(r'-?\d+')







    lineset={}



    for key in dic:



        linegroup=[]



        for i in range(1,len(dic[key])):



            p=nums.findall(dic[key][i])



            q=nums.findall(dic[key][i-1])



            x1=p[0]



            y1=p[1]



            x2=q[0]



            y2=q[1]



            p1=Point(x1,y1)



            p2=Point(x2,y2)



            linegroup.append(Line(p1,p2))



        lineset[key]=linegroup







    vertexgroup=[]



    intersectgroup=[]



    for j in lineset:



        for p in range(len(lineset[j])):



            for m in lineset:



                if(j !=m ):



                    for q in range(len(lineset[m])):



                        inter,inter2=(intersect(lineset[j][p],lineset[m][q]))



                        # print inter



                        if(inter !=0 ):



                            if(lineset[j][p].src not in vertexgroup):



                                vertexgroup.append(lineset[j][p].src)



                            if(lineset[j][p].dst not in vertexgroup):



                                vertexgroup.append(lineset[j][p].dst)



                            if(lineset[m][q].src not in vertexgroup):



                                vertexgroup.append(lineset[m][q].src)



                            if(lineset[m][q].dst not in vertexgroup):



                                vertexgroup.append(lineset[m][q].dst)



                            if(inter2 !=0):



                                if(inter not in vertexgroup):



                                    vertexgroup.append(inter)



                                if(inter not in intersectgroup):



                                    intersectgroup.append(inter)



                                if(inter2 not in vertexgroup):



                                    vertexgroup.append(inter2)



                                if(inter2 not in intersectgroup):



                                    intersectgroup.append(inter2)



                            else:   



                                if(inter not in vertexgroup):



                                    vertexgroup.append(inter)



                                if(inter not in intersectgroup):



                                    intersectgroup.append(inter)



                        else:



                            pass



                



    V={}



    #print ('V={')

    #print ('V %d'%(len(vertexgroup)))

    sys.stdout.write('V %d\n'%(len(vertexgroup)))

    for i in range(len(vertexgroup)):



        # V[i]=str(vertexgroup[i])



        V[str(vertexgroup[i])]=i



        #print ('{}:{}'.format(i,str(vertexgroup[i])))



    #print ('}')



    



    E=[]



    # for i in range(0,len(linegroup)):



    for i in lineset:



        for p in range(len(lineset[i])):



            c=0



            temp=[]



            for j in range(0,len(intersectgroup)):



                x3=intersectgroup[j].x



                y3=intersectgroup[j].y



                p1=lineset[i][p].src



                p2=lineset[i][p].dst



                p3=Point(x3,y3)



                if((p3.x-p1.x)*(p2.y-p1.y)-(p3.y-p1.y)*(p2.x-p1.x)<0.01 and 



                    p3.x >= min(p1.x,p2.x) and p3.x <= max(p1.x,p2.x) and 



                    p3.y >= min(p1.y,p2.y) and p3.y <=max(p1.y,p2.y)):



                    c+=1



                    if(intersectgroup[j] not in temp):



                        temp.append(intersectgroup[j])



        # for a in range(len(temp)):



            # print temp[a]



            if c == 1:



                if(str(lineset[i][p].src) == str(temp[0])):



                    E.append(Edge(V[str(lineset[i][p].dst)],V[str(temp[0])]))



                elif str(lineset[i][p].dst) == str(temp[0]):



                    E.append(Edge(V[str(lineset[i][p].src)],V[str(temp[0])]))



                else:



                    E.append(Edge(V[str(lineset[i][p].src)],V[str(temp[0])]))



                    E.append(Edge(V[str(lineset[i][p].dst)],V[str(temp[0])]))



            if c > 1:



                count=0



                minix=lineset[i][p].src.x-lineset[i][p].dst.x



                miniy=lineset[i][p].src.y-lineset[i][p].dst.y



                minidis=math.sqrt(math.pow(minix,2)+math.pow(miniy,2))







            #connect one end with the nearest intersection



                for q in range(0,len(temp)): 



                    disx1=lineset[i][p].src.x-temp[q].x



                    disy1=lineset[i][p].src.y-temp[q].y



                    dis1=math.sqrt(math.pow(disx1,2)+math.pow(disy1,2))



                    if minidis > dis1:  



                        minidis=dis1 



                        count=q



                if(str(lineset[i][p].src)==str(temp[count])):



                    pass



                else:



                    E.append(Edge(V[str(lineset[i][p].src)],V[str(temp[count])]))



 



            #connect the other end with the nearest intersection



                minidis=math.sqrt(math.pow(minix,2)+math.pow(miniy,2))



                for q in range(0,len(temp)): 



                    disx2=lineset[i][p].dst.x-temp[q].x



                    disy2=lineset[i][p].dst.y-temp[q].y



                    dis2=math.sqrt(math.pow(disx2,2)+math.pow(disy2,2))



                    if minidis > dis2:  



                        minidis=dis2 



                        count=q



                if(str(lineset[i][p].dst)==str(temp[count])):



                    pass



                else:



                    E.append(Edge(V[str(lineset[i][p].dst)],V[str(temp[count])]))







            #connect intersections with the nearest one



                for q in range(0,len(temp)):



                    minidis=math.sqrt(math.pow(minix,2)+math.pow(miniy,2))



                    for p in range(0,len(temp)):



                        if(p != q ):



                            disx=temp[p].x-temp[q].x



                            disy=temp[p].y-temp[q].y



                            dis=math.sqrt(math.pow(disx,2)+math.pow(disy,2))



                            if (minidis >= dis):  



                                minidis=dis 



                                count=p



                    if(Edge(V[str(temp[q])],V[str(temp[count])]) not in E and



                        Edge(V[str(temp[count])],V[str(temp[q])]) not in E):



                        E.append(Edge(V[str(temp[q])],V[str(temp[count])]))

    length = 0

    #print 'E={',

    sys.stdout.write('E={')

    for k in range(len(E)):

        length+=1;

        #print ('%s'%E[k]),

        sys.stdout.write('%s'%E[k])

        if(length != len(E)):

            sys.stdout.write(',')

    sys.stdout.write('}\n')

    sys.stdout.flush()

    #print ('}')



    



def main():







    while True:



        # line = sys.stdin.readline().strip('\n')



        line = sys.stdin.readline()



        if line == '':



            break



        try:



            input(line)



        except Exception as e:



            sys.stderr.write(str(e)+"\n")        



    # return exit code 0 on successful termination



    sys.exit(0)







if __name__ == '__main__':



    main()
