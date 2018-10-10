import java.util.*;
import java.util.Map.*;
import java.io.*;
import java.util.regex.*;
public class Main
{
	static String fileIn="",fileOut="";
	static int weight=0,m=1,n=10,i,j,lines=0,words=0,chars=-1;
	static DataInputStream dataInputStream;
	static Map<String,Integer>map=new TreeMap<String,Integer>();
	public static void main(String args[])throws Exception
	{
	input_scan(args);
	mat();
	List<Entry<String,Integer>>list=new ArrayList<Entry<String,Integer>>(map.entrySet());
	Collections.sort(list,new Comparator<Entry<String,Integer>>()
	{
		public int compare(Entry<String,Integer>e1,Entry<String,Integer>e2)
		{
		if(e1.getValue().equals(e2.getValue()))
			return e1.getKey().compareTo(e2.getKey());
		return e2.getValue().compareTo(e1.getValue());
		}
	});
	PrintWriter printWriter=new PrintWriter(fileOut);
	printWriter.println("characters: "+chars+"\nwords: "+words+"\nlines: "+lines);
	for(i=0;i<Math.min(n,list.size());i++)
		printWriter.println("<"+list.get(i).getKey()+">: "+list.get(i).getValue());
	printWriter.close();dataInputStream.close();
	}
	static void input_scan(String args[])
	{
	if(args.length==1){fileIn=args[0];}
	else
	{
	for(i=1;i<args.length;i+=2)
	{
	String s=args[i-1];
	if("-i".equals(s))fileIn=args[i];
	else if("-o".equals(s))fileOut=args[i];
	else if("-w".equals(s))weight=Integer.parseInt(args[i]);
	else if("-m".equals(s))m=Integer.parseInt(args[i]);
	else if("-n".equals(s))n=Integer.parseInt(args[i]);
	}
	}
	}
	@SuppressWarnings("deprecation")
	static void mat()throws Exception
	{
	String str;
	dataInputStream=new DataInputStream(new FileInputStream(fileIn));
	for(;(str=dataInputStream.readLine())!=null;)
	{
	Matcher matcher=Pattern.compile("(Title|Abstract): (.*)").matcher(str);
	int help=0;
	if(matcher.find())
	{
	if(str.matches("Title: .*"))help=1;
	lines++;str=matcher.group(2).toLowerCase();chars+=1+str.length();
	matcher=Pattern.compile("(.*?)[a-z]{0,3}[0-9]+.*?[^a-z0-9]").matcher(str+" 1 ");
	for(;matcher.find();)
	{
	Matcher matcher2=Pattern.compile("([a-z]{4}[a-z0-9]*)([^a-z0-9]+)").matcher(matcher.group(1));
	List<String>list=new ArrayList<String>(),list2=new ArrayList<String>();
	for(;matcher2.find();words++)
	{
	list.add(matcher2.group(1));
	list2.add(matcher2.group(2));
	}
	for(i=0;i<=list.size()-m;i++)
	{
	for(str=list.get(i),j=0;j<m-1;j++)
		str+=list2.get(i+j)+list.get(i+j+1);
	j=1+9*weight*help;
	if(!map.containsKey(str))map.put(str,j);
	else map.put(str,map.get(str)+j);
	}
	}
	}
	}
	}
}