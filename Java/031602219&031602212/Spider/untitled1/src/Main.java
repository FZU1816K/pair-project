



import java.io.IOException;


import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.HashSet;





public class Main {

    public static void main(String[] args) throws IOException {
        Document document = Jsoup.connect("http://openaccess.thecvf.com/CVPR2018.py").timeout(50000).maxBodySize(0).get();
        Elements mainPage= document.select("dt.ptitle");

	    int t=mainPage.size();
        System.out.println("一共有"+ t +"篇论文");

        Elements urlLink=mainPage.select("a[href^=content_cvpr_2018/html/]");
          int size=urlLink.size();
          int paperid= -1;



        PrintStream ps = new PrintStream("e:/details.txt");   //输出流txt
        System.setOut(ps);




        for(Element paper:urlLink) {                                    //循环爬取url队列
             String URL = paper.attr("href");
             if(!URL.contains("https://")){
                URL = "openaccess.thecvf.com/"+URL;
			}


            Document doc = Jsoup.connect("http://"+URL).timeout(80000).maxBodySize(0).get();
			Elements paperdatas=doc.select("#content");
			Elements title1=paperdatas.select("#papertitle");
            Elements abs=paperdatas.select("#abstract");
            Elements authors = paperdatas.select("#authors");
            Elements opway = paperdatas.select("a[href]");


                String author=authors.select("b").text();
			    String title = title1.text();
			    paperid=paperid+1;
			    String abst=abs.text();
			    String openway=opway.text();


            System.out.println( paperid);
            System.out.println("Title: "+ title );
            System.out.println("Abstract: " +abst);
            System.out.println("Link: "+ URL);
            System.out.println("Month: June");
            System.out.println("Authors: "+ author);
            System.out.println("Relate: "+ openway);
            System.out.println("Relate link: ");
            for(Element linklink:opway) {
                String oplink = linklink.attr("href");
                System.out.println( "http://openaccess.thecvf.com/" + oplink);
            }


            System.out.println("\n");
            System.out.println("\n");
//            Set paperdatas=new HashSet();
//            ((HashSet) paperdatas).add(paperid);
//            ((HashSet) paperdatas).add(title);、
//            ((HashSet) paperdatas).add(authors);



		}







        System.out.println("////结束////");
    }

}
