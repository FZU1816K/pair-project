//package ccx;
import java.util.*;import java.util.Map.*;import java.io.*;
import java.util.regex.*;
public class Main
{
	@SuppressWarnings("deprecation")
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
Map<String,Integer>t=new TreeMap<String,Integer>();
String s;int n=0,w=0,c=-1;
for(;(s=in.readLine())!=null;)
{
	Matcher m=Pattern.compile
	("(Title|Abstract): (.*)").matcher(s);
	int f=0;if(m.find())
	{
if(s.matches("Title: .*"))f=1;
n++;s=m.group(2).toLowerCase();c+=1+s.length();
m=Pattern.compile("(.*?)[a-z]{0,3}[0-9]+.*?[^a-z0-9]")
.matcher(s+" 1 ");
for(;m.find();)
{
	Matcher m2=Pattern.compile
	("([a-z]{4}[a-z0-9]*)([^a-z0-9]+)")
	.matcher(m.group(1));
	List<String>l=new ArrayList<String>(),l2=new ArrayList<String>();
	for(;m2.find();w++)
	{l.add(m2.group(1));l2.add(m2.group(2));}
	for(i=0;i<=l.size()-m0;i++)
	{
for(s=l.get(i),j=0;j<m0-1;j++)s+=l2.get(i+j)+l.get(i+j+1);
j=1+9*w0*f;if(!t.containsKey(s))t.put(s,j);
else t.put(s,t.get(s)+j);
	}
}
	}
}
@SuppressWarnings({ "rawtypes", "unchecked" })
List<Entry<String,Integer>>l=new ArrayList(t.entrySet());
Collections.sort(l,new Comparator<Entry<String,Integer>>()
{
	public int compare(Entry<String,Integer>i
	,Entry<String,Integer>j)
	{
int k=-(i.getValue()-j.getValue());
if(k==0)return i.getKey().compareTo(j.getKey());
return k;
	}
});
PrintWriter o=new PrintWriter
//(System.out);
(fo);
o.println("characters: "+c+"\nwords: "+w+"\nlines: "+n);
for(i=0;i<Math.min(n0,l.size());i++)
o.println("<"+l.get(i).getKey()+">: "+l.get(i).getValue());
o.close();in.close();
	}
}