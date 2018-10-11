import java.awt.Font;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.CategoryAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;

public class wordsbarchart {
	
	ChartPanel frame;
	Map<String,Integer> top = new HashMap<String, Integer>();
	List<Map.Entry<String,Integer>> wordstop = new ArrayList<Map.Entry<String,Integer>>();
	
	public void readwords() {
		try {
			FileInputStream file = new FileInputStream("output.txt");	//构造文件流
			InputStreamReader reader = new InputStreamReader(file);		//文件流读取
			BufferedReader buffReader = new BufferedReader(reader);	
			String regex = "<(.+)>: (\\d+)";
			String strline;
			Pattern pat = Pattern.compile(regex);
			while((strline = buffReader.readLine())!=null){
				Matcher mat = pat.matcher(strline);
				if(mat.find()) {
					top.put(mat.group(1),Integer.parseInt(mat.group(2)));
				}
			}
			buffReader.close();
			List<Map.Entry<String,Integer>> verlist = new ArrayList<Map.Entry<String,Integer>>(top.entrySet());
			Collections.sort(verlist,new Comparator<Map.Entry<String, Integer>>(){
				public int compare(Map.Entry<String, Integer> o1,Map.Entry<String, Integer> o2) {
					if(o1.getValue()==o2.getValue())
						return (o1.getKey()).compareTo(o2.getKey());
					return o2.getValue()-o1.getValue();
		        }
			});
			wordstop = verlist;
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public wordsbarchart() {
		CategoryDataset dataset = getDataSet();
		JFreeChart chart = ChartFactory.createBarChart("词频统计", "词组","出现次数",dataset,PlotOrientation.VERTICAL,true,false,false);
		CategoryPlot plot = chart.getCategoryPlot();
		CategoryAxis domainAxis = plot.getDomainAxis();
		domainAxis.setLabelFont(new Font("黑体",Font.BOLD,14));
		domainAxis.setTickLabelFont(new Font("宋体",Font.BOLD,14));
		ValueAxis rangeAxis=plot.getRangeAxis();        
		rangeAxis.setLabelFont(new Font("黑体",Font.BOLD,15));          
		chart.getLegend().setItemFont(new Font("黑体", Font.BOLD, 15));          
		chart.getTitle().setFont(new Font("宋体",Font.BOLD,20));	
		frame = new ChartPanel(chart,true);
	}
	
	public CategoryDataset getDataSet() {
		readwords();
		DefaultCategoryDataset dataset = new DefaultCategoryDataset();
//		System.out.println(topList.size());
		for(int i=0;i<wordstop.size();i++){
			dataset.addValue(wordstop.get(i).getValue(), wordstop.get(i).getKey(), wordstop.get(i).getKey());
		}
		return dataset;
	}
	
	public ChartPanel getChartPanel() {
		return frame;
	}
}
