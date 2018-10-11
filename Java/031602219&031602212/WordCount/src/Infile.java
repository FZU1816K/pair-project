import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Writer;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Infile {

	public List<Map.Entry<String,Integer>> wordsmap = new ArrayList<Map.Entry<String,Integer>>();
	public Map<String,Integer> ver = new HashMap<String, Integer>();
	public int lines,characters,words;
	public void readfile(String path,int w,int m,int n) {
		
		int w_title,w_content;
		String strline = new String();
		String t_str = new String();
		String c_str = new String();
		StringBuilder t_words = new StringBuilder();
		StringBuilder c_words = new StringBuilder();
		String title_regex = "Title: (.+)";
		String content_regex = "Abstract: (.+)";
		
		try {
			FileInputStream file = new FileInputStream(path);	//构造文件流
			InputStreamReader reader = new InputStreamReader(file);		//文件流读取
			BufferedReader buffReader = new BufferedReader(reader);	
			w_title = w*10+(w-1)*(-1); w_content = 1; 
			lines=0; characters=0; words=0;
			Pattern t_pat = Pattern.compile(title_regex);
			Pattern c_pat = Pattern.compile(content_regex);
			while((strline = buffReader.readLine())!=null){
//				System.out.println(strline);
				Matcher t_mat = t_pat.matcher(strline);
				Matcher c_mat = c_pat.matcher(strline);
				if(t_mat.find()) {
					t_str=t_mat.group(1).toLowerCase();
					t_words.append(t_str).append(" ");
					phrase(t_str,w_title,m);
					characters += t_str.length()+1;
					lines++;
				}
				if(c_mat.find()) {
					c_str=c_mat.group(1).toLowerCase();
					c_words.append(c_str).append(" ");
					phrase(c_str,w_content,m);
					characters += c_str.length();
					lines++;
				}
			}
			buffReader.close();
			
			words = countwords(t_words.toString()+c_words.toString());
//			System.out.println("characters: " + characters);
//			System.out.println("words: " + words);
//			System.out.println("lines: " + lines);
//			for(int i=0;i<n;i++){
//				System.out.println("<"+wordsmap.get(i).getKey()+">: "+wordsmap.get(i).getValue());
//			}
//			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public int countwords(String str) {	
		List<String> wordslist = new ArrayList<String>();
		String regex ="[^0-9a-zA-Z]";	//剔除文本中的非字母和数字的部分并以！作为暂时的分隔符
		Pattern pat = Pattern.compile(regex);
		Matcher mat = pat.matcher(str);
		str = mat.replaceAll("!");				
		String [] textArray = str.split("!+");		//按照分隔符划分
		String v_regex = "^[a-z]{4}[a-z0-9]*$";		//对单词形式进行约定
		for(String i:textArray){
			Pattern v_pat = Pattern.compile(v_regex);
			Matcher v_mat = v_pat.matcher(i);
			if(v_mat.matches()) {
				wordslist.add(i);
			}
		}
		return wordslist.size();
	}
	
	public void phrase(String str,int weight,int length) {
		List<String> p_list = new ArrayList<String>();
		String regex ="[^0-9a-zA-Z]";	//剔除文本中的非字母和数字的部分并以！作为暂时的分隔符
		Pattern pat = Pattern.compile(regex);
		Matcher mat = pat.matcher(str);
		str = mat.replaceAll("!");				
		String [] textArray = str.split("!+");		//按照分隔符划分
		for(int i=0;i<textArray.length;i++) {
			String temp = new String();
			for(int j=0;j<length && i+j<textArray.length;j++) {
				temp += textArray[i+j];
				if(j!=length-1)	temp += " ";
			}
			if(i+length>textArray.length)	break;
			p_list.add(temp);
		}
		createmap(p_list,weight);
	}
	
	public void createmap(List<String> list,int weight) {
		for(String i:list){
			if(!ver.containsKey(i))
				ver.put(i, weight);
			else {
				int num = ver.get(i);
				ver.put(i, num+weight);
			}
		}
		List<Map.Entry<String,Integer>> verlist = new ArrayList<Map.Entry<String,Integer>>(ver.entrySet());
		Collections.sort(verlist,new Comparator<Map.Entry<String, Integer>>(){
			public int compare(Map.Entry<String, Integer> o1,Map.Entry<String, Integer> o2) {
				if(o1.getValue()==o2.getValue())
					return (o1.getKey()).compareTo(o2.getKey());
				return o2.getValue()-o1.getValue();
	        }
		});
		wordsmap = verlist;
	}
	
	public void writefile(String path,int number) {
		try {
			Writer file = new FileWriter(path);
			BufferedWriter out = new BufferedWriter(file);
			out.write("characters: " + characters+"\r\n");
			out.write("words: " + words+"\r\n");
			out.write("lines: " + lines+"\r\n");
			for(int i=0;i<number;i++){
				out.write("<"+wordsmap.get(i).getKey()+">: "+wordsmap.get(i).getValue()+"\r\n");
			}
			out.flush(); // 把缓存区内容压入文件
			out.close(); // 最后记得关闭文件
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
}
