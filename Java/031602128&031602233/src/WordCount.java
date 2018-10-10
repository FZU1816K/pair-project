//package test1;


import java.io.*;
import java.util.*;

public class WordCount {
    private static String content = new String();
    private static Map  ma= new HashMap();
    private static Map  mb= new HashMap();
    private static List<HashMap.Entry<String, Integer>> words = null;
    private static List<HashMap.Entry<String, Integer>> phrases = null;
    private static boolean use_quan = false;
    public static void set_quan(boolean a){
    	use_quan = a;
    }
    public static List<HashMap.Entry<String, Integer>> getWords() {
        return words;
    }
    public static List<HashMap.Entry<String, Integer>> getPharses() {
        return phrases;
    }

    public WordCount(File fileIn) {
        try{
            //读取文件
            BufferedReader bf = new BufferedReader(new InputStreamReader(new FileInputStream(fileIn),"utf8"));
            StringBuffer contents = new StringBuffer();
            int byte_char = -1;
            //开始依次读取字节码
            while ((byte_char = bf.read()) >= 0) {
                contents.append((char)byte_char);
            }
            content = contents.toString();
            bf.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }



    public int getcharnum(){
        String s = content.replaceAll("\r\n","\n");
        int charnum = s.length();
        return charnum;
    }


    public int getlinenum(){
        Boolean flag = false;
        int linenum = 0 , i = 0;
        for (;i<content.length();i++){
            if(content.charAt(i) != '\r' && content.charAt(i) != '\n' && content .charAt(i) != ' ' ){
                flag = true;
            }else if(content.charAt(i) == '\n'){
                if(flag){
                    linenum++;
                    flag = false;
                }
            }
        }
        if(flag) linenum++;
        return linenum;
    }

    public int getwordnum(){
        int wordnum = 0;
        String zzbds = "[^0-9A-Za-z]";
        String contentString  = content.toLowerCase().replaceAll(zzbds,"|");
        String[] contents = contentString.split("\\|");
        int i = 0,quan=1;
        for (; i <contents.length ; i++ ) {
            if(contents[i].length()>=4){
                if(Character.isLetter(contents[i].charAt(0))){
                    if(Character.isLetter(contents[i].charAt(1))){
                        if(Character.isLetter(contents[i].charAt(2))){
                            if(Character.isLetter(contents[i].charAt(3))){
                                //System.out.println(contents[i]);
                            	if(contents[i].equals("title")){
                                	if(use_quan) quan=10;
                                	continue;
                                }else if(contents[i].equals("abstract")){
                                	if(use_quan) quan=1;
                                	continue;
                                }
                            	wordnum++;
                                Maps(ma,contents[i],quan );
                            }
                        }
                    }
                }
            }
        }
        if(!ma.isEmpty()){
            words = Sort(ma);
        }
        return wordnum;
    }
    public int getphrasenum(int gs) {
    	if(gs == 0) return -1;
    	int phrasenum = 0;
    	String temp;
    	String[] contents1 = content.split("[^0-9A-Za-z]");
    	
    /*	String[] contents2 = null;
    	int pos = 0;
    	for(int i = 0; i < contents1.length - gs; i++) {
    		pos += contents1[i].length();

			System.out.println(pos);
    		temp = "";
    		while(true) {
    			System.out.println(content.charAt(pos));
    			
    			temp += content.charAt(pos); pos++;
    			if(content.charAt(pos) == (contents1[i + 1].charAt(0))) break;
    		}
    		contents2[i] = temp;
    	}*/
    	
    	
    	for(int i = 0; i < contents1.length - gs; i++) {
    		int flag = 1;
			if(contents1[i].equals("Abstract") || contents1[i].equals("Title")) continue;
			temp = "";
    		for(int j = 0; j < gs; j++) {
    			if(contents1[i + j].length()>=4){
                    if(Character.isLetter(contents1[i + j].charAt(0))){
                        if(Character.isLetter(contents1[i + j].charAt(1))){
                            if(Character.isLetter(contents1[i + j].charAt(2))){
                                if(Character.isLetter(contents1[i + j].charAt(3))){
                                	temp += contents1[i + j];
                                	if(j != gs - 1) temp += " ";
                                	continue;
                                }
                            }
                        }
                    }
    			}
    			flag = 0;
    		}
    		if(flag == 1) {
    			if(mb.containsKey(temp)) {
    				int x = (int)mb.get(temp);
    				mb.put(temp, x + 1);
    				phrasenum++;
    			}
    			else mb.put(temp, 1);
    		}
    	}
    	if(!mb.isEmpty()) phrases = Sort(mb);
    	return phrasenum;
    }
    
    //更新字典的函数
    public static Map Maps(Map m, String s,int t){
        if(m.containsKey(s)){
            int n = (int)m.get(s);
            n+=t;
            m.put(s,n);
        }else{
            m.put(s,t);
        }
        return m;
    }

    //单词排序
    public static List<HashMap.Entry<String, Integer>> Sort(Map m){
        List<HashMap.Entry<String, Integer>> wordList = new ArrayList<HashMap.Entry<String, Integer>>(m.entrySet());

        Comparator<Map.Entry<String, Integer>> com = new Comparator<Map.Entry<String, Integer>>(){
            @Override
            public int compare(Map.Entry<String, Integer> o1, Map.Entry<String, Integer> o2) {
                if(o1.getValue()==o2.getValue())
                    return o1.getKey().compareTo(o2.getKey());//出现次数相等按字典序
                return o2.getValue()-o1.getValue();//否者按照字典序排序
            }
        };
        wordList.sort(com);
        return wordList;
    }


}