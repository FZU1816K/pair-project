package PC;
import java.io.*;
import java.util.*;


public class Main {
    public static void main(String[] args) throws IOException {
    	String in_ads = "",out_ads = "";
    	boolean use_quan = false;
    	//�����в�������
    	for(int i=0;i<args.length;i+=2){
    		if(args[i].charAt(1)=='i'){
    			in_ads=args[i+1];
    		}else if(args[i].charAt(1)=='o'){
    			out_ads=args[i+1];
    		}else if(args[i].charAt(1)=='w' ){
    			System.out.println(args[i+1]);
    			if(args[i+1].charAt(0)=='1'){
    				use_quan = true;
    			}else use_quan =false;
    		}else {
    			System.out.println("�����ļ����󣡣�");
    			System.exit(0);
    		}
    	}
    	//���������ļ�������ļ�
        File fileIn = new File(in_ads);
        FileOutputStream fileOut = new FileOutputStream(out_ads);
        
        WordCount count = new WordCount(fileIn);//ʵ����WordCount��
        count.set_quan(use_quan);//�����Ƿ�ʹ�ô�Ȩ
        int charnum = count.getcharnum();//��ȡ�ַ���
        int wordnum = count.getwordnum();//��ȡ������
        int linenum = count.getlinenum();//��ȡ��Ч����
        List<HashMap.Entry<String, Integer>> m = count.getWords();
        String output="characters:"+charnum+"\r\n"+"words:"+wordnum+"\r\n" +"lines:"+linenum+"\r\n";
        String t = new String();
        if(m != null){
            if(m.size()!=0){
                for(int j=0;((j<10)&&(j<m.size()));j++){
                    t = "<"+ m.get(j).getKey() + ">:" + m.get(j).getValue();
                    output += t + "\r\n";
                }
            }
        }
        fileOut.write(output.getBytes());
        fileOut.close();
    }
}