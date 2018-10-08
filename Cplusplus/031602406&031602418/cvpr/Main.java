package cpvrpaper;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class CpvrPaper {

	public static void getContent(String URL)
	{
		try 
		{
			File file = new File("C:\\Users\\Administrator\\Desktop\\课程\\软件工程\\result1.txt");
			BufferedWriter bi = new BufferedWriter(new FileWriter(file));
			Document document1 = Jsoup.connect(URL)
					.maxBodySize(0)
					.timeout(600000)
					.get();
			Elements element3 = document1.select("[class=ptitle]");
			Elements hrefs = element3.select("a[href]");
			long count = 0;
			for(Element element6:hrefs)
			{
				String url = element6.absUrl("href");
				Document document2 = Jsoup.connect(url)
						.maxBodySize(0)
						.timeout(600000)
						.get();
				Elements elements1 = document2.select("[id=papertitle]");
				String title = elements1.text();
				bi.write(count+"\r\n");
				bi.write("Title: "+title+"\r\n");
				Elements elements2 = document2.select("[id=abstract]");
				String abstract1 = elements2.text();
				bi.write("Abstract: "+abstract1+"\r\n"+"\r\n"+"\r\n");
				count++;
			}
			bi.close();
		}catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	public static void main(String[] args) throws IOException
	{
		String url = "http://openaccess.thecvf.com/CVPR2018.py";
		getContent(url);
	}
}
