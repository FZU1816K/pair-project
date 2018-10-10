
import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    private static String CVPR_URL = "http://openaccess.thecvf.com/CVPR2018.py";

    public static void main(String[] args) throws IOException {
        System.out.println("正在爬取论文，预计时间3分钟");
        htmlFilter(getHtmlData(CVPR_URL));
        System.out.println("论文爬取完成");
    }

    /**
     * @param urlString
     * @return
     * @throws IOException
     */
    public static String getHtmlData(String urlString) throws IOException {
        /* 建立GET请求 */
        URL url = new URL(urlString);
        HttpURLConnection httpURLConnection = (HttpURLConnection) url.openConnection();
        // httpURLConnection.setConnectTimeout(10000);
        // httpURLConnection.setReadTimeout(20000);
        httpURLConnection.setDoInput(true);
        httpURLConnection.setRequestMethod("GET");

        /* 获取输入流并读取 */
        InputStream inputStream = httpURLConnection.getInputStream();
        InputStreamReader inputStreamReader = new InputStreamReader(inputStream, "UTF-8");
        BufferedReader bufferedReader = new BufferedReader(inputStreamReader);

        /* 读取数据到stringBuilder */
        StringBuilder stringBuilder = new StringBuilder();
        String current = null;
        while ((current = bufferedReader.readLine()) != null) {
            stringBuilder.append(current);
        }

        /* 关闭连接和输入流 */
        bufferedReader.close();
        inputStreamReader.close();
        inputStream.close();
        httpURLConnection.disconnect();

        return (stringBuilder.toString());
    }

    /**
     * @param html
     * @throws IOException
     */
    public static void htmlFilter(String html) throws IOException {
        /* 数据存在dt class="ptitle">中间 */
        Pattern pattern = Pattern.compile("<dt class=\"ptitle\"><br><a href=\"([^\"]*)\">([^<]*)");
        Matcher matcher = pattern.matcher(html);
        File file = new File("result.txt");

        if (file.exists()) file.createNewFile();

        PrintWriter printWriter = new PrintWriter(
                new OutputStreamWriter(new FileOutputStream(file), "UTF-8"));

        int paperCount = 0;
        while (matcher.find()) {
            /* 获取论文Abstract */
            String paperAbstract = getPaperAbstract("http://openaccess.thecvf.com/" + matcher.group(1));

            printWriter.println(paperCount);
            /* 写入论文title */
            printWriter.println("Title: " + matcher.group(2));
            /* 写入论文Abstract */
            printWriter.println("Abstract: " + paperAbstract);
            /* 写入两个换行符 */
            printWriter.println();
            printWriter.println();

            System.out.print("爬取第" + String.valueOf(paperCount) + "篇完成\r");

            paperCount += 1;
        }
        System.out.println();
        printWriter.flush();
        printWriter.close();
    }

    public static String getPaperAbstract(String paperURL) throws IOException {
        String paperHtml = getHtmlData(paperURL);
        //Pattern pattern = Pattern.compile("<div id=\"abstract\" >([^<]*[^//])");
        Pattern pattern=Pattern.compile("<div id=\"abstract\" >(.*?)</div>");
        Matcher matcher = pattern.matcher(paperHtml);
        if (matcher.find()) {
            return matcher.group(1);
        }
        return null;
    }
}
