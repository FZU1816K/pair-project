
import java.io.File;
import java.io.PrintWriter;
import java.io.FileWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.util.ArrayList;


import java.util.Scanner;

public class Main {

    //资源所在的网页地址
    private static String resourceURL = "http://openaccess.thecvf.com/CVPR2018.py";
    private static int count=-1;

    public static void main(String[] args) throws IOException {
        //从一个网站获取和解析一个HTML文档
        Document document = Jsoup.connect(resourceURL).get();
        //获取所有的连接
        Elements elements = document.select("a[href]");
        PrintWriter printWriter =new PrintWriter(new FileWriter("E:/result.txt",true),true);//第二个参数为true，从文件末尾写入 为false则从开
        for(Element element : elements) {
            //筛选论文链接
            if (element.attr("abs:href").endsWith(".html")) {
                count=count+1;
                String paperUrl = element.attr("abs:href");
                System.out.println(paperUrl);
                Document paperDoc = Jsoup.connect(paperUrl).get();
                printWriter.println(count);
                System.out.println(count);
                //打印论文标题
                Elements paperTitles = paperDoc.select("#papertitle");
                for(Element paperTitle : paperTitles) {
                    System.out.println(paperTitle.text());
                    printWriter.println("Title: "+paperTitle.text());
                }
                //打印论文摘要
                Elements paperAbs = paperDoc.select("#abstract");
                for(Element paperAbstract : paperAbs) {
                    System.out.println(paperAbstract.text());
                    printWriter.println("Abstract: "+paperAbstract.text());
                }
                printWriter.println("\n");
                printWriter.println("\n");
            }

        }
        printWriter.close();//关闭输入流
    }

}
