import org.apache.http.impl.client.BasicResponseHandler;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.util.ArrayList;

import org.apache.http.HttpEntity;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

public class SpiderMain {

    /**
     * 取出pdf_link 数组
     * @return
     */

    public static void main(String[] args) {
        StringBuilder t = new StringBuilder();
        try {
            String url = "http://openaccess.thecvf.com/CVPR2018.py";

            CloseableHttpClient client = HttpClients.createDefault();
            HttpGet httpget = new HttpGet(url);
            String response = client.execute(httpget, new BasicResponseHandler());

            Document document = Jsoup.parse(response);

            Elements ptitles = document.getElementsByClass("ptitle");
            ArrayList<String> links = new ArrayList<>();
            String link = "http://openaccess.thecvf.com/";
            StringBuilder str = new StringBuilder();  // 用来拼接 url字符串 http://openaccess.thecvf.com/content_cvpr_2018/html/Das_Embodied_Question_Answering_CVPR_2018_paper.html
            for(Element ptitle: ptitles){
                str.append(link);
                str.append(ptitle.getElementsByTag("a").attr("href"));
                links.add(str.toString());
                // 清空StringBuilder
                str.delete(0,str.length());
            }

            int i = 0 ;
            // div id = papertitle 标题； div id = abstract 摘要
            for(String paper: links){
                Document doc = Jsoup.connect(paper).get();
                String title = doc.select("div#papertitle").first().text();
                String abstr = doc.select("div#abstract").first().text();
                t.append(i);
                t.append("\n");
                t.append("Title: ");
                t.append(title);
                t.append("\n");
                t.append("Abstract: ");
                t.append(abstr);
                //拼接pdf链接
//                t.append("\n");
//                t.append("PDF_Link: ");
//                t.append(paper.replaceAll("/html","/papers").replaceAll(".html",".pdf"));
                if(i<links.size()-1){
                    t.append("\n");
                    t.append("\n");
                    t.append("\n");
                }
                System.out.println(i);
                //System.out.println("Title:" + title);
                //System.out.println("Abstract:" + abstr);
                //System.out.println("=================================");
                i++;
            }
        }catch (Exception e){
            e.printStackTrace();
        }
        System.out.println("爬虫结束，开始输出！");

        try{
            BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream("result.txt"));

            bos.write(t.toString().getBytes());
            bos.close();
            System.out.println("输出完毕！");

        }catch (Exception e){
            System.out.println("文本写出失败！");
            System.out.println(e.getMessage());
        }
    }
}
