import java.awt.GridLayout;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.JFrame;

import com.csvreader.CsvReader;
import com.csvreader.CsvWriter;


public class mainbody {

	public static Map<String,details> ver = new HashMap<String, details>();
	public static Map<String,Integer> author = new HashMap<String, Integer>();
	public static List<Map.Entry<String,Integer>> authorTop = new ArrayList<Map.Entry<String,Integer>>();
	public static String csvFilePath = "cvpr2018-paper-list.csv";
	
	public static void main(String[] args) {		
		
		String strline = new String();
		details d_paper = new details();
		String title_regex = "Title: (.+)";
		String content_regex = "Abstract: (.+)";
		String authors_regex = "Authors: (.+)";
		String link_regex = "Link: (.+)";
		String month_regex = "Month: (.+)";
		
		try {		
			FileInputStream file = new FileInputStream("input.txt");
			InputStreamReader reader = new InputStreamReader(file);		//文件流读取
			BufferedReader buffReader = new BufferedReader(reader);		//构造文件流
			Pattern t_pat = Pattern.compile(title_regex);
			Pattern c_pat = Pattern.compile(content_regex);
			Pattern a_pat = Pattern.compile(authors_regex);
			Pattern l_pat = Pattern.compile(link_regex);
			Pattern m_pat = Pattern.compile(month_regex);
			
			while((strline = buffReader.readLine())!=null){
				Matcher t_mat = t_pat.matcher(strline);
				Matcher c_mat = c_pat.matcher(strline);
				Matcher a_mat = a_pat.matcher(strline);
				Matcher l_mat = l_pat.matcher(strline);
				Matcher m_mat = m_pat.matcher(strline);
				if(t_mat.find()) {
					d_paper.init();
					d_paper.setPaperTitle(t_mat.group(1).toLowerCase());
				}
				if(c_mat.find()) {
					String str = c_mat.group(1);
					String regex ="[^0-9a-zA-Z]";	//剔除文本中的非字母和数字的部分并以！作为暂时的分隔符
					Pattern pat = Pattern.compile(regex);
					Matcher mat = pat.matcher(str);
					str = mat.replaceAll(" ");		
					d_paper.setPaperAbstract(str);
				}
				if(a_mat.find()) {
					d_paper.setPaperAuthors(a_mat.group(1));
					authorTo(a_mat.group(1));
					phrase(d_paper);
				}
				if(l_mat.find()) {
					d_paper.setPaperUrl(l_mat.group(1));
				}
				if(m_mat.find()) {
					d_paper.setPaperMonth(m_mat.group(1));
				}
			}
			buffReader.close();
			readcsv(csvFilePath);
//			writecsv();	
			
//			for(int i=0;i<10;i++){
//				System.out.println("<"+authorTop.get(i).getKey()+">: "+authorTop.get(i).getValue()+"\r\n");
//			}
		} catch (IOException e) {
			
			e.printStackTrace();
		}
			
		JFrame frame=new JFrame("Java数据统计图");
		frame.setLayout(new GridLayout(2,2,10,10));
		System.out.println(authorTop);
		frame.add(new barchart().getChartPanel());
		frame.add(new wordsbarchart().getChartPanel());
		frame.add(new PieChart().getChartPanel());
		frame.setBounds(50, 50, 800, 600);
		frame.setVisible(true);
	}
	
	public static void phrase(details d) {
		details temp = new details();
		temp.init();
		temp.setPaperTitle(d.getPaperTitle());
		temp.setPaperAbstract(d.getPaperAbstract());
		temp.setPaperAuthors(d.getPaperAuthors());
		temp.setPaperUrl(d.getPaperUrl());
		temp.setPaperMonth(d.getPaperMonth());
//		System.out.println(d.getPaperType());
		if(!ver.containsKey(temp.getPaperTitle())) {
			ver.put(temp.getPaperTitle(),temp);
		}
	}
	
	public static void readcsv(String path) {
		try {
            CsvReader csvReader = new CsvReader(path);
            csvReader.readHeaders();
            while (csvReader.readRecord()){
            	if(ver.containsKey(csvReader.get("Title").toLowerCase())){
            		if(ver.get(csvReader.get("Title").toLowerCase()).getPaperType().equals("Poster")) {
            			ver.get(csvReader.get("Title").toLowerCase()).setPaperType(csvReader.get("Type"));
            		};
            		ver.get(csvReader.get("Title").toLowerCase()).setPaperId(csvReader.get("Paper ID"));
            	}
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
	}
	
	public static void writecsv() {
		CsvWriter csvWriter = new CsvWriter("CVPR_Details.csv",',', Charset.forName("GBK"));		
        try {      	
			String[] headers = {"PaperID","Title","Type","Abstract","Authors","Link","Month-2018"};
			csvWriter.writeRecord(headers);
			for(String i:ver.keySet()) {
				String[] contents = {ver.get(i).getPaperId(),ver.get(i).getPaperTitle(),ver.get(i).getPaperType(),ver.get(i).getPaperAbstract(),ver.get(i).getPaperAuthors(),ver.get(i).getPaperUrl(),ver.get(i).getPaperMonth()};
				csvWriter.writeRecord(contents);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
        csvWriter.close();
	}
	
	public static void authorTo(String str) {
		String [] authorArray = str.split(",");		//按照分隔符划分
		for(String name:authorArray) {
			if(!author.containsKey(name))
				author.put(name,1);
			else {
				int num = author.get(name);
				author.put(name,num+1);
			}
		}
		List<Map.Entry<String,Integer>> verlist = new ArrayList<Map.Entry<String,Integer>>(author.entrySet());
		Collections.sort(verlist,new Comparator<Map.Entry<String, Integer>>(){
			public int compare(Map.Entry<String, Integer> o1,Map.Entry<String, Integer> o2) {
				if(o1.getValue()==o2.getValue())
					return (o1.getKey()).compareTo(o2.getKey());
				return o2.getValue()-o1.getValue();
	        }
		});
		authorTop = verlist;
	}
}
