import java.io.*;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main
{
	public static List<String> getPaperssByWeb() throws IOException
	{
		URL url=new URL("http://openaccess.thecvf.com/CVPR2018.py");
		BufferedReader bufr=new BufferedReader(new InputStreamReader(url.openStream()));
		String mail_regex = "<dt class=\"ptitle\"><br><a href=\"(.*?)\">";
		List<String> list=new ArrayList<String>();
		Pattern p = Pattern.compile(mail_regex);
		String line = null;
		while((line=bufr.readLine())!=null)
		{
			Matcher m = p.matcher(line);
			while(m.find()){
			   list.add(m.group(1));
			}
		}
		return list;   
	}

	public static void main(String[] args)
	{
		try{
			String head = "http://openaccess.thecvf.com/"; 
			List<String> list=getPaperssByWeb();
			File f = new File("result.txt");      
			if (!f.exists())
			{       
				f.createNewFile();      
			}      
			OutputStreamWriter write = new OutputStreamWriter(new FileOutputStream(f),"UTF-8");      
			BufferedWriter writer=new BufferedWriter(write); 
			int num = 0;	
			int flag = 0;
			for(String mail:list)
			{
				mail = head + mail;
				URL url=new URL(mail);
				System.out.println(mail);
				//System.out.println("\n");		
				BufferedReader bufred=new BufferedReader(new InputStreamReader(url.openStream(),"UTF-8"));				
				String title_regex = "<div id=\"papertitle\">\\n(.*?)</div>";
				String abstract_regex = "<div id=\"abstract\" >\\n(.*?)</div>";
				Pattern p = Pattern.compile(title_regex);
				Pattern q = Pattern.compile(abstract_regex);
				String line = null;
				String content = null;
				while((line=bufred.readLine())!=null)
				{
					content = content + line + "\n";
				}
				Matcher w = p.matcher(content);
				Matcher n = q.matcher(content);	
				if(w.find()&&n.find())
				{
					if(flag == 1)
					{
						writer.write("\n\n\n"); 
					}		
					flag = 1;					
					writer.write(String.valueOf(num));
					num++;
					writer.write("\nTitle: "); 
					writer.write(w.group(1)); 
					writer.write("\nAbstract: "); 
					writer.write(n.group(1)); 
				}
			}
			writer.close();
			System.out.println("finish!\n");		
		}
		catch(IOException err)
		{
			System.out.println("time out!\n");		
		}
	}
}

