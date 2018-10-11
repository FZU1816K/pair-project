
import org.omg.Messaging.SYNC_WITH_TRANSPORT;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;



public class FileRead {

    ArrayList<String> titles = new ArrayList<String>();
    ArrayList<String> abstracts = new ArrayList<String>();
    ArrayList<String> PDFLink = new ArrayList<>();

    /**
     * 取出titles数组
     * @return titles
     */
    public ArrayList<String> getTitles(){
        return titles;
    }

    /**
     * 取出abstracts数组
     * @return abstracts
     */
    public ArrayList<String> getAbstracts(){
        return abstracts;
    }

    /**
     * 取出pdf_link 数组
     * @return
     */
    public ArrayList<String> getPDFLink() { return PDFLink;}
    /**
     * 文本读入
     * @param file
     */
    public String Input(File file){

        try{
            InputStreamReader isr = new InputStreamReader(new FileInputStream(file), "utf-8");
            BufferedReader in = new BufferedReader(isr);
            StringBuilder str = new StringBuilder();

            titles.clear();
            abstracts.clear();
            PDFLink.clear();

            int c_byte = 0;
            while((c_byte = in.read()) != -1){
                str.append((char) c_byte);

                if((char)c_byte == '\n'){
                    if(str.toString().charAt(0)=='T' && str.toString().charAt(1)=='i' && str.toString().charAt(2)=='t'){
                        str.delete(0,7);
                        titles.add(str.toString());
                    }else if(str.toString().charAt(0)=='A'){
                        str.delete(0,10);
                        abstracts.add(str.toString());
                    }else if(str.toString().charAt(0)=='P'){
                        str.delete(0,10);
                        PDFLink.add(str.toString());
                    }
                    str.delete(0,str.toString().length());
                }
            }
            //如果末尾是abstract abstract数组add,如果末尾是pdflink pdflink数组add
            if(str.toString().charAt(0)=='A'){
                str.delete(0,10);
                abstracts.add(str.toString());
            }
            if(str.toString().charAt(0)=='P'){
                str.delete(0,10);
                PDFLink.add(str.toString());
            }

            in.close();
            return str.toString();
        }catch (Exception e){
                    System.out.println("文本读入失败！<error> :" + e.getMessage());
        }
        return "";
    }

    /**
     * 文本写出
     * @param length
     * @param wordAmount
     * @param lines
     * @param wList
     */
    public void Output(int length, int wordAmount, int lines, List<HashMap.Entry<String, Integer>> wList,String out,int n){

        try{
            FileOutputStream res = new FileOutputStream(out);
            BufferedOutputStream bos = new BufferedOutputStream(res);
            String t = "characters: " + length +"\r\n"
                    +"words: " + wordAmount +"\r\n"
                    +"lines: " + lines +"\r\n";
            int count = 0;
            for(HashMap.Entry<String,Integer> entry:wList){
                count++;
                t += "<"+entry.getKey() + ">: " + entry.getValue();
                if(count<=n-1){
                    t += "\r\n";
                }else{
                    break;
                }
            }
            bos.write(t.getBytes(),0,t.getBytes().length);
            bos.flush();
            bos.close();
        }catch (Exception e){
            System.out.println("文本写出失败！");
            System.out.println(e.getMessage());
        }
    }
    public void Write(String st, String name){
        try{
            FileOutputStream res = new FileOutputStream(name);
            BufferedOutputStream bos = new BufferedOutputStream(res);

            bos.write(st.getBytes(),0,st.getBytes().length);
            bos.flush();
            bos.close();
        }catch (Exception e){
            System.out.println("文本写出失败！");
            System.out.println(e.getMessage());
        }
    }
}
