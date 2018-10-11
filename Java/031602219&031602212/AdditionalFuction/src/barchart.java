import java.awt.Font;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.CategoryAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;

public class barchart {
	
	ChartPanel frame;
	List<Map.Entry<String,Integer>> topList = mainbody.authorTop;
	
	public barchart() {
		CategoryDataset dataset = getDataSet();
		JFreeChart chart = ChartFactory.createBarChart("论文作者统计", "作者","出现次数",dataset,PlotOrientation.VERTICAL,true,false,false);
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
		DefaultCategoryDataset dataset = new DefaultCategoryDataset();
//		System.out.println(topList.size());
		for(int i=0;i<20;i++){
			dataset.addValue(topList.get(i).getValue(), topList.get(i).getKey(), topList.get(i).getKey());
		}
		return dataset;
	}
	
	public ChartPanel getChartPanel() {
		return frame;
	}
}
