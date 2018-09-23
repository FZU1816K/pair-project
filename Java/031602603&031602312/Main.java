//package ccx;
import java.util.*;import java.util.Map.*;import java.io.*;
import java.util.regex.*;
public class Main
{
	@SuppressWarnings({ "deprecation", "unchecked" })
	public static void main(String[]S)throws Exception
	{
String fi="",fo="";int w0=0,m0=1,n0=10,i,j;
if(S.length==1){fi=S[0];}
else
{
	//从1开始，所以奇数个参数时不会去看最后1个参数
	for(i=1;i<S.length;i+=2)
	{
if(S[i-1].equals("-i"))fi=S[i];
else if(S[i-1].equals("-o"))fo=S[i];
else if(S[i-1].equals("-w"))w0=Integer.parseInt(S[i]);
else if(S[i-1].equals("-m"))m0=Integer.parseInt(S[i]);
else if(S[i-1].equals("-n"))n0=Integer.parseInt(S[i]);
	}
}
DataInputStream in=new DataInputStream
(new FileInputStream(fi));
Map<String,Integer>t=new TreeMap();
String s;int n=0,w=0,c=-1;
for(;(s=in.readLine())!=null;)
{
	Matcher m=Pattern.compile
	("(Title|Abstract): (.*)").matcher(s);
	int f=0;if(m.find())
	{
if(s.matches("Title: .*"))f=1;
n++;s=m.group(2);c+=1+s.length();
m=Pattern.compile
("([a-zA-Z]{4}[a-zA-Z0-9]*)([^a-zA-Z0-9]+)")
.matcher(s+" ");
List<String>l=new ArrayList(),l2=new ArrayList();
for(;m.find();w++){l.add(m.group(1));l2.add(m.group(2));}
for(i=0;i<=l.size()-m0;i++)
{
	for(s=l.get(i),j=0;j<m0-1;j++)s+=l2.get(i+j)+l.get(i+j+1);
	j=1+9*w0*f;if(!t.containsKey(s))t.put(s,j);
	else t.put(s,t.get(s)+j);
}
	}
}
List<Entry<String,Integer>>l=new ArrayList(t.entrySet());
Collections.sort(l,new Comparator<Entry<String,Integer>>()
{
	public int compare(Entry<String,Integer>i
	,Entry<String,Integer>j)
	{
int k=j.getValue().compareTo(i.getValue());
if(k==0)return -j.getKey().compareTo(i.getKey());
return k;
	}
});
PrintWriter o=new PrintWriter(fo);
o.println("characters: "+c+"\nwords: "+w+"\nlines: "+n);
for(i=0;i<Math.min(n0,l.size());i++)
o.println("<"+l.get(i).getKey()+">: "+l.get(i).getValue());
o.close();
	}
}