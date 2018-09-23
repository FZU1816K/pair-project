//package ccx;
import java.io.*;import java.net.*;import java.util.regex.*;
public class Main
{
	static String f(String u)throws Exception
	{
InputStream in=new URL
("http://openaccess.thecvf.com/"+u)
.openConnection().getInputStream();
String s="";int l;byte[]b=new byte[8192];
for(;(l=in.read(b))!=-1;)s+=new String(b,0,l);
return s;
	}
	public static void main(String[]S)throws Exception
	{
PrintWriter o=new PrintWriter("result.txt");
//<dt class="ptitle"><br><a href="content_cvpr_2018/html/Das_Embodied_Question_Answering_CVPR_2018_paper.html">Embodied Question Answering</a></dt>
Matcher m=Pattern.compile
("ptitle.*?href=\"(.*?)\"").matcher(f("CVPR2018.py"));
int i;for(i=0;m.find();i++)
{
//<div id="papertitle">Embodied Question Answering</div>
//<div id="abstract" >...</div>
	Matcher m2=Pattern.compile
	("(?s)papertitle\">\\s*(.*?)<.*abstract\" >\\s*(.*?)<")
	.matcher(f(m.group(1)));
	m2.find();o.println(i+"\nTitle: "+m2.group(1)
	+"\nAbstract: "+m2.group(2)+"\n\n");
	System.out.println(i);
}
o.close();System.out.println("ok");
	}
}
