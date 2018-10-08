
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class Main {

	public static void main(String[] args) {
		String rooturl = "http://openaccess.thecvf.com/CVPR2018.py";
		getContent(rooturl);
	}

	private static void getContent(String rooturl) {
		// TODO Auto-generated method stub
		try {
			File file = new File("cvpr\\result.txt");
			BufferedWriter bufferedWriter= new BufferedWriter(new FileWriter(file));
			org.jsoup.nodes.Document document = Jsoup.connect(rooturl).maxBodySize(0)
												.timeout(1000000)
												.get();
			Elements elements =  document.select("[class=ptitle]");
			Elements hrefs = elements.select("a[href]");
			int count = 0;
			for(Element element:hrefs) {
				String url = element.absUrl("href");
				org.jsoup.nodes.Document documrnt2 = Jsoup.connect(url).maxBodySize(0)
													.timeout(1000000)
													.get();
				Elements elements2 = (Elements) documrnt2.select("[id=papertitle]");
				String title = elements2.text();
				if(count != 0)
					bufferedWriter.write("\r\n" + "\r\n" + "\r\n");
				bufferedWriter.write(count + "\r\n");
				bufferedWriter.write("Title: " + title + "\r\n");
				Elements elements3 = (Elements) documrnt2.select("[id=abstract]");
				String Abstract = elements3.text();
				bufferedWriter.write("Abstract: " + Abstract);
				count++;
			}
			bufferedWriter.close();
		}catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}
}
