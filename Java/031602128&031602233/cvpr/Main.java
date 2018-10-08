package PC;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.select.Elements;
import org.jsoup.nodes.Element;
import static org.junit.Assert.assertEquals;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileWriter;
import org.junit.*;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

public class Main{
	public static String getHtmlByUrl(String url) throws IOException{  
        String html = null;  
        CloseableHttpClient httpClient = HttpClients.createDefault();//创建httpClient对象   
        HttpGet httpget = new HttpGet(url);
        try {  
            HttpResponse responce = httpClient.execute(httpget);
            int resStatu = responce.getStatusLine().getStatusCode();
            if (resStatu == HttpStatus.SC_OK) {
                  
                HttpEntity entity = responce.getEntity();  
                if (entity != null) {  
                    html = EntityUtils.toString(entity);//获得html源代码
                }  
            }  
        } catch (Exception e) {
            System.out.println("访问【"+url+"】出现异常!");  
            e.printStackTrace();  
        } finally {
            //释放连接
            httpClient.close();  
        }
        //System.out.println(html);
        return html;  
    }  

   public static void main(String []args)throws IOException{
	   String URL="http://openaccess.thecvf.com/CVPR2018.py";
	   String content= getHtmlByUrl(URL);
	   
	   //Document document = Jsoup.connect(URL).userAgent("Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; 360SE)").timeout(50000).post();
	   Document document = Jsoup.parse(content);
	   String num,left="dt.ptitle:nth-child(",right="a:nth-child(2)";
	   //System.out.println(doc.toString());
	   
	   int t=1,nb=0;
	   File f=new File("result.txt");
	   PrintWriter pw=new PrintWriter( new FileWriter(f,true) );
	   
	   //pw.write(document2.toString());
	   while(t<=2935){
		   num=t+"";
		   
		   Elements test=document.select(left+num+")" ).select(right);
		   
		   String str=test.text();
		   String url2=test.attr("href");
		   System.out.println("http://openaccess.thecvf.com/"+ url2);
		   Document document2 = Jsoup.connect("http://openaccess.thecvf.com/"+ url2).userAgent("Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0)").timeout(50000).get();
		   
		   Elements test2=document2.select("#abstract");
		   String str2=test2.text();
		   
			System.out.println("输出到第"+nb+"个");
			pw.write(""+nb);pw.write("\r\n");
			pw.write("Title: "+ str);pw.write("\r\n");
			pw.write("Abstract: "+str2);pw.write("\r\n\r\n\r\n");
			t+=3;nb++;
	   }
	   pw.close();
	   System.out.println("爬取完成");
   }
}


