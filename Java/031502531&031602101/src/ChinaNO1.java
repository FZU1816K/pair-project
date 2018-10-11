import java.util.*;
import java.util.regex.Pattern;

public class ChinaNO1 {
	private String s;
	private St begin;
	private String alls=null;
	private int kazu=0;
	private int ww=1;
	private int w=1;
	private static boolean isNumeric(String str){
		 Pattern pattern = Pattern.compile("^[0-9]+?$"); 
		return pattern.matcher(str).matches();
	}
	private static boolean isTitle(String str){
		 Pattern pattern = Pattern.compile("^Title: .+?"); 
		return pattern.matcher(str).matches();
	}
	private static boolean isAbstract(String str){
		 Pattern pattern = Pattern.compile("^Abstract: .+?"); 
		return pattern.matcher(str).matches();
	}
	public ChinaNO1(int w,int m,int n){
		begin =new  St(m,n);	
		this.w=w;
		if (w==0) this.w=1;
		if (w==1) this.w=10;
	}
	public void setS(String s){
		if (isNumeric(s)) {
			kazu=kazu+s.length()+18;
			if (Integer.valueOf(s)!=0) kazu=kazu+2;
			return ;
		}
		if (isTitle(s)) {
			s=s.substring(7);
			ww=w;
		}
		if (isAbstract(s)){
			s=s.substring(10);
			ww=1;
		}
		if (s!=null){
		    this.s=s.toLowerCase();
		}
			begin.getS(this.getS(), ww);
	}
	public String getS(){
		return s;
	}
	public int getKazu() {
		return kazu;
	}
	public St getSt(){
		return begin;
	}
}
